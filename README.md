
# Azadi SDK V2.0

This is the latest in-development version of the Azadi SDK. Requires [`riscv-gnu-toolchain`](https://github.com/riscv/riscv-gnu-toolchain).

## Build Instructions

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=../tools/TC-riscv.cmake ../
$ cmake --build .
```
Optionally you can pass `-DTESTNAME=<test-name>` flag to build a specific test inside software directory.
By default `gpio-test` is executed.

```
$ cmake -DCMAKE_TOOLCHAIN_FILE=../tools/TC-riscv.cmake -DTESTNAME=plic_test ../
```