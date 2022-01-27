#include "ShredderCharSpe.h"

int isCharSpe(char * thisChar, byte * bitMap, int arrayPos)
{
  struct charSpeLCD c1;
  Serial.println("IN");
  //Serial.println((thisChar[arrayPos] & 0xFF,HEX),HEX);
  if((thisChar[arrayPos] & 0xFF) == PREFIXE_UTF8_SPECHAR)
  {
    //Serial.println(thisChar[arrayPos] & 0xFF);
    if((thisChar[arrayPos +1] & 0xFF) == E_ACCENT_AIGU)////NEED CHECKUP
    {
      //Serial.println(thisChar[arrayPos +1] & 0xFF);
      Serial.print("HERE!! :");
      for(int i = 0; i<ARRAY_MAX_LENGHT; i++)
      {
        bitMap[i] = c1.eAccentAigu[i];
        Serial.print(c1.eAccentAigu[i],HEX);
        Serial.print(", ");
      }
      Serial.println(";");
      return 1;
    } 
    else
    {
      bitMap = 0;
    }
    Serial.println("OUT");
    return 0;
  }
  Serial.println("OUT");
  return 0;
}
