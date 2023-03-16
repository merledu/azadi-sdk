OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv",
	      "elf32-littleriscv")
OUTPUT_ARCH(riscv)

MEMORY 
{
ICCM  : ORIGIN = 0x10000000, LENGTH = 2048K 
DCCM  : ORIGIN = 0x20000000, LENGTH = 2048K
}

ENTRY(_start)
SECTIONS
{
PROVIDE( __stack_top = ORIGIN(DCCM) + LENGTH(DCCM));
.init : { KEEP (*(SORT_NONE(.init))) }>ICCM

.text : { *(.text) }>ICCM

.fini :
{
  KEEP (*(SORT_NONE(.fini)))
}>ICCM

.preinit_array  :
{
  PROVIDE_HIDDEN (__preinit_array_start = .);
  KEEP (*(.preinit_array))
  PROVIDE_HIDDEN (__preinit_array_end = .);
}>ICCM

.init_array     :
{
  PROVIDE_HIDDEN (__init_array_start = .);
  KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
  KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
  PROVIDE_HIDDEN (__init_array_end = .);
}>ICCM

.fini_array     :
{
  PROVIDE_HIDDEN (__fini_array_start = .);
  KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
  KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
  PROVIDE_HIDDEN (__fini_array_end = .);
}>ICCM

.ctors          :
{
  /* gcc uses crtbegin.o to find the start of
      the constructors, so we make sure it is
      first.  Because this is a wildcard, it
      doesn't matter if the user does not
      actually link against crtbegin.o; the
      linker won't look for a file to match a
      wildcard.  The wildcard also means that it
      doesn't matter which directory crtbegin.o
      is in.  */
  KEEP (*crtbegin.o(.ctors))
  KEEP (*crtbegin?.o(.ctors))
  /* We don't want to include the .ctor section from
      the crtend.o file until after the sorted ctors.
      The .ctor section from the crtend file contains the
      end of ctors marker and it must be last */
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
  KEEP (*(SORT(.ctors.*)))
  KEEP (*(.ctors))
}>ICCM

.dtors :
{
  KEEP (*crtbegin.o(.dtors))
  KEEP (*crtbegin?.o(.dtors))
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
  KEEP (*(SORT(.dtors.*)))
  KEEP (*(.dtors))
}>ICCM

.data :
{
  __global_pointer$ = . + 0x000;
  *(.data)
}>DCCM

.bss : { *(.bss) }>DCCM
}
