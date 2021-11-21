[![myoptional](https://github.com/rkollataj/myoptional/actions/workflows/buil.yml/badge.svg)](https://github.com/rkollataj/myoptional/actions/workflows/buil.yml) [![Doxygen](https://img.shields.io/badge/Doxygen-master-blue.svg)](https://rkollataj.github.io/myoptional/)

# myoptional
myoptional is a header-only library. It implements a class that enables to hold a user defined class or status code.

## Building and Running
### Linux and macOS
```
git clone https://github.com/rkollataj/myoptional.git
cmake -E make_directory myoptional/build
cd myoptional/build
git submodule update --init
cmake .. 
make -j8
ctest
```
### Windows
```
git clone https://github.com/rkollataj/myoptional.git
cmake -E make_directory myoptional/build
cd myoptional/build
git submodule update --init
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release -- /m
ctest -C Release --output-on-failure
```
