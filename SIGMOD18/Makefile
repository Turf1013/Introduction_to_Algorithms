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
	$(CXX) $(CFLAGS) -o fifoM fifo.cpp $(LIBS) -D WATCH_MEM

sjf: output.h sjf.cpp monitor.h
	$(CXX) $(CFLAGS) -o sjf sjf.cpp $(LIBS)

sjfM: output.h fifo.cpp monitor.h
	$(CXX) $(CFLAGS) -o sjfM sjf.cpp $(LIBS) -D WATCH_MEM

hst: input.h HST.h HST.cpp monitor.h
	$(CXX) $(CFLAGS) -o hst HST.cpp $(LIBS)

.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm hst gi giM fifo fifoM sjf sjfM 2> /dev/null || true
