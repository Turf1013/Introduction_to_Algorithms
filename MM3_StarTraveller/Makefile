##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: star
star: starTraveller.cpp
	$(CXX) $(CFLAGS) -o star starTraveller.cpp $(LIBS)

base: starTraveller_v0a.cpp
	$(CXX) $(CFLAGS) -o base starTraveller_v0a.cpp $(LIBS)


.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm star star.g* 2> /dev/null || true	
		-@rm base 2> /dev/null || true	

test: build
		java -jar tester.jar -exec ./star -seed 1 -vis -delay 1000
		@echo

