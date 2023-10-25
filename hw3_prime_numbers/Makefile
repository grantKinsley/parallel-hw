########################################################################
# Makefile : Build hw2
# Author   : Claudio Parra.
# Licence  : Creative Commons.
#
# To Build this homework, run:
#     make
#
# To clean the binary files created, run:
#     make clean
########################################################################

# make sure we are using bash and not other shell.
SHELL    := /bin/bash

# hw name and common code dir
bin_name := prime_finder.bin
cmn_dir  := common

# Compiler and linker options.
CC      := gcc
CFLAGS  := -I $(cmn_dir)/ -g
CWARN   := -Wall -Wextra
LIBS    := -pthread -lm

# files
HW_SRC   := $(wildcard *.c)
CMN_SRC  := $(wildcard $(cmn_dir)/*.c)
DEPENDS  := $(patsubst %.c,%.d,$(HW_SRC) $(CMN_SRC))
HW_OBJ   := $(patsubst %.c,%.o,$(HW_SRC))
CMN_OBJ  := $(patsubst %.c,%.o,$(CMN_SRC))

.PHONY: clean

$(bin_name): $(HW_OBJ) $(CMN_OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CWARN) $(CFLAGS) -MMD -MP -c $< -o $@


clean:
	@rm -f $(HW_OBJ) $(bin_name)
	@rm -f $(CMN_OBJ)
	@rm -f $(DEPENDS)
