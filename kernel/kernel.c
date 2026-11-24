#include "../include/kernel.h"

/*  VGA
 * 
 *  the linear text buffer is located in physical address 0xB8000.
 *  VGA mode 3 provides a text interface 80 characters wide and 25 characters lines per screen.
 */
void CloseVGACursor()
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
			VGAWriteChar(0, VGA_WHITE, VGA_BLACK, (vector){x, y});
		}
	}
}

void
VGAScroll(vector *VGACursor)
{
	for(int Y = 0; Y < 24; Y++)
	{
		for(int X = 0; X < 80; X++)
		{
			volatile uint16 * VGACharUp   = (volatile uint16 *)0xB8000 + (Y * 80 + X);
			volatile uint16 * VGACharDown = (volatile uint16 *)0xB8000 + ((Y+1) * 80 + X);
			*VGACharUp = *VGACharDown;
		}
	}
	VGACursor->Y--;
}

void VGAChangeLine(vector *VGACursor)
{
	if(VGACursor->Y == 24)
	{
		VGAScroll(VGACursor);
	}
	VGACursor->X = 0;
	VGACursor->Y++;
}

void
VGAPutChar(vector *VGACursor, unsigned char CharCode)
{
	VGAWriteChar(0, VGA_WHITE, VGA_BLACK, *VGACursor);
	if(CharCode == '\n')
	{
		VGAChangeLine(VGACursor);
	}
	else
	{
		VGAWriteChar(CharCode, VGA_WHITE, VGA_BLACK, *VGACursor);
		VGACursor->X++;
		if(VGACursor->X == 80)
		{
			VGAChangeLine(VGACursor);
		}
	}
	VGAWriteChar(0, VGA_WHITE, VGA_WHITE, *VGACursor);
}

void VGAPutString(vector *VGACursor, unsigned char* String)
{
	int32 i = 0;
	unsigned char Char = String[i];
	while(Char!=0)
	{
		VGAPutChar(VGACursor, Char);
		i++;
		Char = String[i];
	}
}

void
kernel_main()
{
	CloseVGACursor();
	VGAClearScreen();

	vector VGACursor = {0, 0};

	VGAPutString(&VGACursor, "Hello sailer\n");

	for(;;)
	{
	}
}
