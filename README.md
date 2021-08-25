# hx711-rpi-py

Python bindings for [Raspberry Pi HX711 C++ Library](https://github.com/endail/hx711)

**WORK IN PROGRESS...**

- Read from a HX711 using Python
- Use with Raspberry Pi
- Developed and tested with a Raspberry Pi Zero W (should work on other Pis)

## Sample Output

![hx711.gif](hx711.gif)

The .gif above illustrates the output of a [simple Python script](src/test.py) on a Raspberry Pi Zero W where the HX711 chip was operating at 80Hz. Each time the `.weight` function is called, the median of three samples is used.

## Example

```python
from HX711 import *

hx = SimpleHX711(2, 3)

while True:
    print(hx.weight())
```

## Build

```console
# Step 1: clone this repository
git clone https://github.com/endail/hx711-rpi-py
cd hx711-rpi-py

# Step 2: install liblgpio and libhx711 dependencies
sudo ./install-deps

# Step 3: build (this may take some time)
make

# bin directory will contain python module
# eg. HX711.cpython-37m-arm-linux-gnueabihf.so
# import this file into your script
```
