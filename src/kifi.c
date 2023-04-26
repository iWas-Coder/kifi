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
#include <stdio.h>
#include <ppo.h>
#include <sha-256.h>
#include <keccak-256.h>


/****************/
/* === MAIN === */
/****************/
int main(void) {
  byte text[] = "test";
  printf("%sInput:%s ", RED_BOLD, RESET);
  printf("%s%s%s\n\n", WHITE_BOLD, text, RESET);

  byte sha256_hash[SHA256_BLOCK_SIZE];
  sha256_compute(text, sha256_hash);
  printf("%sSHA-256:%s %s", YELLOW_BOLD, RESET, WHITE_BOLD);
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) printf("%02x", sha256_hash[i]);
  printf("%s\n", RESET);

  byte keccak256_hash[KECCAK256_BLOCK_SIZE];
  keccak256_compute(text, keccak256_hash);
  printf("%sKeccak-256:%s %s", YELLOW_BOLD, RESET, WHITE_BOLD);
  for (int i = 0; i < KECCAK256_BLOCK_SIZE; i++) printf("%02x", keccak256_hash[i]);
  printf("%s\n", RESET);

  return 0;
}
