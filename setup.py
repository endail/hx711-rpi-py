# coding: utf-8
from setuptools import setup, find_packages, Extension
from pybind11.setup_helpers import Pybind11Extension

__version__ = "0.0.1"

setup(
    name="HX711",
    version=__version__,
    author="Daniel Robertson",
    author_email="52652357+endail@users.noreply.github.com",
    url="https://github.com/endail/hx711-rpi-py",
    description="Python bindings for Raspberry Pi HX711 C++ Library",
    long_description="",
    zip_safe=False,
    ext_modules=[

        Pybind11Extension(
            "HX711",
            ["src/bindings.cpp"],
            libraries=[
                "hx711",
                "lgpio"
            ]
        )

#        Extension(
#            name="HX711",
#            sources=[
#                "src/bindings.cpp"
#            ],
#            libraries=[
#                "hx711",
#                "lgpio"
#            ]
#        )
        
    ]
)
