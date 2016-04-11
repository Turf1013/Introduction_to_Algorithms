##
#  Makefile for `ternary-search-tree` application
##

CC = gcc
LIBS = -lrt
CFLAGS = -Wall

build: rst
rst: log.o rs_tst.o 
		$(CC) $(CFLAGS) -o tst rs_tst.o log.o $(LIBS) 
log.o: log.c log.h
		$(CC) $(CFLAGS) -c log.c $(LIBS) 
rs_tst.o: rs_tst.c rs_tst.h log.h
		$(CC) $(CFLAGS) -c rs_tst.c $(LIBS) 

.PHONY: clean test debug
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm tst tst.g* 2> /dev/null || true

optimized: CFLAGS += -O3 -ftree-vectorize
optimized: build

test: build
		./tst data.in
		@echo

debug: CFLAGS += -g -fprofile-arcs -ftest-coverage
debug: build

