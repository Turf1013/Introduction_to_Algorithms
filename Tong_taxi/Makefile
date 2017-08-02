##
#	Makefile for `taxi ridesharing` application
##
CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = --std=c++11 -W -Wall -Wno-sign-compare -O2 -s -pipe -mmmx -msse -msse2 -msse3
TARGET = ./all

all: base judge tshare bb kit zshare bila effg
base: input.h output.h base.cpp monitor.h
	$(CXX) $(CFLAGS) -o base base.cpp $(LIBS)

greedy: input.h output.h greedy.cpp monitor.h
	$(CXX) $(CFLAGS) -o greedy greedy.cpp $(LIBS)

genD: genData.cpp
	$(CXX) $(CFLAGS) -o genD genData.cpp $(LIBS)

tshare: input.h output.h monitor.h TShare.cpp
	$(CXX) $(CFLAGS) -o tshare TShare.cpp $(LIBS)

tshare_dist: input.h output.h monitor.h Tshare_dist.cpp
	$(CXX) $(CFLAGS) -o tshare_dist Tshare_dist.cpp $(LIBS)

tshare_km: input.h output.h monitor.h KM.h Tshare_KM.cpp
	$(CXX) $(CFLAGS) -o tshare_km Tshare_KM.cpp $(LIBS)

zshare: input.h output.h monitor.h ZShare.cpp
	$(CXX) $(CFLAGS) -o zshare ZShare.cpp $(LIBS)

bb: input.h output.h monitor.h BB.cpp
	$(CXX) $(CFLAGS) -o bb BB.cpp $(LIBS)

kit: input.h output.h monitor.h treeNode.h Kinetic.cpp
	$(CXX) $(CFLAGS) -o kit Kinetic.cpp $(LIBS)
	
hot: input.h output.h monitor.h treeNode.h Kinetic_hot.cpp
	$(CXX) $(CFLAGS) -o hot Kinetic_hot.cpp $(LIBS)

hotp: input.h output.h monitor.h treeNode.h Kinetic_hot_v1.cpp
	$(CXX) $(CFLAGS) -o hotp Kinetic_hot_v1.cpp $(LIBS)

judge: input.h judge.cpp
	$(CXX) $(CFLAGS) -o judge judge.cpp $(LIBS)

judges: input.h judge_sumDist.cpp
	$(CXX) $(CFLAGS) -o judges judge_sumDist.cpp $(LIBS)

bila: input.h output.h monitor.h peng_Bilateral.cpp
	$(CXX) $(CFLAGS) -o bila peng_Bilateral.cpp $(LIBS)

effg: input.h output.h monitor.h peng_EfficientGreedy.cpp
	$(CXX) $(CFLAGS) -o effg peng_EfficientGreedy.cpp $(LIBS)

.PHONY: clean 
clean:
		-@rm *.o *.gcno *~ 2> /dev/null || true
		-@rm greedy greedy.g* 2> /dev/null || true	
		-@rm base base.g* 2> /dev/null || true	
		-@rm genD genD.g* 2> /dev/null || true	
		-@rm tshare tshare.g* 2> /dev/null || true	
		-@rm bb bb.g* 2> /dev/null || true
		-@rm kit kit.g* 2> /dev/null || true
		-@rm judge judge.g* judges 2> /dev/null || true
		-@rm hot hotp hotp.g* hot.g* 2> /dev/null || true
		-@rm zshare zshare.g* 2> /dev/null || true
		-@rm bila effg tshare_dist tshare_km 2> /dev/null || true

