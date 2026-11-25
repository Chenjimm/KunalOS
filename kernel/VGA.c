#include "../include/kernel.h"

/*  VGA
 * 
 *  the linear text buffer is located in physical address 0xB8000.
 *  VGA mode 3 provides a text interface 80 characters wide and 25 characters lines per screen.
 */
void
CloseBIOSCursor()
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
VGAClearScreen(vector* VGACursor)
{
	for(int x = 0; x < 80; x++)
	{
		for(int y = 0; y < 25; y++ )
		{
			VGAWriteChar(0, VGA_WHITE, VGA_BLACK, (vector){x, y});
		}
	}
	VGACursor->X = 0;
	VGACursor->Y = 0;
	VGAWriteChar(0, VGA_WHITE, VGA_WHITE, *VGACursor);
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
	for(int X = 0; X < 80; X++)
	{
		VGAWriteChar(0, VGA_BLACK, VGA_BLACK, (vector){X, 24});
	}
	VGACursor->Y--;
}

void
VGAChangeLine(vector *VGACursor)
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

void
VGAPutString(vector *VGACursor, char* String)
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
VGAPrintf(vector *VGACursor, char* String, ...)
{
	va_list ArgsPointer;
	va_start(ArgsPointer, VGACursor);
	int i = 0;
	while(String[i] != 0)
	{
		char Char = String[i];
		if(Char == '%')
		{
			i++;
			Char = String[i];
			switch(Char)
			{
				case 'd':
				{
					int32 Base = 10;
					int32 Value = va_arg(ArgsPointer, int);
					char Index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
					char Format[256] = {};
					if(Value < 0)
					{
						VGAPutChar(VGACursor, '-');
						Value = -Value;
					}

					int32 Length = 0;
					do
					{
						Format[Length++] = Index[Value%Base];
						Value /= Base;
					}
					while(Value);
					Length--;

					for(int32 PrintIndex = Length; PrintIndex >= 0; PrintIndex--)
					{
						VGAPutChar(VGACursor, Format[PrintIndex]);
					}
				} break;

				case 'x':
				{
					int32 Base = 16;
					int32 Value = va_arg(ArgsPointer, int);
					char Index[] = "0123456789ABCDEF";
					char Format[256] = {};
					if(Value < 0)
					{
						VGAPutChar(VGACursor, '-');
						Value = -Value;
					}

					int32 Length = 0;
					do
					{
						Format[Length++] = Index[Value%Base];
						Value /= Base;
					}
					while(Value);
					Length--;

					for(int32 PrintIndex = Length; PrintIndex >= 0; PrintIndex--)
					{
						VGAPutChar(VGACursor, Format[PrintIndex]);
					}
				} break;

				case 's':
				{
					char* Value = va_arg(ArgsPointer, char*);
					VGAPutString(VGACursor, Value);
				} break;

				case 'c':
				{
					unsigned char Value = (unsigned char)va_arg(ArgsPointer, int);
					VGAPutChar(VGACursor, Value);
				} break;
			}
		}
		else
		{
			VGAPutChar(VGACursor, Char);
		}
		i++;
	}
}
