##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: RR LRF OLRF offline PR
RR: monitor.h input.h output.h global.h RR.cpp
	$(CXX) $(CFLAGS) -o RR RR.cpp $(LIBS)

RRM: monitor.h input.h output.h global.h RR.cpp
	$(CXX) $(CFLAGS) -o RRM RR.cpp $(LIBS) -D WATCH_MEM

PR: monitor.h input.h output.h global.h PR.cpp
	$(CXX) $(CFLAGS) -o PR PR.cpp $(LIBS)

PRM: monitor.h input.h output.h global.h PR.cpp
	$(CXX) $(CFLAGS) -o PRM PR.cpp $(LIBS) -D WATCH_MEM	
	
LRF: monitor.h input.h output.h global.h LRF.cpp
	$(CXX) $(CFLAGS) -o LRF LRF.cpp $(LIBS)

LRFM: monitor.h input.h output.h global.h LRF.cpp
	$(CXX) $(CFLAGS) -o LRFM LRF.cpp $(LIBS) -D WATCH_MEM

OLRF: monitor.h input.h output.h global.h OLRF.cpp
	$(CXX) $(CFLAGS) -o OLRF OLRF.cpp $(LIBS)

OLRFM: monitor.h input.h output.h global.h OLRF.cpp
	$(CXX) $(CFLAGS) -o OLRFM OLRF.cpp $(LIBS) -D WATCH_MEM	
	
offline: monitor.h input.h output.h global.h offline.cpp
	$(CXX) $(CFLAGS) -o offline offline.cpp $(LIBS)

offlineM: monitor.h input.h output.h global.h offline.cpp
	$(CXX) $(CFLAGS) -o offlineM offline.cpp $(LIBS) -D WATCH_MEM 	

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true	
		-@rm RR LRF OLRF offline PR 2> /dev/null || true	
		-@rm RRM LRFM OLRFM offlineM PRM 2> /dev/null || true	
