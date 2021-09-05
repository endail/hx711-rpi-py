#!/usr/bin/env python3

from setuptools import setup, find_packages
from pybind11.setup_helpers import Pybind11Extension

# TODO: get data from pyproject.toml
# https://stackoverflow.com/questions/62362693/how-do-i-read-project-dependencies-from-pyproject-toml-from-my-setup-py-to-avoi

setup(
    name="hx711-rpi-pi",
    version="0.0.1",
    author="Daniel Robertson",
    author_email="52652357+endail@users.noreply.github.com",
    url="https://github.com/endail/hx711-rpi-py",
    description="Python bindings for Raspberry Pi HX711 C++ Library",
    long_description="",
    license="MIT",
    package_dir={"": "src"},
    packages=find_packages("src"),
    ext_modules=[
        Pybind11Extension(
            name="HX711",
            sources=[
                "src/bindings.cpp"
            ],
            libraries=[
                "lgpio",
                "hx711"
            ]
        )
    ]
)
