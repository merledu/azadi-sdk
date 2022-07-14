
# Azadi SDK V2.0

This is the latest version of the Azadi SDK.

The SDK requires the `riscv 32-bit toolchain`. You can install it by downloading latest release from the github or compile them manually.


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
