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
#include <stdio.h>


/********************************/
/* === FUNCTION DEFINITIONS === */
/********************************/
void print_hash(byte* hash) {
  printf(WHITE_BOLD);
  for (unsigned int i = 0; i < HASH_LENGTH; i++) printf("%02x", hash[i]);
  printf("%s\n", RESET);
}

void print_exec_time(clock_t t0, clock_t t1, char* msg) {
  double exec_time = (double) (t1 - t0) / CLOCKS_PER_SEC;
  printf("\n%s%s: ", PURPLE_BOLD, msg);
  // Microseconds
  if ((int) exec_time == 0) printf("%u μs\n", (int) (exec_time * MICROSECS_IN_SEC));
  // Minutes
  else if (exec_time > SECS_IN_MIN) printf("%u min\n", (int) (exec_time / SECS_IN_MIN));
  // Seconds
  else printf("%.2f s\n", exec_time);
  printf(RESET);
}
