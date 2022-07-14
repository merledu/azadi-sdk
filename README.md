
# Azadi SDK setup

This is the latest version of the Azadi SDK, which is under active development.

## Getting started

These instructions were developed using a fresh Ubuntu 20.04 64-Bit.

The following packages needed to be installed:

~~~~~shell
sudo apt-get install -y build-essential git libftdi-dev libftdi1 doxygen python3-pip libsdl2-dev curl cmake libusb-1.0-0-dev scons gtkwave libsndfile1-dev rsync autoconf automake texinfo libtool pkg-config libsdl2-ttf-dev
~~~~~

The SDK also requires the `riscv 32-bit toolchain` and `sifive-elf2hex` packages. You can install them by downloading latest release from their github or compile them manually (recommended):

Please, refer to official guide to update gcc if is needed.

## SDK build

Compile the SDK with this command:

~~~~~shell
make PROGRAM=hello
~~~~~

This searches for the c program in software directory and compiles it. The generated hex and elf file can then executed on Azadi SoC.

## Adding New Programs

The recommended way to program Azadi SoC is to use the platform io package of Azadi SDK. Nevertheless, if you plan to use the sdk manually, you should:

1. Create a folder inside `software` directory
2. Create a c file with same name as program folder name and a Makefile
3. Build the program with `make PROGRAM=program_name`