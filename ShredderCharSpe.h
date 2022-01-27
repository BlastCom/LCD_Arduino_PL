#include <SPI.h>

#define PREFIXE_UTF8_SPECHAR 0xc3
#define E_ACCENT_GRAVE 0xa8 //from UTF-8 table
#define E_ACCENT_AIGU 0xa9 //from UTF-8 table
#define ARRAY_MAX_LENGHT 8


typedef struct charSpeLCD
{
  byte eAccentAigu[ARRAY_MAX_LENGHT] = {0x02, 0x0c, 0x0e, 0x11, 0x1f, 0x10, 0x0e, 0x00};
  byte eAccentGrave[ARRAY_MAX_LENGHT] = {0x08, 0x06, 0x0e, 0x11, 0x1f, 0x10, 0x0e, 0x00};
};

int isCharSpe(char * thisChar, byte * bitMap, int arrayPos);
