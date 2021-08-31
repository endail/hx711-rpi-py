#!/bin/bash

if [ `id -u` -ne 0 ]; then
    echo "Run as root"
    exit 1;
fi

# build and install liblgpio if not found
if ! $(ldconfig -p | grep -q liblgpio); then
    #git clone https://github.com/joan2937/lg
    #cd lg
    #make && make install
    #cd ..
    wget https://abyz.me.uk/lg/lg.zip
    unzip lg.zip
    cd lg
    make
    sudo make install
    cd ..
else
    echo "liblgpio already installed"
fi

# build and install libhx711 if not found
if ! $(ldconfig -p | grep -q libhx711); then
    git clone https://github.com/endail/hx711
    cd hx711
    make && make install
    cd ..
else
    echo "libhx711 already installed"
fi
