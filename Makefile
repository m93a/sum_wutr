#compiler
CC = g++

#c++ flags
CPPFLAGS = -std=c++0x

#linker flags
LOADLIBES = -lGL -lGLU -lglut

target = main
objects = main.o math.o vector.o gl.o particle.o crystal.o crystal_bond.o

default: $(target)

$(target): $(objects)
	$(CC) $^ $(LOADLIBES) -o $@

help:
	@echo ""
	@echo "  Hi!"
	@echo "  You probably want to know how to use this makefile."
	@echo "  It's easy: first, run \`make\`,"
	@echo "  then \`make install\` and finally \`make clean\`."
	@echo "  I wish you nice compiling :)"
	@echo ""

install:
	@echo ""
	@echo "  This is an alpha. You cannot install it yet."
	@echo "  If you want to try the program, run \`./main\`"
	@echo ""

clean:
	rm -f *.o
	rm -f *~

.PHONY: help default clean
