##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: greedy greedyM
greedy: monitor.h input.h output.h global.h greedy.cpp
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS)
	
greedyM: monitor.h input.h output.h global.h greedy.cpp
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS) -D WATCH_MEM


.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedyM 2> /dev/null || true