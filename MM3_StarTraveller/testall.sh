#!/bin/sh

if [ -z "$1" ]; then
	for i in {1..10}
	do
	   java -jar tester.jar -exec ./star -seed $i -save star$i.png
	done
else
	for i in {1..10}	
	do
	   java -jar tester.jar -exec ./$1 -seed $i -save base$i.png
	done
fi
