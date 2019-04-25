# cz5test

A simple test of z5 wrapped to work with C.

This takes the example C++ `main.cpp` file _example_ found in the `README.md` of
the `z5py` [repository](https://github.com/constantinpape/z5), which can be seen
in the `main.cpp` file of this repository.

The point of this repository is to demonstrate:

1. how to build and run the `main.cpp` C++ file, using the C++ `z5` API
2. how to wrap the `z5` C++ code (that is necessary to execute the `main.cpp`
   program) in a C header file
3. how to build and run the `main.c` C file, using the C/C++ `z5` wrapper

## Environment Setup

To create the environment you need to build and run, you need to install the
conda environment using the _export_ file `environment.txt`, as follows:

```bash
conda create --name cz5test --file environment.txt
```

## Building

To build, you need to activate the conda environment and use the conda compilers.
Assuming you are in the `cz5test` repository top-level directory, do the following:

```bash
# Activate conda environment
conda activate cz5test

# Create the build directory
mkdir build
cd build

# Configure the build with cmake
cmake ..

# Make the `main.cpp` executable and run it (test)
make test_cpp
./test_cpp

# Make the `main.c` executable and run it (test)
# CURRENTLY THIS DOESN'T WORK!!!  This is the goal!
make test_c
./test_c
```