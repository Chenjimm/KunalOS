#include "../include/kernel.h"

void
outb(uint16 port, uint8 val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* There's an outb %al, $imm8 encoding, for compile-time constant port numbers that fit in 8b. (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

uint8
inb(uint16 port)
{
    uint8 ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

int
InitSerialPort()
{
	outb(PORT + 1, 0x00);
   	outb(PORT + 3, 0x80);
   	outb(PORT + 0, 0x03);
   	outb(PORT + 1, 0x00);
   	outb(PORT + 3, 0x03);
   	outb(PORT + 2, 0xC7);
   	outb(PORT + 4, 0x0B);
   	outb(PORT + 4, 0x1E);
   	outb(PORT + 0, 0xAE);

	if(inb(PORT + 0) != 0xAE)
	{
		return 1;
   	}

   	outb(PORT + 4, 0x0F);
   	return 0;
}

// 检查是否接收到数据 (Bit 0 == 1)
int
serial_received()
{
	return inb(PORT + 5) & 1;
}

// 阻塞读取一个字符
char
SerialRead()
{
	while (serial_received() == 0); // 等待直到数据就绪
   	return inb(PORT);                // 从接收缓冲区读取数据
}

// 检查发送缓冲区是否为空 (Bit 5 == 1, 即 0x20)
int
is_transmit_empty()
{
	return inb(PORT + 5) & 0x20;
}

// 阻塞发送一个字符
void
SerialPutChar(char a)
{
	while(is_transmit_empty() == 0); // 等待直到缓冲区为空
   	outb(PORT, a);                    // 将字符写入发送缓冲区
}
