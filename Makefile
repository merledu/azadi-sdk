export CORE
export DRIVERS
export INCLUDE
export LIBS
export FILEPATH
export ROOT

PROGRAM ?= 

 

ROOT := $(shell pwd)
FILEPATH := $(ROOT)/softwares/$(PROGRAM)
# paths
BSP := $(ROOT)/bsp
CORE := $(BSP)/core
DRIVERS := $(BSP)/drivers
INCLUDE := $(BSP)/include
LIBS := $(BSP)/lib

RISCV=riscv32-unknown-elf-
GCC=$(RISCV)gcc
OBJDMP=$(RISCV)objdump
GCCFLAGS=-march=rv32im -mabi=ilp32 -mcmodel=medany -g
OBJFLAGS=--disassemble-all --disassemble-zeroes 
# --section=.text --section=.text.startup --section=.text.init --section=.data
LINK_FLAGS = -march=rv32im -mabi=ilp32 -static -nostdlib -nostartfiles -T $(CORE)/link.ld



.PHONY: build build-drivers compile-drivers build-include build-core upload

upload : software
	@echo "Uploading..."

compile-drivers :
	@mkdir -p generated
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(CORE)/trap.c -o generated/trap.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/gpio/gpio.c -o generated/gpio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/plic/plic.c -o generated/plic.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/uart/uart.c -o generated/uart.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/mmio.c -o generated/mmio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/bitfield.c -o generated/bitfield.o -lgcc
	
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/utils.c -o generated/utils.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(CORE)/init.c -o generated/init.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(CORE)/trap.c -o generated/trap.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/gpio/gpio.c -o generated/gpio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/uart/uart.c -o generated/uart.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/timer/timer.c -o generated/timer.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/pwm/pwm.c -o generated/pwm.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/spi/spi.c -o generated/spi.o -lgcc
#	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/uart/uart.c -o generated/uart.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/plic/plic.c -o generated/plic.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/uart/uart.c -o generated/uart.o -lgcc		

build-drivers : compile-drivers
	$(RISCV)ar rcs generated/drivers.a generated/gpio.o generated/plic.o generated/timer.o generated/pwm.o generated/uart.o generated/spi.o

build : clean build-drivers
	@echo "building $(FILEPATH)/$(PROGRAM).c"
	@mkdir $(FILEPATH)/output
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -I$(DRIVERS)/timer -I$(DRIVERS)/plic -I$(DRIVERS)/uart -I$(DRIVERS)/gpio -I$(DRIVERS)/spi -c $(FILEPATH)/$(PROGRAM).c -o $(FILEPATH)/output/$(PROGRAM).o -lgcc
	$(GCC) $(LINK_FLAGS) $(CORE)/start.S $(CORE)/trap.S generated/timer.o generated/uart.o generated/utils.o generated/trap.o generated/plic.o generated/gpio.o $(FILEPATH)/output/$(PROGRAM).o -o $(FILEPATH)/output/$(PROGRAM).merl -lgcc
	$(OBJDMP) $(OBJFLAGS) $(FILEPATH)/output/$(PROGRAM).merl > $(FILEPATH)/output/$(PROGRAM).dump 
	$(RISCV)elf2hex --bit-width 32 --input $(FILEPATH)/output/$(PROGRAM).merl --output program.hex

test : clean 
	@echo "building $(FILEPATH)/$(PROGRAM).c"
	@mkdir $(FILEPATH)/output
	@mkdir -p generated
	$(GCC) $(GCCFLAGS) -I $(INCLUDE) -c $(DRIVERS)/timer/timer.c -c $(DRIVERS)/uart/uart.c -c $(DRIVERS)/spi/spi.c -o generated/timer.o generated/spi.o generated/uart.o generated/pwm.o -lgcc
	$(GCC) $(GCCFLAGS) -I $(INCLUDE) -I $(DRIVERS)/timer -I $(DRIVERS)/uart -I $(DRIVERS)/pwm -I $(DRIVERS)/spi -c $(FILEPATH)/$(PROGRAM).c -o $(FILEPATH)/output/$(PROGRAM).o -lgcc
	$(GCC) $(LINK_FLAGS) $(CORE)/start.S $(CORE)/timerh.S generated/timer.o generated/uart.o generated/spi.o  generated/pwm.o $(FILEPATH)/output/$(PROGRAM).o -o $(FILEPATH)/output/$(PROGRAM).merl -lgcc
	$(OBJDMP) $(OBJFLAGS) $(FILEPATH)/output/$(PROGRAM).merl > $(FILEPATH)/output/$(PROGRAM).dump 
	$(RISCV)elf2hex --bit-width 32 --input $(FILEPATH)/output/$(PROGRAM).merl --output program.hex

.PHONY: software	
software: clean
	@echo "Build $(PROGRAM)"
	cd ./softwares/$(PROGRAM) && $(MAKE) PROGRAM=$(PROGRAM) RISCV=$(RISCV)


.PHONY: clean
clean:
	rm -rf $(FILEPATH)/output
	rm -rf generated
	rm -f program.hex
