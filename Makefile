CC = gcc
CFLAGS = -std=gnu99 -Wall -g -I$(INCLUDE) #-DDEBUG

SRC = src
BIN = bin
INCLUDE = include
OBJ = obj

EXECS = shell

all: $(EXECS)

$(OBJ)/wrappers.o: $(SRC)/wrappers.c $(INCLUDE)/wrappers.h
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/shell.o: $(SRC)/shell.c $(INCLUDE)/wrappers.h
	$(CC) $(CFLAGS) -c $(SRC)/shell.c -o $(OBJ)/shell.o
	
shell: $(OBJ)/shell.o $(OBJ)/wrappers.o
	$(CC) $(CFLAGS) $(OBJ)/shell.o $(OBJ)/wrappers.o -o shell

.PHONY: clean
clean:
	/bin/rm -f $(OBJ)/*.o $(BIN)/$(EXECS) $(EXECS)
