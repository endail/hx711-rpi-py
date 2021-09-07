#!/usr/bin/env python3

import pathlib
from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup, find_packages

here = pathlib.Path(__file__).parent.resolve()

setup(
    name="hx711-rpi-py",
    version="0.1.0",
    license="MIT",
    description="Python bindings for Raspberry Pi HX711 C++ Library",
    long_description=(here / "README.md").read_text(encoding="utf-8"),
    long_description_content_type="text/markdown",
    url="https://github.com/endail/hx711-rpi-py",
    author="Daniel Robertson",
    author_email="52652357+endail@users.noreply.github.com",
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3 :: Only",
        "Topic :: Software Development",
        "Topic :: Home Automation",
        "Topic :: Scientific/Engineering",
        "Topic :: System :: Hardware :: Hardware Drivers",
        "Operating System :: POSIX :: Linux"
    ],
    keywords = "hx711, raspberry-pi, sensor, weight, load-cell",
    package_dir={"": "src"},
    packages=find_packages(where="src"),
    python_requires=">=3.6, <4",
    install_requires=[],
    extras_require={},
    package_data={},
    data_files=[],
    entry_points={},
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
