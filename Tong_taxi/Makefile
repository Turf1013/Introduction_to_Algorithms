##
#	Makefile for `taxi ridesharing` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: base judge tshare bb kit
base: input.h output.h base.cpp monitor.h
	$(CXX) $(CFLAGS) -o base base.cpp $(LIBS)

greedy: input.h output.h greedy.cpp monitor.h
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS)

genD: genData.cpp
	$(CXX) $(CFLAGS) -o genD genData.cpp $(LIBS)

tshare: input.h output.h monitor.h TShare.cpp
	$(CXX) $(CFLAGS) -o tshare TShare.cpp $(LIBS)

bb: input.h output.h monitor.h BB.cpp
	$(CXX) $(CFLAGS) -o bb BB.cpp $(LIBS)

kit: input.h output.h monitor.h treeNode.h Kinetic.cpp
	$(CXX) $(CFLAGS) -o kit Kinetic.cpp $(LIBS)

judge: input.h judge.cpp
	$(CXX) $(CFLAGS) -o judge judge.cpp $(LIBS)


.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedy.g* 2> /dev/null || true	
		-@rm base base.g* 2> /dev/null || true	
		-@rm genD genD.g* 2> /dev/null || true	
		-@rm tshare tshare.g* 2> /dev/null || true	
		-@rm bb bb.g* 2> /dev/null || true
		-@rm kit kit.g* 2> /dev/null || true
		-@rm judge judge.g* 2> /dev/null || true

