##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: cross
cross: terrainCrossing.cpp
	$(CXX) $(CFLAGS) -o cross terrainCrossing.cpp $(LIBS)

base: terrainCrossing_v0.cpp
	$(CXX) $(CFLAGS) -o base terrainCrossing_v0.cpp $(LIBS)


.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm cross cross.g* 2> /dev/null || true	
		-@rm base 2> /dev/null || true	

test: build
		java -jar tester.jar -exec ./cross -seed 1 -debug
		@echo

