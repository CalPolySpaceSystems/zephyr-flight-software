#
# Copyright (c) 2017 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

PREFIX ?= .
OBJ_DIR ?= $(PREFIX)/obj
LIB_DIR ?= $(PREFIX)/lib

all:
	mkdir -p $(OBJ_DIR) $(LIB_DIR)
	$(CC) -c $(CFLAGS) -Iinclude src/ms56xx.c -o $(OBJ_DIR)/ms56xx.o
	$(AR) -rcs $(LIB_DIR)/libms56xx.a $(OBJ_DIR)/ms56xx.o

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)
