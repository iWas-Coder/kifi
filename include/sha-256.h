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


#ifndef SHA256_H_
#define SHA256_H_


/*******************/
/* === HEADERS === */
/*******************/
#include <stddef.h>


/******************/
/* === MACROS === */
/******************/
#define SHA256_BLOCK_SIZE 32


/**********************/
/* === DATA TYPES === */
/**********************/
typedef unsigned char byte;
typedef unsigned int word;
typedef struct {
  byte data[64];
  word data_len;
  unsigned long long bit_len;
  word state[8];
} sha256_ctx;


/*********************************/
/* === FUNCTION DECLARATIONS === */
/*********************************/
void sha256_init(sha256_ctx* ctx);
void sha256_transform(sha256_ctx* ctx, const byte* data);
void sha256_update(sha256_ctx* ctx, const byte* data, size_t len);
void sha256_out(sha256_ctx* ctx, byte* hash);
void sha256_compute(byte* string, byte* hash);


#endif  // SHA256_H_
