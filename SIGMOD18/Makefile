##
#	Makefile for `taxi ridesharing` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: gi
gi: input.h output.h greedyInsert.cpp monitor.h
	$(CXX) $(CFLAGS) -o gi greedyInsert.cpp $(LIBS)

giM: input.h output.h greedyInsert.cpp monitor.h
	$(CXX) $(CFLAGS) -o gi greedyInsert.cpp $(LIBS) -D WATCH_MEM

fifo: output.h fifo.cpp monitor.h
	$(CXX) $(CFLAGS) -o fifo fifo.cpp $(LIBS)

fifoM: output.h fifo.cpp monitor.h
	$(CXX) $(CFLAGS) -o fifoM fifo.cpp $(LIBS)	
	
.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm gi giM fifo fifoM 2> /dev/null || true
