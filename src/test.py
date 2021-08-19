#!/usr/bin/python3
import sys
sys.path.append("../build")

from HX711 import *

hx = SimpleHX711(2, 3, Value(-370), Value(-367471), Rate.HZ_80)

while 1:
	print(hx.read(Options(3)))
