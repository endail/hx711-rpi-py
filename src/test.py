#!/usr/bin/python3

import sys
sys.path.append("../build")

from HX711 import *

hx = SimpleHX711(2, 3, -370, -367471, Rate.HZ_80)

while True:
	print(hx.weight())
