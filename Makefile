.PHONY: clean

# Compiler & options
CC=g++-8
CFLAGS=-std=c++17 -pthread -Wall -Wextra -Wshadow -Wconversion -fsanitize=address -fsanitize=undefined
CFLAGS+=-lstdc++fs
CFLAGS+=$(DFLAGS)

# File directory
BIN_DIR=bin
OBJ_DIR=obj
SRC_DIR=src

# Files
_MAIN=reader
_MAIN_OBJ=main.o record.o common.o

# Directed Files
MAIN=$(patsubst %, $(BIN_DIR)/%, $(_MAIN))
MAIN_OBJ=$(patsubst %, $(OBJ_DIR)/%, $(_MAIN_OBJ))

# Default target: all
default: clean all

# Make all
all: $(MAIN)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

# Make traceroute
main: $(MAIN)

$(MAIN): $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Objective file dependency
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean middle files
clean:
	rm -f $(OBJ_DIR)/*
	rm -f $(BIN_DIR)/*
