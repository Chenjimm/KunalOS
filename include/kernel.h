#include <stdarg.h>

// VAG
#define VGA_BLACK         0x0
#define VGA_BLUE          0x1
#define VGA_GREEN         0x2
#define VGA_CYAN          0x3
#define VGA_RED           0x4
#define VGA_MAGENTA       0x5
#define VGA_BROWN         0x6
#define VGA_LIGHT_GRAY    0x7
#define VGA_DARK_GRAY     0x8
#define VGA_LIGHT_BLUE    0x9
#define VGA_LIGHT_GREEN   0xa
#define VGA_LIGHT_CYAN    0xb
#define VGA_LIGHT_RED     0xc
#define VGA_LIGHT_MAGENTA 0xd
#define VGA_YELLOW        0xe
#define VGA_WHITE         0xf

typedef char  int8;
typedef short int16;
typedef int   int32;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef struct vector {
	int X;
	int Y;
} vector;

void
CloseBIOSCursor();

void
VGAWriteChar(unsigned char CharCode, uint8 CharColor, uint8 BackgroundColor, vector Vector);

void
VGAClearScreen(vector* VGACursor);

void
VGAScroll(vector *VGACursor);

void
VGAChangeLine(vector *VGACursor);

void
VGAPutChar(vector *VGACursor, unsigned char CharCode);

void
VGAPutString(vector *VGACursor, char* String);

void
VGAPrintf(vector *VGACursor, char* String, ...);

// Serial Port

// 要和串口进行通行，首先要对串口初始化
// 要设置串口的连接速度——波特率，必须与其他设备相同。 一般使用较低的波特率。
// 还要设置相同的奇偶校验类型，和字符位数
// 初始化后，还要设置中断处理程序。
// IRQ会检查是否收到数据,收到则会进行处理，还会检查对方是否准备好接收数据。
// 初始化COM1

#define PORT 0x3f8 // COM1 base address


void
outb(uint16 port, uint8 val);

uint8
inb(uint16 port);

int
InitSerialPort();

int
serial_received();

char
SerialRead();

int
is_transmit_empty();

void
SerialPutChar(char a);
