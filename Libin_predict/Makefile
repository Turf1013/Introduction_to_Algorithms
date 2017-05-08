##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: Simple SimpleMem OPT OPTMem Guide Polar PolarMem
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

Polar: monitor.h input.h output.h Polar.cpp
	$(CXX) $(CFLAGS) -o Polar Polar.cpp $(LIBS)

PolarMem: monitor.h input.h output.h Polar.cpp
	$(CXX) $(CFLAGS) -o PolarMem Polar.cpp $(LIBS) -D WATCH_MEM

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true	
		-@rm Guide 2> /dev/null || true	
		-@rm Simple SimpleMem 2> /dev/null || true	
		-@rm OPT OPTMem 2> /dev/null || true
		-@rm Polar PolarMem 2> /dev/null || true