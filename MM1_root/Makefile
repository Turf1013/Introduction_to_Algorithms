##
#	Makefile for `CutTheRoots` application
##

CXX = g++
LIBS = -lrt
CFLAGS = -Wall

build: CutTheRoots
CutTheRoots: CutTheRoots_v3.cpp
	$(CXX)	$(CFLAGS) -o CutTheRoots CutTheRoots.cpp $(LIBS)

.PHONY: clean test
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm CutTheRoots CutTheRoots.g* 2> /dev/null || true	

test: build
		java -jar tester.jar -exec ./CutTheRoots -seed 1 -vis -save output.png
		@echo
