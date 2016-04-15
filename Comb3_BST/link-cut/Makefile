##
#  Makefile for `ternary-search-tree` application
##

CC = gcc
LIBS = -lrt
CFLAGS = -Wall

build: lincut
lincut: link_cut.o
		$(CC) $(CFLAGS) -o lincut link_cut.o log.o $(LIBS) 
log.o: log.c log.h
		$(CC) $(CFLAGS) -c log.c $(LIBS) 
link_cut.o: link_cut.c link_cut.h log.h
		$(CC) $(CFLAGS) -c link_cut.c $(LIBS) 

.PHONY: clean test debug
clean:
		-@rm *.o *.gcno 2> /dev/null || true
		-@rm lincut lincut.g* 2> /dev/null || true

optimized: CFLAGS += -O3 -ftree-vectorize
optimized: build

test: build
		./lincut data.in
		@echo

debug: CFLAGS += -g -fprofile-arcs -ftest-coverage
debug: build

