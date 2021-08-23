#!/bin/bash

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1;
fi

# build and install liblgpio if not found
if ! $(ldconfig -p | grep -q liblgpio); then
    git clone --depth 1 --branch v0.1 https://github.com/joan2937/lg
    cd lg
    make && make install
    cd ..
fi

# build and install libhx711 if not found
if ! $(ldconfig -p | grep -q libhx711); then
    git clone https://github.com/endail/hx711
    cd hx711
    make && make install
    cd ..
fi
