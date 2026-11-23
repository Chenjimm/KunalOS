#include "../include/kernel.h"

void
WriteCharacter(uint8 c, uint8 forecolour, uint8 backcolour, int32 x, int32 y)
{
     uint16 attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16 * where;
     where = (volatile uint16 *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}

void
kernel_main()
{
	for(;;)
	{
	}
}
