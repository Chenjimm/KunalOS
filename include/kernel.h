// color
#define BLACK         0x0
#define BLUE          0x1
#define GREEN         0x2
#define CYAN          0x3
#define RED           0x4
#define MAGENTA       0x5
#define BROWN         0x6
#define LIGHT_GRAY    0x7
#define DARK_GRAY     0x8
#define LIGHT_BLUE    0x9
#define LIGHT_GREEN   0xa
#define LIGHT_CYAN    0xb
#define LIGHT_RED     0xc
#define LIGHT_MAGENTA 0xd
#define YELLOW        0xe
#define WHITE         0xf

typedef char  int8;
typedef short int16;
typedef int   int32;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef struct char_cell
{
	char Char;
	int8 Property;
} char_cell;

