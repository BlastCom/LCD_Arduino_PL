//Includes
#include <SPI.h>
#include <stdlib.h>
#include "LCDcommands.h"
#include "ShredderCharSpe.h"
// *** END Includes

//Defines
#define slaveSelect 10
// *** Defines

//Global Variables !!!The less is the better, none would be perfect. Need to clean before release!!!
typedef struct customCharBank
{
  int memoryPosition = 0;
  char thisCharacter;
  byte bitMap[8] = {0};
};
customCharBank charSpeBank[8];
int customCharNB = 0;

// *** END Global Variables

void setup()
{
  //Variables
  //HERE
  // *** END Variables

  //Functions
  Serial.begin(9600);
  SPI.begin();
  SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE3));
  pinMode(slaveSelect, OUTPUT);
  delay(100);

  clearLCD();
  setLightLCD(0x08); //backlight full bright ranged from 0x01 to 0x08

  writeString("La déchiqueteuse", 1, 1);
  writeString("Plastic Loop", 2, 4);
  writeString("Par Simon Laflamme", 3, 1);
  delay(2000);
  // *** END Functions
}

// the loop function runs over and over again forever
void loop()
{
  //Variables
  //HERE
  // *** END Variables

  //Functions
  //HERE
  // *** END Functions
}

void writeString(char * arrayString, int verticalPos, int horizontalPos)
{
  //Variables
  char thisCharacter;
  byte * thisBitMap;
  int countCharSpe = 0;
  int trueSize = strlen(arrayString); //need a 16 bit character for éè
  int flagSpeChar = 0;
  // *** END Variables
  //byte eAccentAigu[ARRAY_MAX_LENGHT] = {0x02, 0x0c, 0x0e, 0x11, 0x1f, 0x10, 0x0e, 0x00};
  //Functions

  setCursorPos(verticalPos, horizontalPos);

  
  for (int i = 0; i < trueSize; i++)
  {
    if (i > 20)
      break;

    thisCharacter = arrayString[i];
    Serial.println(thisCharacter);

    flagSpeChar = isCharSpe(arrayString, thisBitMap, i);
    Serial.print("Special Char Val : ");
    Serial.println(flagSpeChar, BIN);
    if(flagSpeChar)
    {
      /*for(int j = 0; j < 8; j++)
      {
        Serial.print(thisBitMap[j]);
        Serial.print(", ");
      }*/
      Serial.print("HEY");
    }
    Serial.println(";");

    //check if there's a special character
    if (flagSpeChar)
    {
      //Show the special character at the right place
      loadCustomChar(thisBitMap, 0x01);
      setCursorPos(verticalPos, horizontalPos+i);
      writeSingle(0x01);
      //charSpeBank[customCharNB].thisCharacter = arrayString[i]; //WRONG!!!!
      //charSpeBank[customCharNB].memoryPosition = customCharNB;
      /*for(int j = 0; j < 8; j++)
        charSpeBank[customCharNB].bitMap[j] = thisBitMap[j]; */
      i++; //Skip next character related to special character
    }
    else
      writeSingle(arrayString[i]); //Show non special character
  }
  // *** END Functions
}
