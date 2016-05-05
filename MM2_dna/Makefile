##
#	Makefile for `dna` application
##
CC = gcc
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

sl: slices
slices: slice.cpp
	$(CXX) $(CFLAGS) -o sl slice.cpp $(LIBS)

hash: hash.cpp
	$(CXX) $(CFLAGS) -o hash hash.cpp $(LIBS)

train: train.cpp
	$(CXX) $(CFLAGS) -o train train.cpp $(LIBS)

score: score.cpp
	$(CXX) $(CFLAGS) -o score score.cpp $(LIBS)
	

.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm dna dna.g* 2> /dev/null || true	
		-@rm ob freq algo sl hash train score 2> /dev/null || true	

test: build
		./dna 12
		@echo

