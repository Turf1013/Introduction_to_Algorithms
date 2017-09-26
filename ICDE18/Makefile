##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: LRF offline PR LAF LAFM AAM AAMM MCF MCFM RR RRM
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

LGF: monitor.h input.h output.h global.h LGF.cpp
	$(CXX) $(CFLAGS) -o LGF LGF.cpp $(LIBS)

LRFM: monitor.h input.h output.h global.h LRF.cpp
	$(CXX) $(CFLAGS) -o LRFM LRF.cpp $(LIBS) -D WATCH_MEM

offline: monitor.h input.h output.h global.h offline_fast.cpp
	$(CXX) $(CFLAGS) -o offline offline_fast.cpp $(LIBS)
	
SSPA: monitor.h input.h output.h global.h sspa.cpp
	$(CXX) $(CFLAGS) -o SSPA sspa.cpp $(LIBS)
	
SSPAM: monitor.h input.h output.h global.h sspa.cpp
	$(CXX) $(CFLAGS) -o SSPAM sspa.cpp $(LIBS) -D WATCH_MEM

offlineM: monitor.h input.h output.h global.h offline_fast.cpp
	$(CXX) $(CFLAGS) -o offlineM offline_fast.cpp $(LIBS) -D WATCH_MEM

MCF: monitor.h input.h output.h global.h offline.cpp
	$(CXX) $(CFLAGS) -o MCF offline.cpp $(LIBS)

MCFM: monitor.h input.h output.h global.h offline.cpp
	$(CXX) $(CFLAGS) -o MCFM offline.cpp $(LIBS) -D WATCH_MEM

LAF: monitor.h input.h output.h global.h LAF.cpp
	$(CXX) $(CFLAGS) -o LAF LAF.cpp $(LIBS)

LAFM: monitor.h input.h output.h global.h LAF.cpp
	$(CXX) $(CFLAGS) -o LAFM LAF.cpp $(LIBS) -D WATCH_MEM

AAM: monitor.h input.h output.h global.h AAM.cpp
	$(CXX) $(CFLAGS) -o AAM AAM.cpp $(LIBS)

AAMM: monitor.h input.h output.h global.h AAM.cpp
	$(CXX) $(CFLAGS) -o AAMM AAM.cpp $(LIBS) -D WATCH_MEM

.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm RR LRF OLRF offline PR 2> /dev/null || true
		-@rm RRM LUF LRFM OLRFM offlineM PRM 2> /dev/null || true
		-@rm LGF AAM AAMM MCF MCFM LAF LAFM 2> /dev/null || true
		-@rm SSPA SSPAM 2> /dev/null || true