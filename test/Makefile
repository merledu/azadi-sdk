TEST_PATH = $(SDK_ROOT)/test

RISCV=riscv32-unknown-elf-
GCC=$(RISCV)gcc
OBJDMP=$(RISCV)objdump
GCCFLAGS=-march=rv32i -mabi=ilp32 -mcmodel=medany
OBJFLAGS=--disassemble-all --disassemble-zeroes 
LINK_FLAGS = -march=rv32i -mabi=ilp32 -static -nostdlib -nostartfiles -T $(SDK_ROOT)/test/link.ld
# --section=.text --section=.text.startup --section=.text.init --section=.data

.PHONY: build

build : clean
	@echo "building $(FILEPATH)/hello.c"
	@mkdir $(TEST_PATH)/output
	$(GCC) $(GCCFLAGS) -c $(TEST_PATH)/gpio.c -o $(TEST_PATH)/output/gpio -lgcc
	$(GCC) $(GCCFLAGS) -c $(TEST_PATH)/hello.c -o $(TEST_PATH)/output/hello -lgcc
	$(GCC) $(LINK_FLAGS) $(TEST_PATH)/start.S $(TEST_PATH)/output/hello $(TEST_PATH)/output/gpio -o $(TEST_PATH)/output/hello.merl -lgcc
	$(RISCV)elf2hex --bit-width 32 --input $(TEST_PATH)/output/hello.merl --output $(TEST_PATH)/output/program.hex
	$(OBJDMP) $(OBJFLAGS) $(TEST_PATH)/output/hello.merl > $(TEST_PATH)/output/hello.dump 
	

.PHONY: clean
clean:
	rm -rf $(TEST_PATH)/output
