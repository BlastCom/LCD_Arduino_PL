#include "LCDcommands.h"

void writeSingle(byte thisValue) {
  // take the chip select low to select the device:
  digitalWrite(10, LOW);
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(10, HIGH);
  delay(20); //Important! Give time to the LCD to read the last command.
}

void writeRegister(byte thisRegister, byte thisValue1) {
  // take the chip select low to select the device:
  digitalWrite(10, LOW);
  SPI.transfer(thisRegister); //* modified * Send register location
  delay(20);
  SPI.transfer(thisValue1);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(10, HIGH);
  delay(20); //Important! Give time to the LCD to read the last command.
}

void writeRegister(byte thisRegister, byte thisValue1, byte thisValue2) {
  // take the chip select low to select the device:
  digitalWrite(10, LOW);
  SPI.transfer(thisRegister); //* modified * Send register location
  delay(20);
  SPI.transfer(thisValue1);  //Send value to record into register
  delay(20);
  SPI.transfer(thisValue2);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(10, HIGH);
  delay(20); //Important! Give time to the LCD to read the last command.
}

void writeRegister(byte thisRegister, byte thisValue1, byte thisValue2, byte thisValue3) {
  // take the chip select low to select the device:
  digitalWrite(10, LOW);
  SPI.transfer(thisRegister); //* modified * Send register location
  delay(20);
  SPI.transfer(thisValue1);  //Send value to record into register
  delay(20);
  SPI.transfer(thisValue2);  //Send value to record into register
  delay(20);
  SPI.transfer(thisValue3);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(10, HIGH);
  delay(20); //Important! Give time to the LCD to read the last command.
}

void writeRegister(byte thisRegister, byte thisValue1, byte thisValue2, byte * thisValue3) {
  // take the chip select low to select the device:
  digitalWrite(10, LOW);
  SPI.transfer(thisRegister); //* modified * Send register location
  delay(20);
  SPI.transfer(thisValue1);  //Send value to record into register
  delay(20);
  SPI.transfer(thisValue2);  //Send value to record into register
  
  for (int i = 0; i < 8; i++)
  {
    SPI.transfer(thisValue3[i]);  //Send value to save into register
    delay(20);
  }

  // take the chip select high to de-select:
  digitalWrite(10, HIGH);
  delay(20); //Important! Give time to the LCD to read the last command.
}

/*
 * Function that clear the LCD screen
 */
void clearLCD(void)
{
  writeRegister(0xFE, 0x51); //clear screen
}

/*
 * Set the LCD backlight brightness. (0x01 to 0x08)
 * 0x01 = Turn off
 * 0x08 = Turn on (100% brightness)
 * Note: Value saved in LCD module memory (even if turn off)
 * 
 * Example (Loop): 
 * 
  byte lightLevel = 0x01;
  if(lightLevel == 0x09)
    flagTest = 0x01;
  setLightLCD(lightLevel);
  flagTest++;
  delay(1000);
 */
void setLightLCD(byte lightLevel)
{
  writeRegister(0xFE, 0x53, lightLevel); //LED Screen On
}

/*
 * Function that clear the LCD screen
 */
void setContrastLCD(byte thisValue)
{
    writeRegister(0xFE, thisValue); //set Contrast
    //NEED 3 PARAMS, Curently 2 Max
}

/*
 * Set the cursor to a specific place on the LCD 20X4 matrix.
 *      
 *        Column 1  Column 20
 * Line 1   0x00      0x13
 * Line 2   0x40      0x53
 * Line 3   0x14      0x27
 * Line 4   0x54      0x67
 * 
 * Default: 0x00
 */
void setCursorPos(int line, int pos)
{
  byte truePos = 0x00;
  
  if(line == 1)
    truePos = 0x00 + pos;
  else if(line == 2)
    truePos = 0x40 + pos;
  else if(line == 3)
    truePos = 0x14 + pos;
  else if(line == 4)
    truePos = 0x54 + pos;
  else{}
  //false; nothing happen
  
  writeRegister(0xFE, 0x45, truePos);
}

/*
 * nbItteration should be initialize to 0 at start of program
 * 
 * thoughts:
 * know how many special character are loaded and show them on lcd
 * OR
 * Load them all at start, then show on lcd depending on which character
 */
int loadCustomChar(byte * bitMap, int * nbItteration) 
{
  if(*nbItteration)
  {
    nbItteration++;
    writeRegister(0xFE, 0x54, nbItteration, bitMap);
  }
  return 0;
}
/*
void loadMemCustomChar(byte memPosition, byte * thisArray)
{
  writeRegister(0xFE, 0x54, memPosition, thisArray);
}*/
/**
void loadCustomChar(byte memPos, byte lcdPos)
{
  if(
    (lcdPos >= 0x00 && lcdPos <= 0x13) || //Line1
    (lcdPos >= 0x40 && lcdPos <= 0x53) || //Line2
    (lcdPos >= 0x14 && lcdPos <= 0x27) || //Line3
    (lcdPos >= 0x54 && lcdPos <= 0x67)    //Line4
    ){
    writeRegister(0xFE, 0x45, lcdPos);
    writeSingle(memPos);
   }
}
*/
