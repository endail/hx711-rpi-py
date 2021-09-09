from HX711 import SimpleHX711, Rate

hx = SimpleHX711(2, 3, -370, -367471, Rate.HZ_80)

while True:
	print(hx.weight())
