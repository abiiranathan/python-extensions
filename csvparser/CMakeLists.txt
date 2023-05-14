
# Create a build directory: mkdir build && cd build
# Generate the build files: cmake ..
# Build the module: cmake --build .
# Install the module (optional): sudo cmake --install .

cmake_minimum_required(VERSION 3.12)
project(csvparser)

# Set the path to pybind11
# Or clone pybind11 from github into project
set(PYBIND11_INCLUDE_DIR "/home/nabiizy/c-extensions/.venv/lib/python3.11/site-packages/pybind11/share/cmake/pybind11")

# Find pybind11 package
find_package(pybind11 REQUIRED PATHS ${PYBIND11_INCLUDE_DIR})

# Add the csvparser module
pybind11_add_module(csvparser csvparser.cpp)

# Set compiler flags
target_compile_options(csvparser PRIVATE
    -std=c++11
    -O3
    -Wall
    -pedantic
)

target_compile_definitions(csvparser PRIVATE VERSION_INFO="0.0.1")

# Install the module
install(TARGETS csvparser
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
)


