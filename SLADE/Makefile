##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: greedy base opq opqe opqe2
sgreedy: greedy_sky.cpp
	$(CXX) $(CFLAGS) -o sgreedy greedy_sky.cpp $(LIBS)

sopq: opq_sky.cpp
	$(CXX) $(CFLAGS) -o sopq opq_sky.cpp $(LIBS)

sopqe: opqe_sky.cpp
	$(CXX) $(CFLAGS) -o sopqe opqe_sky.cpp $(LIBS)

base: monitor.h input.h output.h global.h baseline.cpp
	$(CXX) $(CFLAGS) -o base baseline.cpp $(LIBS) -lglpk

baseM: monitor.h input.h output.h global.h baseline.cpp
	$(CXX) $(CFLAGS) -o baseM baseline.cpp $(LIBS) -lglpk -D WATCH_MEM

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

opqe2: monitor.h input.h output.h global.h opqe2.cpp
	$(CXX) $(CFLAGS) -o opqe2 opqe2.cpp $(LIBS)

opqeM: monitor.h input.h output.h global.h opqe.cpp
	$(CXX) $(CFLAGS) -o opqeM opqe.cpp $(LIBS) -D WATCH_MEM

.PHONY: clean
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedyM opq opqM opqe opqe2 opqeM base baseM 2> /dev/null || true
		-@rm sopq sopqe sgreedy 2> /dev/null || true
