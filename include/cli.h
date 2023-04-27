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


#ifndef CLI_H_
#define CLI_H_


/******************/
/* === MACROS === */
/******************/
;


/**********************/
/* === DATA TYPES === */
/**********************/
typedef struct {
  char short_name;
  char* long_name;
  int (*handler)(int*, char***, void*);
  void* data;
} commander_option;
typedef struct {
  int (*handler)(int, char**);
  commander_option** options;
} commander_command;
typedef struct {
  int (*handler)(int*, char***, void*);
  void* data;
} commander;


/*********************************/
/* === FUNCTION DECLARATIONS === */
/*********************************/
int cli_group_handler(int*, char***, void*);
int cli_command_handler(int*, char***, void*);
int cli_flag_handler(int*, char***, void*);
int cli_handle(int, char**, commander*);


#endif  // CLI_H_