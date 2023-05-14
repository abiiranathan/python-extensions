from setuptools import setup, Extension
import pybind11

# OpenMP requires libomp-dev
extension_mod = Extension(
    "csvparser",
    sources=["csvparser.cpp"],
    include_dirs=[pybind11.get_include()],
    extra_compile_args=[
        "-std=c++11",
        "-O3",
        "-Wall",
        "-pedantic",
    ],
    # extra_link_args=["-fopenmp"],
)

setup(
    name="csvparser",
    version="1.0",
    author="Dr. Abiira Nathan",
    description="A CSV parser implemented in C++",
    ext_modules=[extension_mod],
)
