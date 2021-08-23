from setuptools import setup, find_packages, Extension
from pybind11.setup_helpers import Pybind11Extension

setup(
    ext_modules=[
        Pybind11Extension(
            "HX711",
            ["src/bindings.cpp"],
            libraries=[
                "hx711",
                "lgpio"
            ]
        )
    ]
)
