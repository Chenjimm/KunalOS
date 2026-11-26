#include "../include/kernel.h"

void
kernel_main()
{
	/*** Init ***/
	// Setting
	CloseBIOSCursor();
	InitSerialPort();

	// Init var
	vector VGACursor = {0, 0};
	VGAClearScreen(&VGACursor);

	VGAPrintf(&VGACursor, "Hello, %s!\n", "KunalOS");

	SerialPutChar('H');
	SerialPutChar('e');
	SerialPutChar('l');
	SerialPutChar('l');
	SerialPutChar('o');
	SerialPutChar(',');
	SerialPutChar('T');
	SerialPutChar('h');
	SerialPutChar('e');
	SerialPutChar('r');
	SerialPutChar('e');
	SerialPutChar('!');
	SerialPutChar('\n');

	char A = SerialRead();
	VGAPrintf(&VGACursor, "%c\n", A);

	for(;;)
	{
		asm("hlt");
	}
}
