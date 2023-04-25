/*
* GNU Kifi, a multi-algorithm PoW miner.
* Copyright (C) 2023-2023 Wasym A. Alonso
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/*******************/
/* === HEADERS === */
/*******************/
#include <string.h>
#include <keccak-256.h>


/******************/
/* === MACROS === */
/******************/
#define I64(x) (x ## LL)
#define ROTATE_LEFT64(qword, n) (qword << n ^ (qword >> (64 - n)))
#define IS_ALIGNED_64(p) (0 == (7 & ((const char*) p - (const char*) 0)))


/****************************/
/* === GLOBAL VARIABLES === */
/****************************/
const uint8_t constants[] = {
  1, 26, 94, 112, 31, 33, 121, 85, 14, 12, 53, 38, 63, 79, 93, 83, 82, 72, 22, 102, 121, 88, 33, 116,
  1, 6, 9, 22, 14, 20, 2, 12, 13, 19, 23, 15, 4, 24, 21, 8, 16, 5, 3, 18, 17, 11, 7, 10,
  1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43, 25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14,
};


/********************************/
/* === FUNCTION DEFINITIONS === */
/********************************/
uint8_t get_constant(uint8_t type, uint8_t index) {
  return constants[type + index];
}

uint64_t get_round_constant(uint8_t round) {
  uint64_t result = 0;
  uint8_t round_info = get_constant(KECCAK256_ROUND_INFO, round);

  if (round_info & (1 << 6)) { result |= ((uint64_t) 1 << 63); }
  if (round_info & (1 << 5)) { result |= ((uint64_t) 1 << 31); }
  if (round_info & (1 << 4)) { result |= ((uint64_t) 1 << 15); }
  if (round_info & (1 << 3)) { result |= ((uint64_t) 1 << 7); }
  if (round_info & (1 << 2)) { result |= ((uint64_t) 1 << 3); }
  if (round_info & (1 << 1)) { result |= ((uint64_t) 1 << 1); }
  if (round_info & (1 << 0)) { result |= ((uint64_t) 1 << 0); }

  return result;
}

void keccak256_init(keccak256_ctx* ctx) {
  memset(ctx, 0, sizeof(keccak256_ctx));
}

void keccak256_theta(uint64_t* A) {
  uint64_t C[5], D[5];

  for (uint8_t i = 0; i < 5; i++) {
    C[i] = A[i];
    for (uint8_t j = 5; j < 25; j += 5) C[i] ^= A[i + j];
  }
  for (uint8_t i = 0; i < 5; i++) {
    D[i] = ROTATE_LEFT64(C[(i + 1) % 5], 1) ^ C[(i + 4) % 5];
  }
  for (uint8_t i = 0; i < 5; i++) {
    for (uint8_t j = 0; j < KECCAK256_MAX_PERMUTATION_SIZE; j += 5) {
      A[i + j] ^= D[i];
    }
  }
}

void keccak256_pi(uint64_t* A) {
  uint64_t A1 = A[1];

  for (uint8_t i = 1; i < KECCAK256_PI_TRANSFORM; i++) {
    A[get_constant(KECCAK256_PI_TRANSFORM, i - 1)] = A[get_constant(KECCAK256_PI_TRANSFORM, i)];
  }
  A[10] = A1;
}

void keccak256_chi(uint64_t* A) {
  for (uint8_t i = 0; i < KECCAK256_MAX_PERMUTATION_SIZE; i += 5) {
    uint64_t A0 = A[i + 0],
             A1 = A[i + 1];
    A[i + 0] ^= ~A1 & A[i + 2];
    A[i + 1] ^= ~A[i + 2] & A[i + 3];
    A[i + 2] ^= ~A[3 + i] & A[i + 4];
    A[i + 3] ^= ~A[i + 4] & A0;
    A[i + 4] ^= ~A0 & A1;
  }
}

void keccak256_permutation(uint64_t* hash) {
  for (uint8_t round = 0; round < KECCAK256_MAX_QWORDS_RATE; round++) {
    keccak256_theta(hash);

    for (uint8_t i = 1; i < KECCAK256_MAX_PERMUTATION_SIZE; i++) {
      hash[i] = ROTATE_LEFT64(hash[i], get_constant(KECCAK256_RHO_TRANSFORM, i - 1));
    }

    keccak256_pi(hash);
    keccak256_chi(hash);
    *hash ^= get_round_constant(round);
  }
}

void keccak256_process_block(uint64_t* hash, const uint64_t* block) {
  for (uint8_t i = 0; i < 17; i++) hash[i] ^= block[i];
  keccak256_permutation(hash);
}

void keccak256_update(keccak256_ctx* ctx, const byte* msg, uint16_t size) {
  uint16_t idx = (uint16_t) ctx->rest;
  ctx->rest = (unsigned) ((ctx->rest + size) % KECCAK256_BLOCK_SIZE_DERIV);

  if (idx) {
    uint16_t left = KECCAK256_BLOCK_SIZE_DERIV - idx;
    memcpy((char*) ctx->msg + idx, msg, (size < left ? size : left));
    if (size < left) return;

    keccak256_process_block(ctx->hash, ctx->msg);
    msg += left;
    size -= left;
  }

  while (size >= KECCAK256_BLOCK_SIZE_DERIV) {
    uint64_t* aligned_msg_block;
    if (IS_ALIGNED_64(msg)) aligned_msg_block = (uint64_t*)(void*) msg;
    else {
      memcpy(ctx->msg, msg, KECCAK256_BLOCK_SIZE_DERIV);
      aligned_msg_block = ctx->msg;
    }

    keccak256_process_block(ctx->hash, aligned_msg_block);
    msg += KECCAK256_BLOCK_SIZE_DERIV;
    size -= KECCAK256_BLOCK_SIZE_DERIV;
  }

  if (size) memcpy(ctx->msg, msg, size);
}

void keccak256_out(keccak256_ctx* ctx, byte* hash) {
  memset((char*) ctx->msg + ctx->rest, 0, KECCAK256_BLOCK_SIZE_DERIV - ctx->rest);
  ((char*) ctx->msg)[ctx->rest] |= 0x01;
  ((char*) ctx->msg)[KECCAK256_BLOCK_SIZE_DERIV - 1] |= 0x80;

  keccak256_process_block(ctx->hash, ctx->msg);

  if (hash) memcpy(hash, ctx->hash, KECCAK256_BLOCK_SIZE);
}

void keccak256_compute(byte* string, byte* hash) {
  keccak256_ctx ctx;

  keccak256_init(&ctx);
  keccak256_update(&ctx, string, strlen((char*) string));
  keccak256_out(&ctx, hash);
}
