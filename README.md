# cz5test

A simple test of z5 wrapped to work with C.

This takes the example C++ `main` file found on the `z5py` [repository](https://github.com/constantinpape/z5),
which can be seen in the `main.cpp` file.

The point of this repository is to demonstrate:

1. how to build and run the `main.cpp` C++ file, using the C++ `z5` API
2. how to wrap the `z5` C++ code (that is necessary to execute the `main.cpp` program) in a C header file
3. how to build and run the `main.c` C file, using the C/C++ `z5` wrapper
