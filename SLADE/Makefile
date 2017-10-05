##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: greedy greedyM opq opqM
greedy: monitor.h input.h output.h global.h greedy.cpp
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS)
	
greedyM: monitor.h input.h output.h global.h greedy.cpp
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS) -D WATCH_MEM

opq: monitor.h input.h output.h global.h opq.cpp
	$(CXX) $(CFLAGS) -o opq opq.cpp $(LIBS)
	
opqM: monitor.h input.h output.h global.h opq.cpp
	$(CXX) $(CFLAGS) -o opqM opq.cpp $(LIBS) -D WATCH_MEM
	
opqe: monitor.h input.h output.h global.h opqe.cpp
	$(CXX) $(CFLAGS) -o opqe opqe.cpp $(LIBS)
	
opqeM: monitor.h input.h output.h global.h opqe.cpp
	$(CXX) $(CFLAGS) -o opqeM opqe.cpp $(LIBS) -D WATCH_MEM
	
.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedyM opq opqM 2> /dev/null || true