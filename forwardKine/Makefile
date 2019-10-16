# the compiler
CC=g++
# options 
CFLAGS=-std=c++11 -c 

SOURCES=main.cpp 

FILE='coredump'

OBJECTS=$(SOURCES:.cpp=.o)

LDFLAGS=-L/usr/local/lib

EXECUTABLE=app

all: $(SOURCES)  $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run_test: clean all
	./$(EXECUTABLE) ${ARGS}

debug_compile: 
	$(CC) -std=c++11 -g $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

run_gdb: clean debug_compile
	gdb --args $(EXECUTABLE) ${ARGS} 

run_gdb_core_file: clean debug_compile
	gdb -c ${FILE} --args $(EXECUTABLE) ${ARGS}

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)