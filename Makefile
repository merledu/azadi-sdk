PROGRAM ?= hello

RISCV=riscv64-unknown-elf-
GCC=$(RISCV)gcc
OBJDMP=$(RISCV)objdump
GCCFLAGS=-march=rv32imac -mabi=ilp32 -mcmodel=medany -O3
OBJFLAGS=--disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
HEX=riscv64-unknown-elf-elf2hex

FILEPATH = softwares/$(PROGRAM)


.PHONY: build upload

upload : build
	@echo "Uploading..."
	$(shell ./util/tx.sh $(FILEPATH)/output/$(PROGRAM).hex)

build :
	@echo "building $(FILEPATH)/$(PROGRAM).c"
	@mkdir $(FILEPATH)/output
	$(GCC) $(GCCFLAGS) -c $(FILEPATH)/$(PROGRAM).c -o $(FILEPATH)/output/$(PROGRAM).o
	$(OBJDMP) $(OBJFLAGS) $(FILEPATH)/output/$(PROGRAM).o > $(FILEPATH)/output/$(PROGRAM).mem 
	@hexdump -v -e '"%08x\n"' $(FILEPATH)/output/$(PROGRAM).mem > $(FILEPATH)/output/$(PROGRAM).hex

	

.PHONY: clean
clean:
	rm -rf $(FILEPATH)/output
	