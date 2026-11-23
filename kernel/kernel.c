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

	vector VGACursor = {0, 0};
	VGAWriteChar(0, VAG_BLACK, VAG_WHITE, VGACursor);

	for(;;)
	{
		asm("hlt");
	}
}
