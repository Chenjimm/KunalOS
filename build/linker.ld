OUTPUT_ARCH(i386)
ENTRY(start)

SECTIONS
{
	/* BIOS loads the MBR at 0x7C00. */
	. = 0x7C00;

	.boot : {
		KEEP(*(.boot))
	}

	/* The MBR must be exactly one 512-byte sector. */
	ASSERT(. == 0x7E00, "boot sector must be exactly 512 bytes")

	/* boot.s reads LBA 1 to 0x7E00 and jumps there. */
	.stage2 0x7E00 : {
		KEEP(*(.stage2))
	}

	/* The MBR only reads 64 sectors after the boot sector. */
	ASSERT(SIZEOF(.stage2) <= 64 * 512, "stage2 is too large for the MBR to load")

	. = 0x10000;

	.kernel : {
	    KEEP(*(.kernel))
	    *(.text*)
	    *(.rodata*)
	    *(.data*)
	}
	
	.bss : {
	    *(.bss*)
	    *(COMMON)

	}
	/DISCARD/ : {
		*(.comment)
		*(.note*)
		*(.eh_frame)
	}
}
