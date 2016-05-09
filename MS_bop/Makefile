##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: hop
hop: hop.cpp
	$(CXX) $(CFLAGS) -o hop hop.cpp $(LIBS)

prep: preprocess.cpp
	$(CXX) $(CFLAGS) -o prep preprocess.cpp $(LIBS)

	

.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm hop hop.g* 2> /dev/null || true	
		-@rm prep 2> /dev/null || true	

test: build
		./hop
		@echo

