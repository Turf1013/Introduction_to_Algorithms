##
#	Makefile for `SIGMOD Qiyu` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: cnt sssp
cnt: calcDemand.cpp
	$(CXX) $(CFLAGS) -o cnt calcDemand.cpp $(LIBS)

cnt0: calcDemand_v0.cpp
	$(CXX) $(CFLAGS) -o cnt0 calcDemand_v0.cpp $(LIBS)
	
sssp: sssp.cpp
	$(CXX) $(CFLAGS) -o sssp sssp.cpp $(LIBS)

.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm cnt cnt0 sssp 2> /dev/null || true
		-@rm greedy base 2> /dev/null || true
