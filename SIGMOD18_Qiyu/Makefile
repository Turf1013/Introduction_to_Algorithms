##
#	Makefile for `SIGMOD Qiyu` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: cnt sssp input.o global.o bao base
cnt: calcDemand.cpp
	$(CXX) $(CFLAGS) -o cnt calcDemand.cpp $(LIBS)

cnt0: calcDemand_v0.cpp
	$(CXX) $(CFLAGS) -o cnt0 calcDemand_v0.cpp $(LIBS)

sssp: sssp.cpp
	$(CXX) $(CFLAGS) -o sssp sssp.cpp $(LIBS)

global.o: global.h global.cpp
	$(CXX) $(CFLAGS) -c global.cpp $(LIBS)

input.o: input.h input.cpp global.h
	$(CXX) $(CFLAGS) -c input.cpp $(LIBS)

bao: boundAndOptimize.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o bao input.o global.o boundAndOptimize.cpp $(LIBS)

base: baseline.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o base input.o global.o baseline.cpp $(LIBS)

ibase: ibaseline.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o ibase input.o global.o ibaseline.cpp $(LIBS)


.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm cnt cnt0 sssp 2> /dev/null || true
		-@rm greedy ibase base bao 2> /dev/null || true
