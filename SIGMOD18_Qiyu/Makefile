##
#	Makefile for `SIGMOD Qiyu` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3 -mcmodel=medium

all: input.o global.o base ibase bao ibao sbao isbao
prepareData: prepareData.cpp
	$(CXX) $(CFLAGS) -o prepareData prepareData.cpp $(LIBS)

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

ibao: iBoundAndOptimize.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o ibao input.o global.o iBoundAndOptimize.cpp $(LIBS)

base: baseline.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o base input.o global.o baseline.cpp $(LIBS)

ibase: ibaseline.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o ibase input.o global.o ibaseline.cpp $(LIBS)

sbao: subgraph_bao.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o sbao input.o global.o subgraph_bao.cpp $(LIBS)

isbao: subgraph_ibao.cpp input.h input.cpp global.h global.cpp input.o global.o
	$(CXX) $(CFLAGS) -o isbao input.o global.o subgraph_ibao.cpp $(LIBS)

voroni: voroni.cpp voroni.h
	$(CXX) $(CFLAGS) -o voroni voroni.cpp $(LIBS)
	
.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm cnt cnt0 sssp 2> /dev/null || true
		-@rm greedy ibase base bao ibao sbao isbao 2> /dev/null || true
