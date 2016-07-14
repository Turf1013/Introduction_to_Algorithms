##
#  Makefile for `ternary-search-tree` application
##

CC = gcc
CXX = g++
LIBS = -lrt
CFLAGS = -std=c++11 -Wall

build: stree
stree: ukk_algo.cpp
	$(CXX) $(CFLAGS) -o stree ukk_algo.cpp $(LIBS)

.PHONY: clean
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm stree stree.g* 2> /dev/null || true


