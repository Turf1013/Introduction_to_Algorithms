##
#	Makefile for `Libin_predict` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: Simple SimpleMem OPT OPTMem Guide Polar PolarMem Hung GuideH Dinic
Simple: monitor.h input.h output.h global.h simpleGreedy.cpp
	$(CXX) $(CFLAGS) -o Simple simpleGreedy.cpp $(LIBS)

SimpleMem: monitor.h input.h output.h global.h simpleGreedy.cpp
	$(CXX) $(CFLAGS) -o SimpleMem simpleGreedy.cpp $(LIBS) -D WATCH_MEM

OPT: monitor.h input.h output.h global.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPT OPT.cpp $(LIBS)

Dinic: monitor.h input.h output.h global.h OPT_Dinic.cpp
	$(CXX) $(CFLAGS) -o Dinic OPT_Dinic.cpp $(LIBS)

DinicF: monitor.h input.h output.h global.h OPT_Dinic_fast.cpp
	$(CXX) $(CFLAGS) -o DinicF OPT_Dinic_fast.cpp $(LIBS)

DinicFMem: monitor.h input.h output.h global.h OPT_Dinic_fast.cpp
	$(CXX) $(CFLAGS) -o DinicFMem OPT_Dinic_fast.cpp $(LIBS) -D WATCH_MEM

Hung: monitor.h input.h output.h global.h OPT_hungarian.cpp
	$(CXX) $(CFLAGS) -o Hung OPT_hungarian.cpp $(LIBS)

HungMem: monitor.h input.h output.h global.h OPT_hungarian.cpp
	$(CXX) $(CFLAGS) -o HungMem OPT_hungarian.cpp $(LIBS) -D WATCH_MEM

OPTMem: monitor.h input.h output.h global.h OPT.cpp
	$(CXX) $(CFLAGS) -o OPTMem OPT.cpp $(LIBS) -D WATCH_MEM

Guide: monitor.h input.h output.h global.h guide.cpp
	$(CXX) $(CFLAGS) -o Guide guide.cpp $(LIBS)

GuideH: monitor.h input.h output.h global.h guide_hung.cpp
	$(CXX) $(CFLAGS) -o GuideH guide_hung.cpp $(LIBS)

GuideD: monitor.h input.h output.h global.h guide_dinic.cpp
	$(CXX) $(CFLAGS) -o GuideD guide_dinic.cpp $(LIBS)

GuideDF: monitor.h input.h output.h global.h guide_dinic_fast.cpp
	$(CXX) $(CFLAGS) -o GuideDF guide_dinic_fast.cpp $(LIBS)

GuideDFMem: monitor.h input.h output.h global.h guide_dinic_fast.cpp
	$(CXX) $(CFLAGS) -o GuideDFMem guide_dinic_fast.cpp $(LIBS) -D WATCH_MEM

Polar: monitor.h input.h output.h global.h Polar.cpp
	$(CXX) $(CFLAGS) -o Polar Polar.cpp $(LIBS)

PolarMem: monitor.h input.h output.h global.h Polar.cpp
	$(CXX) $(CFLAGS) -o PolarMem Polar.cpp $(LIBS) -D WATCH_MEM

Sha: monitor.h input.h output.h global.h Shahabi.cpp
	$(CXX) $(CFLAGS) -o Sha Shahabi.cpp $(LIBS)

ShaMem: monitor.h input.h output.h global.h Shahabi.cpp
	$(CXX) $(CFLAGS) -o ShaMem Shahabi.cpp $(LIBS) -D WATCH_MEM

Lig: monitor.h Libin_SimpleG.cpp
	$(CXX) $(CFLAGS) -o Lig Libin_SimpleG.cpp $(LIBS)

Lip: monitor.h Libin_Polar.cpp
	$(CXX) $(CFLAGS) -o Lip Libin_Polar.cpp $(LIBS)

Edge: input.h global.h calcEdge.cpp
	$(CXX) $(CFLAGS) -o Edge calcEdge.cpp $(LIBS)

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true	
		-@rm Guide 2> /dev/null || true	
		-@rm Simple SimpleMem 2> /dev/null || true	
		-@rm OPT OPTMem 2> /dev/null || true
		-@rm Polar PolarMem 2> /dev/null || true
		-@rm Lig 2> /dev/null || true
