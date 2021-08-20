#!/bin/bash

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1;
fi

# build and install libhx711 if not found
if ! $(ldconfig -p | grep -q libhx711); then
    git clone https://github.com/endail/hx711
    cd hx711
    make && make install
    cd ..
fi

git submodule update --init
make all
