##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: Simple SimpleMem
Simple: monitor.h input.h output.h global.h simpleGreedy.cpp
	$(CXX) $(CFLAGS) -o Simple simpleGreedy.cpp $(LIBS)

SimpleMem: monitor.h input.h output.h global.h simpleGreedy.cpp
	$(CXX) $(CFLAGS) -o SimpleMem simpleGreedy.cpp $(LIBS) -D WATCH_MEM

OPT: monitor.h input.h output.h global.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPT OPT.cpp $(LIBS)

OPTMem: monitor.h input.h output.h global.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPTMem OPT.cpp $(LIBS) -D WATCH_MEM

Guide: monitor.h input.h output.h global.h guide.cpp
	$(CXX) $(CFLAGS) -o Guide guide.cpp $(LIBS)
.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true	
		-@rm Guide 2> /dev/null || true	
		-@rm Simple SimpleMem 2> /dev/null || true	
		-@rm OPT OPTMem 2> /dev/null || true