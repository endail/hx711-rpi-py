# Raspberry Pi HX711 Python Bindings

[![Upload to PyPI](https://github.com/endail/hx711-rpi-py/actions/workflows/build_and_upload.yml/badge.svg)](https://github.com/endail/hx711-rpi-py/actions/workflows/build_and_upload.yml) [![Downloads](https://pepy.tech/badge/hx711-rpi-py)](https://pepy.tech/project/hx711-rpi-py)

Python bindings for [Raspberry Pi HX711 C++ Library](https://github.com/endail/hx711)

- Use with Raspberry Pi
- Read from a HX711 using Python
- Code tested inside [virtual Raspberry Pi Zero/3/4 environments](.github/workflows/build_and_upload.yml) on GitHub and builds automatically uploaded to PyPI
- This repo automatically rebuilds when the C++ library is updated

## Sample Output

![hx711.gif](hx711.gif)

The .gif above illustrates the output of a [simple Python script](src/test.py) on a Raspberry Pi Zero W where the HX711 chip was operating at 80Hz. In this example, each time the `.weight` function is called the median of three samples was used to calculate the weight in grams.

## Examples

```python
from HX711 import *

# create a SimpleHX711 object using GPIO pin 2 as the data pin,
# GPIO pin 3 as the clock pin, -370 as the reference unit, and
# -367471 as the offset
with SimpleHX711(2, 3, -370, -367471) as hx:

  # set the scale to output weights in ounces
  hx.setUnit(Mass.Unit.OZ)

<<<<<<< HEAD
    # zero the scale
    hx.zero()

    # constantly output weights using the median of 35 samples
    while True:
        print(hx.weight(35)) #eg. 1.08 oz
=======
  # constantly output weights using the median of 35 samples
  while True:
    print(hx.weight(35)) #eg. 1.08 oz
>>>>>>> b119c828c604d64e70fe69c758ab81849f08071a
```

### Alternative Syntax (w/out `with`)

```python
from HX711 import *
from datetime import timedelta

hx = SimpleHX711(2, 3, -370, -367471)
hx.setUnit(Mass.Unit.OZ)
while True:
    print(hx.weight(35))
```

Keep in mind that calling `.weight()` will return a `Mass` object, but you can do the following:

```python
# set the scale to output weights in ounces
hx.setUnit(Mass.Unit.OZ)

# obtain a median reading from 35 samples as a Mass object in ounces
m = hx.weight(35)

# number in ounces
num = float(m) # eg. 1.08

# string representation of the Mass
s = str(m) # eg. 1.08 oz

# print the Mass object
print(m) # eg. 1.08 oz

# change the unit to grams
m.setUnit(Mass.Unit.G)
grams_as_str = str(m) # eg. 30.62 g

# or obtain a new Mass object
m2 = m.convertTo(Mass.Unit.KG)
kgs_as_str = str(m2) # eg. 0.031 kg
```

The list of different `Mass.Unit`s can be viewed [here](https://github.com/endail/hx711#mass).

### Time-Based Sampling

You can use [`datetime.timedelta`](https://docs.python.org/3/library/datetime.html#timedelta-objects) to obtain as many samples as possible within the time period.

```python
from HX711 import *
from datetime import timedelta

with SimpleHX711(2, 3, -370, -367471) as hx:
    while True:
        # eg. obtain as many samples as possible within 1 second
        print(hx.weight(timedelta(seconds=1)))
```

### Options

`.weight()`, `.zero()`, and `.read()` can all take an `Options` parameter. You can use this to fine tune how you want the scale to behave.

```python

# zero the scale by using the average value of all samples obtained within 1 second
hx.zero(Options(
    stratType=StrategyType.Time,
    readType=ReadType.Average,
    timeout=timedelta(seconds=1)))

# obtain a raw value from the scale using the median of 100 samples
num = hx.read(Options(
    stratType=StrategyType.Samples,
    readType=ReadType.Median,
    samples=100))

# obtain a Mass object using the median of three samples
# all four statements below are equivalent
m = hx.weight()
m = hx.weight(3)
m = hx.weight(Options())
m = hx.weight(Options(
    stratType=StrategyType.Samples,
    readType=ReadType.Median
    samples=3))
```

## Install

1. Install [libhx711](https://github.com/endail/hx711)

2. `pip3 install --upgrade hx711-rpi-py`

## Calibrate

There is a Python script in the `src` directory you can use to calibrate your load cell and obtain the reference unit and offset values referred to above. The simplest way to use it after installing `hx711-rpi-py` is as follows:

```console
pi@raspberrypi:~ $ wget https://github.com/endail/hx711-rpi-py/blob/master/src/calibrate.py
pi@raspberrypi:~ $ python3 calibrate.py
```

## Documentation

As the Python code relies upon the [underlying C++ library](https://github.com/endail/hx711#documentation), the documentation is identical. However, not all of the code is exposed to Python. An example is the [Utility class](https://github.com/endail/hx711/blob/master/include/Utility.h), which is only meant for use within the C++ library. You can check precisely which functionality is accessible through Python in the [bindings.cpp file](src/bindings.cpp).
