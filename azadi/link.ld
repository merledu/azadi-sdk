OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv",
	      "elf32-littleriscv")
OUTPUT_ARCH(riscv)

MEMORY 
{
ICCM  : ORIGIN = 0x10000000, LENGTH = 8K 
DCCM  : ORIGIN = 0x20000000, LENGTH = 8K
}

ENTRY(_start)
SECTIONS
{
PROVIDE( __stack_top = ORIGIN(DCCM) + LENGTH(DCCM));
.init : { KEEP (*(SORT_NONE(.init))) }>ICCM
.text : { *(.text) }>ICCM
.data :
{
  __global_pointer$ = . + 0x000;
  *(.data)
}>DCCM
.bss : { *(.bss) }>DCCM
}
