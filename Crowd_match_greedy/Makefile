##
#	Makefile for `dna` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++0x -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: Ext TGOA Filter Greedy ExtMem TGOAMem FilterMem GreedyMem OPT OPTMem Pure PureMem Static StaticMem
Ext: monitor.h input.h Extended_Greedy_RT.cpp
	$(CXX) $(CFLAGS) -o Ext Extended_Greedy_RT.cpp $(LIBS)

TGOA: monitor.h input.h TGOA.cpp
	$(CXX) $(CFLAGS) -o TGOA TGOA.cpp $(LIBS)

Filter: monitor.h input.h TGOA_Filter.cpp
	$(CXX) $(CFLAGS) -o Filter TGOA_Filter.cpp $(LIBS)

Greedy: monitor.h input.h TGOA_Greedy.cpp
	$(CXX) $(CFLAGS) -o Greedy TGOA_Greedy.cpp $(LIBS)

ExtMem: monitor.h input.h Extended_Greedy_RT.cpp
	$(CXX) $(CFLAGS) -o ExtMem Extended_Greedy_RT.cpp $(LIBS) -D WATCH_MEM

TGOAMem: monitor.h input.h TGOA.cpp
	$(CXX) $(CFLAGS) -o TGOAMem TGOA.cpp $(LIBS) -D WATCH_MEM

FilterMem: monitor.h input.h TGOA_Filter.cpp
	$(CXX) $(CFLAGS) -o FilterMem TGOA_Filter.cpp $(LIBS) -D WATCH_MEM

GreedyMem: monitor.h input.h TGOA_Greedy.cpp
	$(CXX) $(CFLAGS) -o GreedyMem TGOA_Greedy.cpp $(LIBS) -D WATCH_MEM

OPT: monitor.h input.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPT OPT.cpp $(LIBS)

OPTMem: monitor.h input.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPTMem OPT.cpp $(LIBS) -D WATCH_MEM

Pure: monitor.h input.h Pure_Greedy.cpp
	$(CXX) $(CFLAGS) -o Pure Pure_Greedy.cpp $(LIBS)

PureMem: monitor.h input.h Pure_Greedy.cpp
	$(CXX) $(CFLAGS) -o PureMem Pure_Greedy.cpp $(LIBS) -D WATCH_MEM

Static: monitor.h input.h Static_Greedy.cpp
	$(CXX) $(CFLAGS) -o Static Static_Greedy.cpp $(LIBS)

StaticMem: monitor.h input.h Static_Greedy.cpp
	$(CXX) $(CFLAGS) -o StaticMem Static_Greedy.cpp $(LIBS) -D WATCH_MEM	
	
.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm Ext Ext.g* 2> /dev/null || true	
		-@rm TGOA TGOA.g* 2> /dev/null || true	
		-@rm Filter Filter.g* 2> /dev/null || true	
		-@rm Greedy Greedy.g* 2> /dev/null || true	
		-@rm ExtMem ExtMem.g* 2> /dev/null || true	
		-@rm TGOAMem TGOAMem.g* 2> /dev/null || true	
		-@rm FilterMem FilterMem.g* 2> /dev/null || true	
		-@rm GreedyMem GreedyMem.g* 2> /dev/null || true
		-@rm OPT OPTMem OPT.g* OPTMem.g* 2> /dev/null || true	
		-@rm Pure PureMem Pure.g* PureMem.g* 2> /dev/null || true	
		-@rm Static StaticMem Static.g* StaticMem.g* 2> /dev/null || true
		