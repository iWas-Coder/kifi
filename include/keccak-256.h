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


#ifndef KECCAK256_H_
#define KECCAK256_H_


/*******************/
/* === HEADERS === */
/*******************/
#include <stdint.h>


/******************/
/* === MACROS === */
/******************/
#define KECCAK256_MAX_PERMUTATION_SIZE 25
#define KECCAK256_MAX_QWORDS_RATE 24
#define KECCAK256_BLOCK_SIZE_DERIV ((1600 - 256 * 2) / 8)
#define KECCAK256_BLOCK_SIZE (100 - KECCAK256_BLOCK_SIZE_DERIV / 2)
#define KECCAK256_ROUND_INFO 0
#define KECCAK256_PI_TRANSFORM KECCAK256_MAX_QWORDS_RATE
#define KECCAK256_RHO_TRANSFORM 48


/**********************/
/* === DATA TYPES === */
/**********************/
typedef unsigned char byte;
typedef struct {
  uint64_t hash[KECCAK256_MAX_PERMUTATION_SIZE];
  uint64_t msg[KECCAK256_MAX_QWORDS_RATE];
  uint16_t rest;
} keccak256_ctx;


/*********************************/
/* === FUNCTION DECLARATIONS === */
/*********************************/
uint8_t get_constant(uint8_t type, uint8_t index);
uint64_t get_round_constant(uint8_t round);
void keccak256_init(keccak256_ctx* ctx);
void keccak256_theta(uint64_t* A);
void keccak256_pi(uint64_t* A);
void keccak256_chi(uint64_t* A);
void keccak256_permutation(uint64_t* hash);
void keccak256_process_block(uint64_t* hash, const uint64_t* block);
void keccak256_update(keccak256_ctx* ctx, const byte* msg, uint16_t size);
void keccak256_out(keccak256_ctx* ctx, byte* hash);
void keccak256_compute(byte* string, byte* hash);


#endif  // KECCAK256_H_
