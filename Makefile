LIBS := -lIrrlicht -lGL -lX11 -lXxf86vm

CC=g++
CFLAGS=-I.


# Name of the executable created
EJEC:= AncientRise
# Path for the executable
BINPATH = ./bin
# Path for the .o files
BUILDPATH = ./obj
# Path for the source files
SOURCEPATH = ./sourcefiles

EXECUTABLE = $(BINPATH)/$(EJEC)
SRC := $(wildcard $(SOURCEPATH)/*.cpp)
#OBJ := $(subst .cpp,.o,$(SRC))
OBJ = $(patsubst $(SOURCEPATH)/%.cpp, $(BUILDPATH)/%.o, $(SRC))

$(EJEC): prepare $(OBJ)
	$(warning Creando el ejecutable $@...)
	$(CC) -o $(EXECUTABLE) $^ $(LIBS) 


$(BUILDPATH)/%.o: $(SOURCEPATH)/%.cpp 
	$(warning Creando el binario $@...)
	#$(CC) -c -o $@ $^ $(CFLAGS)
	$(CC) $(CFLAGS) -c $< -o $@

info:
	$(info $(SRC))
	$(info $(OBJ))


clean: 
	rm -f $(BUILDPATH)/*.o 
	rm -f $(BINPATH)/$(EJEC)

prepare:
	$(warning Creando la estructura de carpetas)
	mkdir -p $(BINPATH)
	mkdir -p $(BUILDPATH)


