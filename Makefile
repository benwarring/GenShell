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

$(OBJ)/shell_utils.o: $(SRC)/shell_utils.c $(INCLUDE)/shell_utils.h
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/shell.o: $(SRC)/shell.c $(INCLUDE)/wrappers.h $(INCLUDE)/shell_utils.h
	$(CC) $(CFLAGS) -c $(SRC)/shell.c -o $(OBJ)/shell.o

shell: $(OBJ)/shell.o $(OBJ)/wrappers.o $(OBJ)/shell_utils.o
	$(CC) $(CFLAGS) $(OBJ)/shell.o $(OBJ)/wrappers.o $(OBJ)/shell_utils.o -o shell

.PHONY: clean
clean:
	/bin/rm -f $(OBJ)/*.o $(BIN)/$(EXECS) $(EXECS)
