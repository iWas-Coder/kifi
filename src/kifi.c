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
#include <ppo.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sha-256.h>
#include <keccak-256.h>


/******************/
/* === MACROS === */
/******************/
#define EXAMPLE "hello"
#define ZEROS 1


/****************/
/* === MAIN === */
/****************/
int main(void) {
  // Input
  byte text[] = EXAMPLE;
  printf("%sInput:%s ", RED_BOLD, RESET);
  printf("%s%s%s\n\n", WHITE_BOLD, text, RESET);

  // SHA-256
  byte sha256_hash[SHA256_BLOCK_SIZE];
  sha256_compute(text, sha256_hash);
  printf("%sSHA-256:%s %s", YELLOW_BOLD, RESET, WHITE_BOLD);
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) printf("%02x", sha256_hash[i]);
  printf("%s\n", RESET);

  // SHA-256d
  byte sha256d_hash[SHA256_BLOCK_SIZE];
  sha256d_compute(text, sha256d_hash);
  printf("%sSHA-256d:%s %s", YELLOW_BOLD, RESET, WHITE_BOLD);
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) printf("%02x", sha256d_hash[i]);
  printf("%s\n", RESET);

  // Keccak-256
  byte keccak256_hash[KECCAK256_BLOCK_SIZE];
  keccak256_compute(text, keccak256_hash);
  printf("%sKeccak-256:%s %s", YELLOW_BOLD, RESET, WHITE_BOLD);
  for (int i = 0; i < KECCAK256_BLOCK_SIZE; i++) printf("%02x", keccak256_hash[i]);
  printf("%s\n\n", RESET);

  // Random nonce starting point
  srand(time(NULL));
  uint32_t nonce = rand();
  printf("%sNonce starting point (random):%s %s0x%02x%s\n", CYAN_BOLD, RESET, WHITE_BOLD, nonce, RESET);
  printf("%sNumber of leading zeros:%s %s%u%s\n", CYAN_BOLD, RESET, WHITE_BOLD, ZEROS, RESET);
  printf("Press ENTER key to continue...\n");
  getchar();

  // Hashing loop
  printf("%sSHA-256d hashing:%s\n", RED_BOLD, RESET);
  clock_t t0, t1;
  t0 = clock();
  for (;;) {
    char str[SHA256_BLOCK_SIZE];
    sprintf(str, "%u", nonce);
    byte hash_candidate[SHA256_BLOCK_SIZE];
    sha256d_compute((byte*) str, hash_candidate);
    print_hash(hash_candidate);
    
    uint32_t zeros = 0;
    for (int i = 0; i < ZEROS && i < (int) sizeof(hash_candidate); i++) {
      if (hash_candidate[i] == 0) zeros++;
      else break;
    }
    if (zeros == ZEROS) {
      // Execution time (completed)
      t1 = clock();
      print_exec_time(t0, t1, "Execution time");

      // Print found hash and corresponding nonce
      printf("\n%sNonce:%s %s0x%02x%s\n", GREEN_BOLD, RESET, WHITE_BOLD, nonce, RESET);
      printf("%sHash:%s ", GREEN_BOLD, RESET);
      print_hash(hash_candidate);
      return 0;
    }

    nonce++;
  }

  // Time spent (not completed)
  t1 = clock();
  print_exec_time(t0, t1, "Time spent");

  return 1;
}
