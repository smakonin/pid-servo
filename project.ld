OUTPUT_FORMAT("coff-hc1x")
OUTPUT_ARCH("hc12")
ENTRY(_start)
SECTIONS 				
{ 		
  .io 0x0000 (NOLOAD) :
  {
    *(.io)
  }
  .text 0x1000 :
  {
    *(.text)
    *(.const)
    _ctor_beg = . ; 
    *(.ctor);
    _ctor_end = . ; 
    _dtor_beg = . ; 
    *(.dtor);
    _dtor_end = . ; 
  } 
  .data :
  {
    *(.data)
  }
  .bss :
  {
    _bss_beg = . ; 
    *(.bss);
    *(COMMON);
    _bss_end = . ; 
  }
  .heap : 
  {
    _heap_beg = . ; 
    *(.heap);
    _heap_end = . ; 
  }
  .vectors 0x0B00 :
  {
    *(.vectors)
  }
}
