LIBS := -lIrrlicht

CC=g++
CFLAGS=-I.

SOURCES := $(wildcard *.cpp)
OBJ := $(subst .cpp,.o,$(SOURCES))

ancientRise: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp 
	$(CC) -c -o $@ $^ $(CFLAGS)

	//$(DEPS)

info:
	$(info $(SOURCES)
	$(info $(OBJ))