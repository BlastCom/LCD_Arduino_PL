#include <SPI.h>
#define LCDarrayMax 20

void writeSingle(byte thisValue);
void writeRegister(byte thisRegister, byte thisValue1);
void writeRegister(byte thisRegister, byte thisValue1, byte thisValue2);
void writeRegister(byte thisRegister, byte thisValue1, byte thisValue2, byte * thisValue3);
void clearLCD(void);
void setLightLCD(byte lightLevel);
void setContrastLCD(byte thisValue);
void setCursorPos(int line, int pos);
void loadMemCustomChar(byte memPosition, byte * thisArray);
int loadCustomChar(byte * bitMap, int * nbItteration);
