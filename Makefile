OBJ := obj
INCL := include
SRC := src

SOURCES := $(filter-out $(SRC)/%_incl.c, $(wildcard $(SRC)/*.c))
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

EXEC := bf

CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic

all: $(OBJ) $(EXEC)

.PHONY: clean

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

$(OBJ)/main.o: $(SRC)/main.c $(INCL)/util.h
	$(CC) $(SRC)/main.c -I$(INCL) -c -o $(OBJ)/main.o

$(OBJ)/util.o: $(SRC)/util.c $(INCL)/util.h
	$(CC) $(SRC)/util.c -I$(INCL) -c -o $(OBJ)/util.o

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -f main $(OBJECTS)
