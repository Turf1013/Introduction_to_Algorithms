##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: Ext TGOA Filter Greedy testMem testClk
Ext: monitor.h input.h Extended_Greedy_RT.cpp
	$(CXX) $(CFLAGS) -o Ext Extended_Greedy_RT.cpp $(LIBS)

TGOA: monitor.h input.h TGOA.cpp
	$(CXX) $(CFLAGS) -o TGOA TGOA.cpp $(LIBS)

Filter: monitor.h input.h TGOA_Filter.cpp
	$(CXX) $(CFLAGS) -o Filter TGOA_Filter.cpp $(LIBS)

Greedy: monitor.h input.h TGOA_Greedy.cpp
	$(CXX) $(CFLAGS) -o Greedy TGOA_Greedy.cpp $(LIBS)

testMem: testMemory.cpp monitor.h input.h Extended_Greedy_RT.cpp 
	$(CXX) $(CFLAGS) -o Ext Extended_Greedy_RT.cpp $(LIBS) -D WATCH_MEM
	$(CXX) $(CFLAGS) -o testMem testMemory.cpp $(LIBS)

testClk: testClock.cpp monitor.h input.h Extended_Greedy_RT.cpp
	$(CXX) $(CFLAGS) -o Ext Extended_Greedy_RT.cpp $(LIBS)	
	$(CXX) $(CFLAGS) -o testClk testClock.cpp $(LIBS)	

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm Ext Ext.g* 2> /dev/null || true	
		-@rm TGOA TGOA.g* 2> /dev/null || true	
		-@rm Filter Filter.g* 2> /dev/null || true	
		-@rm Greedy Greedy.g* 2> /dev/null || true	
		-@rm testMem testClk* 2> /dev/null || true	
