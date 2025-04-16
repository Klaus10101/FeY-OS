
ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

# OUTPUT_FORMAT(elf64-x86_64)
# OUTPUT_ARCH(x86_64:x86_64)

SECTIONS
{
	. = 0X0100000;

	.text :
	{    
	    *(.multiboot)
		*(.text*)
		*(.roadata)
	}
	.data :
	{
		start_cons = .;
		KEEP(*(.init_array));
		KEEP(*(SORT_BY_INIT_PRIORITY( .init_arrat.*)));
		end_cons = .;

		*(.data)
	}
	.bss :
	{
		*(.bss)
	}
	/DISCARD/ :
	{    
	    *(.fini_array)
		*(.comment)
	}
}
