##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: base greedy grid
base: GraphDrawing_base_v0.cpp monitor.h
	$(CXX) $(CFLAGS) -o base GraphDrawing_base_v0.cpp $(LIBS)

greedy: GraphDrawing_greedy_v0.cpp monitor.h
	$(CXX) $(CFLAGS) -o greedy GraphDrawing_greedy_v0.cpp $(LIBS)

grid: GraphDrawing_grid_v0.cpp monitor.h
	$(CXX) $(CFLAGS) -o grid GraphDrawing_grid_v0.cpp $(LIBS)

raw: GraphDrawing.cpp monitor.h
	$(CXX) $(CFLAGS) -o raw GraphDrawing.cpp $(LIBS)


.PHONY: clean test
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedy.g* 2> /dev/null || true	
		-@rm base base.g* 2> /dev/null || true	
		-@rm raw raw.g* 2> /dev/null || true	

test: build
		java -jar tester.jar -exec ./base -seed 1 -vis -delay 1000
		@echo

