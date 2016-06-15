##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: exam
exam: onlineExam.cpp
	$(CXX) $(CFLAGS) -o exam onlineExam.cpp $(LIBS)

base: onlineExam_v0.cpp
	$(CXX) $(CFLAGS) -o base onlineExam_v0.cpp $(LIBS)


.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm exam exam.g* 2> /dev/null || true	
		-@rm base 2> /dev/null || true	

test: build
		java -jar tester.jar -exec ./exam -seed 1 -vis -delay 1000
		@echo

