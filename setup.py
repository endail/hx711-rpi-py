from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pybind11 import get_cmake_dir

import sys

__version__ = "0.0.1"

ext_modules = [
    Pybind11Extension(
		"HX711",
        ["src/bindings.cpp"])
]

setup(
    name="HX711",
    version=__version__,
    author="Daniel Robertson",
    author_email="52652357+endail@users.noreply.github.com",
    url="https://github.com/endail/hx711-rpi-py",
    description="Python bindings for Raspberry Pi HX711 C++ Library",
    long_description="",
    ext_modules=ext_modules,
    extras_require={"test": "pytest"},
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
