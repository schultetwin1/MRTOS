MEMORY
{
  ram (rwx)  : ORIGIN = 0x20000000, LENGTH = 8K
  rom (rx)   : ORIGIN = 0x08000000, LENGTH = 64K
  eep (r)    : ORIGIN = 0x08080000, LENGTH = 2K
}

EXTERN (vector_table)

ENTRY(reset_handler)

SECTIONS
{
  .text : {
    *(.vectors)
    *(.text*)
    . = ALIGN(4);
    *(.rodata*)
    . = ALIGN(4);
  } >rom

  . = ALIGN(4);
  _etext = .;

  .data : {
    _data = .;
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } >ram AT >rom
  _data_loadaddr = LOADADDR(.data);

  .bss : {
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } >ram

  end = .;
}

PROVIDE(_stack = ORIGIN(ram) + LENGTH(ram));
