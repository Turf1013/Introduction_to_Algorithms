##
#	Makefile for `taxi ridesharing` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: base greedy grid
base: base_v0.cpp monitor.h
	$(CXX) $(CFLAGS) -o base base_v0.cpp $(LIBS)

greedy: greedy_v0.cpp monitor.h
	$(CXX) $(CFLAGS) -o greedy greedy_v0.cpp $(LIBS)

genD: genData.cpp
	$(CXX) $(CFLAGS) -o genD genData.cpp $(LIBS)

tshare: input.h output.h monitor.h TShare.cpp
	$(CXX) $(CFLAGS) -o tshare TShare.cpp $(LIBS)

bb: input.h output.h monitor.h BB.cpp
	$(CXX) $(CFLAGS) -o bb BB.cpp $(LIBS)

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedy.g* 2> /dev/null || true	
		-@rm base base.g* 2> /dev/null || true	
		-@rm genD genD.g* 2> /dev/null || true	
		-@rm tshare tshare.g* 2> /dev/null || true	
		-@rm bb bb.g* 2> /dev/null || true

