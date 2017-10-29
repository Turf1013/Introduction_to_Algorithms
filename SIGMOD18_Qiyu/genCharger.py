#!/usr/bin/env python
import os
import sys
import commands

class constForCharger:
	chargers = [
		[50, 1000],
		[100,  2300],
		[1230, 26000],
		[2780, 60000],
		[4760, 130000],
	]

class CFC(constForCharger):
    pass

def genChargerData(desFileName):
    with open(desFileName, "w") as fout:
        chargerN = len(CFC.chargers)
        fout.write("%d\n" % (chargerN))
        for item in CFC.chargers:
            power,price = item[:2]
            fout.write("%d %d\n" % (power, price))

def exp0():
    desFileName = "chargers.txt"
    genChargerData(desFileName)


if __name__ == "__main__":
    exp0()
