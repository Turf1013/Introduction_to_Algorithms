#!/usr/bin/env python
import os
import sys
import commands

class constForCharger:
    chargers = [
        [7.3, 10],
        [16.5, 12],
        [50, 15],
        [120, 30],
    ]

class CFC(constForCharger):
    pass

def genChargerData(desFileName):
    with open(desFileName, "w") as fout:
        chargerN = len(CFC.chargers)
        fout.write("%d\n" % (chargerN))
        for item in CFC.chargers:
            power,price = item[:2]
            fout.write("%.02f %d\n" % (1.0/power, price))

def exp0():
    desFileName = "chargers.txt"
    genChargerData(desFileName)


if __name__ == "__main__":
    exp0()
