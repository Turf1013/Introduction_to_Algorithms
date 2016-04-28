##
#	Makefile for `dna` application
##

CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3

build: dna
dna: dna.cpp
	$(CXX) $(CFLAGS) -o dna dna.cpp $(LIBS)

ob: observe
observe: observe.cpp
	$(CXX) $(CFLAGS) -o ob observe.cpp $(LIBS)

freq: frequency
frequency: frequency.cpp
	$(CXX) $(CFLAGS) -o freq frequency.cpp $(LIBS)

algo: algorithm
algorithm: algorithm.cpp
	$(CXX) $(CFLAGS) -o algo algorithm.cpp $(LIBS)

.PHONY: clean test
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm dna dna.g* 2> /dev/null || true	

test: build
		./dna 12
		@echo

