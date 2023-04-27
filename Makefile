#
# GNU Kifi, a multi-algorithm PoW miner.
# Copyright (C) 2023-2023 Wasym A. Alonso
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#


##################
# === MACROS === #
##################
# Project information
APP = kifi
DESC = a multi-algorithm PoW miner
# Version and metadata
VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = -rc1
NAME = Hurr durr I'ma ninja hash
ifeq ($(SUBLEVEL),0)
        FULL_VERSION ?= $(VERSION).$(PATCHLEVEL)$(EXTRAVERSION)
else
        FULL_VERSION ?= $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)$(EXTRAVERSION)
endif

# Pretty Printing Output (PPO)
PPO_MKDIR = MKDIR
PPO_CLEAN = CLEAN
PPO_CPP = CPP
PPO_CC = CC
PPO_ASM = ASM
PPO_LD = LD

# Directories
SRC_DIR = src
HDR_DIR = include
BUILD_DIR = build
CPP_DIR = $(BUILD_DIR)/cpp
ASM_DIR = $(BUILD_DIR)/asm
OBJ_DIR = $(BUILD_DIR)/obj

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
ASMS := $(patsubst $(SRC_DIR)/%.c,$(ASM_DIR)/%.s,$(SRCS))
CPPS := $(patsubst $(SRC_DIR)/%.c,$(CPP_DIR)/%.i,$(SRCS))
OUT = $(APP)_v$(FULL_VERSION)

# Compilation flags
CC = gcc
CPPFLAGS = -I $(HDR_DIR)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu2x -O2
LDFLAGS =

# PHONY targets definition
.PHONY: all $(APP) test clean mrproper help

# SECONDARY targets definition
.SECONDARY: $(CPPS) $(ASMS)


###################
# === TARGETS === #
###################
# Root target
all: $(APP)

# App binary
$(APP): $(OUT)

# Linking stage
$(OUT): $(OBJS)
	@printf	"$(PPO_LD)\t$@\n"
	@$(CC) $^ $(LDFLAGS) -o $@

# Assembly stage
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.s
	@if [ ! -d $(OBJ_DIR) ]; then \
		printf "$(PPO_MKDIR)\t$(OBJ_DIR)\n"; \
		mkdir -p $(OBJ_DIR); \
	fi
	@printf	"$(PPO_ASM)\t$@\n"
	@$(CC) -c $< -o $@

# Compilation stage
$(ASM_DIR)/%.s: $(CPP_DIR)/%.i
	@if [ ! -d $(ASM_DIR) ]; then \
		printf "$(PPO_MKDIR)\t$(ASM_DIR)\n"; \
		mkdir -p $(ASM_DIR); \
	fi
	@printf	"$(PPO_CC)\t$@\n"
	@$(CC) $(CFLAGS) -S $< -o $@

# Preprocessing stage
$(CPP_DIR)/%.i: $(SRC_DIR)/%.c
	@if [ ! -d $(CPP_DIR) ]; then \
		printf "$(PPO_MKDIR)\t$(CPP_DIR)\n"; \
		mkdir -p $(CPP_DIR); \
	fi
	@printf	"$(PPO_CPP)\t$@\n"
	@$(CC) $(CPPFLAGS) -E $< -o $@


#########################
# === PHONY TARGETS === #
#########################
# Runs all unit tests
test:
	@printf "test"

# Clean build directory
clean:
	@if [ -d $(BUILD_DIR) ]; then \
		printf "$(PPO_CLEAN)\t$(BUILD_DIR)\n"; \
		rm -r $(BUILD_DIR); \
	fi

# Cleans final products (depends on 'build')
mrproper: clean
	@if [ -e $(OUT) ]; then \
		printf "$(PPO_CLEAN)\t$(OUT)\n"; \
		rm $(OUT); \
	fi

# Help
help:
	@printf "all\t\t- Build all targets marked with [*]\n"
	@printf "* $(APP)\t\t- Build the '$(APP)' binary\n"
	@printf "test\t\t- Runs all unit tests\n"
	@printf "clean\t\t- Clean build directory\n"
	@printf "mrproper\t- Cleans final products (depends on 'build')\n"
	@echo ""
	@printf "Execute 'make' or 'make all' to build all targets marked with [*]\n"
	@printf "For further info see the ./README file and the documentation generated\n"
