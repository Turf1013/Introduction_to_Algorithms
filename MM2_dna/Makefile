##
#	Makefile for `CutTheRoots` application
##

CXX = g++
LIBS = -lrt
CFLAGS = -Wall

build: dna
CutTheRoots: dna.cpp
	$(CXX)	$(CFLAGS) -o dna dna.cpp $(LIBS)

.PHONY: clean test
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm dna dna.g* 2> /dev/null || true	

test: build
		./dna 1
		@echo
		./dna 2
		@echo
		./dna 3
		@echo

