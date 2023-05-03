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


#ifndef PPO_H_
#define PPO_H_


/******************/
/* === MACROS === */
/******************/
#define HASH_LENGTH 32
#define RESET "\033[0m"
#define RED_BOLD "\033[1;31m"
#define CYAN_BOLD "\033[1;36m"
#define WHITE_BOLD "\033[1;37m"
#define GREEN_BOLD "\033[1;32m"
#define YELLOW_BOLD "\033[1;33m"


/**********************/
/* === DATA TYPES === */
/**********************/
typedef unsigned char byte;


/*********************************/
/* === FUNCTION DECLARATIONS === */
/*********************************/
void print_hash(byte* hash);


#endif  // PPO_H_
