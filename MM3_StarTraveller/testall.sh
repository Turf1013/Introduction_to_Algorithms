#!/bin/sh

if [ -z "$1" ]; then
	for i in {1..10}
	do
	   java -jar tester.jar -exec ./star -seed $i
	done
else
	for i in {1..10}	
	do
	   java -jar tester.jar -exec ./$1 -seed $i
	done
fi