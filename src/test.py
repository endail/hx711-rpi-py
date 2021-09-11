from HX711 import SimpleHX711, Rate

with SimpleHX711(2, 3, -370, -367471, Rate.HZ_80) as hx:
    while True:
        print(hx.weight())
