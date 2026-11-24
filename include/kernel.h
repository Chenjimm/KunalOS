// VAG Color
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
