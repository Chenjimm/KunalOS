#include "../include/kernel.h"

void
kernel_main()
{
	CloseBIOSCursor();

	vector VGACursor = {0, 0};
	VGAClearScreen(&VGACursor);

	VGAPutString(&VGACursor, "Hello OS\n");

	for(;;)
	{
	}
}
