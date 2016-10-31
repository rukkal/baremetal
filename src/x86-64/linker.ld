ENTRY(_start)

SECTIONS
{
    /* the multiboot header should be somewhere in the first 8KB of the final kernel file */
	. = 1000;
    
    .bootstrap :
    {
        multiboot_header.o (.text)
    }
	
    /* let's put other sections at 1MB (bootloaders usually put kernels at that place) */
    . = 1M;
   
	.text BLOCK(4000K) : ALIGN(4K)
	{
        *(EXCLUDE_FILE(*multiboot_header.o) .text)
		*(.text)
	}

	.rodata BLOCK(4000K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4000K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4000K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
