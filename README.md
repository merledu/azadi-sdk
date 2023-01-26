
# Azadi SDK V2.0

This is the latest unstable version of the Azadi SDK. Requires [`riscv-gnu-toolchain`](https://github.com/riscv/riscv-gnu-toolchain).

## Build Instructions

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=../tools/TC-riscv.cmake ../
$ cmake --build .
```
