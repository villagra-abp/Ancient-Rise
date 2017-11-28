LIBS := -lIrrlicht

CC=g++
CFLAGS=-I.

EJEC:= AncientRise

SOURCES := $(wildcard *.cpp)
OBJ := $(subst .cpp,.o,$(SOURCES))

$(EJEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp 
	$(CC) -c -o $@ $^ $(CFLAGS)


info:
	$(info $(SOURCES))
	$(info $(OBJ))

clean: 
	rm -f *.o 
	rm -f $(EJEC)
