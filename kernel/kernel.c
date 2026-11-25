#include "../include/kernel.h"

void
kernel_main()
{
	CloseBIOSCursor();

	vector VGACursor = {0, 0};
	VGAClearScreen(&VGACursor);

	VGAPrintf(&VGACursor, "Hello, %s!\n", "KunalOS");

	for(;;)
	{
		asm("hlt");
	}
}
