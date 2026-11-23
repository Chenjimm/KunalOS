#include "../include/kernel.h"

/*  VAG
 * 
 *  the linear text buffer is located in physical address 0xB8000.
 *  VGA mode 3 provides a text interface 80 characters wide and 25 characters lines per screen.
 */
void CloseVAGCursor()
{
	__asm__ __volatile__(
		"pushfl\n\t"
		"pushl %%eax\n\t"
		"pushl %%edx\n\t"

		"movw $0x3D4, %%dx\n\t"
		"movb $0x0A, %%al\n\t"
		"outb %%al, %%dx\n\t"

		"incw %%dx\n\t"
		"movb $0x20, %%al\n\t"
		"outb %%al, %%dx\n\t"

		"popl %%edx\n\t"
		"popl %%eax\n\t"
		"popfl\n\t"
		:
		:
		: "eax", "edx", "cc", "memory");
}

void
VGAWriteChar(unsigned char CharCode, uint8 CharColor, uint8 BackgroundColor, vector Vector)
{
	uint16 Color = (BackgroundColor<<4) | (CharColor & 0x0f);
	volatile uint16 * VGAAddress = (volatile uint16 *)0xB8000 + (Vector.Y * 80 + Vector.X);
	*VGAAddress = (CharCode) | (Color<<8);
}

void
VGAClearScreen()
{
	for(int x = 0; x < 80; x++)
	{
		for(int y = 0; y < 25; y++ )
		{
			VGAWriteChar(0, VAG_WHITE, VAG_BLACK, (vector){x, y});
		}
	}
}

void
kernel_main()
{
	CloseVAGCursor();
	VGAClearScreen();

	VGAWriteChar('H', VAG_WHITE, VAG_BLACK, (vector){0, 0});
	VGAWriteChar('e', VAG_WHITE, VAG_BLACK, (vector){1, 0});
	VGAWriteChar('l', VAG_WHITE, VAG_BLACK, (vector){2, 0});
	VGAWriteChar('l', VAG_WHITE, VAG_BLACK, (vector){3, 0});
	VGAWriteChar('o', VAG_WHITE, VAG_BLACK, (vector){4, 0});
	VGAWriteChar(',', VAG_WHITE, VAG_BLACK, (vector){5, 0});
	VGAWriteChar('k', VAG_WHITE, VAG_BLACK, (vector){6, 0});
	VGAWriteChar('u', VAG_WHITE, VAG_BLACK, (vector){7, 0});
	VGAWriteChar('n', VAG_WHITE, VAG_BLACK, (vector){8, 0});
	VGAWriteChar('a', VAG_WHITE, VAG_BLACK, (vector){9, 0});
	VGAWriteChar('l', VAG_WHITE, VAG_BLACK, (vector){10, 0});
	VGAWriteChar('O', VAG_WHITE, VAG_BLACK, (vector){11, 0});
	VGAWriteChar('S', VAG_WHITE, VAG_BLACK, (vector){12, 0});
	VGAWriteChar('!', VAG_WHITE, VAG_BLACK, (vector){13, 0});

	for(;;)
	{
	}
}
