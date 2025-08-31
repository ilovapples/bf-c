BINC := $(HOME)/Coding/include
BLIB := $(HOME)/Coding/lib

OBJECTS := main.o util.o
APLCORE_LDFLAGS := -L$(BLIB) -laplcore

EXEC := bf

$(EXEC): $(OBJECTS) $(BLIB)/libaplcore.a
	gcc $(OBJECTS) $(APLCORE_LDFLAGS) -o $(EXEC)

main.o: main.c util.h $(BINC)/aplcore/types.h
	gcc main.c -I$(BINC) -I$(BINC)/aplcore -c -o main.o

util.o: util.c util.h $(BINC)/aplcore/types.h
	gcc util.c -I$(BINC) -I$(BINC)/aplcore -c -o util.o

clean:
	rm -f main $(OBJECTS)
