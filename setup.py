import pybind11
from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "point",
        sorted(glob("./*.cpp")),
        include_dirs=[pybind11.get_include()],
        language="c++",
    ),
]

setup(cmdclass={"build_ext": build_ext}, ext_modules=ext_modules)
