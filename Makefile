CC = gcc
CFLAGS = -std=gnu99 -Wall -g -I$(INCLUDE) #-DDEBUG

SRC = src
BIN = bin
INCLUDE = include
OBJ = obj

EXECS = 

all: $(EXECS)

$(OBJ)/wrappers.o: $(SRC)/wrappers.c $(INCLUDE)/wrappers.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	/bin/rm -f $(OBJ)/*.o $(EXECS)
