#include "PneumaticSys.hpp"

PneumaticSys ps;
char temp[4];
uint8_t *presentPressureStatus = new uint8_t[4]; //当前的气压状态
uint8_t *previousPressureStatus = new uint8_t[4]; //先前的气压状态
uint8_t *operatingArray =  new uint8_t[4];

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial1.setTimeout(50);
  Serial.setTimeout(50);
  Serial.println("Serial Initialize Done!");
  for (int i=0; i<4; i++)
  {
    previousPressureStatus[i] = 0;
  }
}


void loop() 
{
  String temp_string;
  int temp_int;
  if (Serial1.available()>0) 
  {   
    Serial1.readBytes(temp, 4);
    if(temp[0] > 48 && temp[1] > 48 && temp[2] > 48 &&temp[3] > 48 )
    {
      for(int i=0; i<4; i++)
      {
        presentPressureStatus[i] = temp[i] - 48;
      }
    }
  }
        
   for (int i=0; i<4; i++)
   {
      if (previousPressureStatus[i]!=presentPressureStatus[i]) operatingArray[i] = 1; //判断有哪几个与之前的气压状态不同，不同为1，相同为0
      else operatingArray[i] = 0;
   }
   
   if(operatingArray[0] == 1 or operatingArray[1] == 1 or operatingArray[2] == 1 or operatingArray[3] == 1)
   {
      for (int i=0; i<4; i++)
     {
        if (operatingArray[i] == 1) 
        {
          Serial.print("改变数：");
          Serial.println(i);
        }
        {
          switch(presentPressureStatus[i])
          {
            case 0:ps.enableNormalPneumatic(i); break;
            case 1:ps.enablePositivePneumatic(i); break;
            case 2:ps.enableNegtivePneumatic(i); break;
          }
        }
     }
     delay(500);
      for (int i=0; i<4; i++)
     {
        if (operatingArray[i] == 1) 
        {
           ps.holdPressure(i);
        }
     }
     previousPressureStatus = presentPressureStatus;
     Serial.print("当前状态：");
     for(int i=0; i<4; i++)
     {   
        Serial.print(previousPressureStatus[i]);
        Serial.print(",");
     }
     Serial.println(" ");
   }    
      
  
}
