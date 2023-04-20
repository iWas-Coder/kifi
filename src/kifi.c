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
#include <sha-256.h>
#include <stdio.h>


/****************/
/* === MAIN === */
/****************/
int main(void) {
  byte text[] = {"test"};
  byte hash[SHA256_BLOCK_SIZE];
  sha256_compute(text, hash);

  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) printf("%02x", hash[i]);
  printf("\n");

  return 0;
}
