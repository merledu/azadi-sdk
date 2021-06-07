
RISCV ?= riscv64-unknown-elf-

GCC=$(RISCV)gcc
OBJDMP=$(RISCV)objdump
GCCFLAGS=-march=rv32imfdc -mabi=ilp32d -mcmodel=medany -g
OBJFLAGS=--disassemble-all --disassemble-zeroes 
# --section=.text --section=.text.startup --section=.text.init --section=.data
LINK_FLAGS = -march=rv32imfdc -mabi=ilp32d -static -nostdlib -nostartfiles -T $(CORE)/link.ld

.PHONY : start upload compile

start:
	make compile build

compile : 
	@cd ../../
	@mkdir -p generated
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(CORE)/trap.c -o generated/trap.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/gpio/gpio.c -o generated/gpio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/plic/plic.c -o generated/plic.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/mmio.c -o generated/mmio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/bitfield.c -o generated/bitfield.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(LIBS)/utils.c -o generated/utils.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(CORE)/init.c -o generated/init.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(CORE)/trap.c -o generated/trap.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/gpio/gpio.c -o generated/gpio.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/timer/timer.c -o generated/timer.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/pwm/pwm.c -o generated/pwm.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/sa/uart.c -o generated/uart.o -lgcc
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -c $(DRIVERS)/plic/plic.c -o generated/plic.o -lgcc	
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -c $(DRIVERS)/spi/spi.c -o generated/spi.o -lgcc

build :
	@echo "building $(FILEPATH)/$(PROGRAM).c"
	@mkdir $(FILEPATH)/output
	$(GCC) $(GCCFLAGS) -I$(INCLUDE) -I$(LIBS) -I$(DRIVERS)/timer -I$(DRIVERS)/plic -I$(DRIVERS)/gpio -c $(FILEPATH)/$(PROGRAM).c -o $(FILEPATH)/output/$(PROGRAM).o -lgcc
	$(GCC) $(LINK_FLAGS) $(CORE)/start.S $(CORE)/trap.S generated/timer.o generated/utils.o generated/trap.o generated/plic.o generated/gpio.o $(FILEPATH)/output/$(PROGRAM).o -o $(FILEPATH)/output/$(PROGRAM).merl -lgcc
	$(OBJDMP) $(OBJFLAGS) $(FILEPATH)/output/$(PROGRAM).merl > $(FILEPATH)/output/$(PROGRAM).dump 
	$(RISCV)elf2hex --bit-width 32 --input $(FILEPATH)/output/$(PROGRAM).merl --output $(ROOT)/program.hex