CC = gcc
CFLAGS = -std=gnu99 -Wall -g -I$(INCLUDE) #-DDEBUG

SRC = src
BIN = bin
INCLUDE = include
OBJ = obj

EXECS = $(BIN)/shell

all: $(EXECS)

$(OBJ)/wrappers.o: $(SRC)/wrappers.c $(INCLUDE)/wrappers.h
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/shell.o: $(SRC)/shell.c $(INCLUDE)/wrappers.h
	$(CC) $(CFLAGS) -c $(SRC)/shell.c -o $(OBJ)/shell.o
	
$(BIN)/shell: $(OBJ)/shell.o $(OBJ)/wrappers.o
	$(CC) $(CFLAGS) $(OBJ)/shell.o $(OBJ)/wrappers.o -o $(BIN)/shell

.PHONY: clean
clean:
	/bin/rm -f $(OBJ)/*.o $(EXECS)
