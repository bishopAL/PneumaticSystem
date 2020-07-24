#include "PneumaticSys.hpp"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

PneumaticSys ps;
char temp[4];
uint8_t *presentPressureStatus = new uint8_t[4]; //当前的气压状态
uint8_t *previousPressureStatus = new uint8_t[4]; //先前的气压状态
uint8_t *operatingArray =  new uint8_t[4];

uint8_t *separateFlag(int flag)
{
  uint8_t *res = new uint8_t[4];
  res[0] = flag / 1000;
  res[1] = (flag - res[0]*1000) / 100;
  res[2] = (flag - res[0]*1000 - res[1]*100) / 10;
  res[3] = (flag - res[0]*1000 - res[1]*100 - res[2]* 10) / 1;
  return res;
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial.println("Serial Initialize Done!");
  for (int i=0; i<4; i++)
  {
    previousPressureStatus[i] = 0;
    presentPressureStatus[i] = 0;
  }
  
  Serial.print("当前电磁阀编号状态：");
  for(int i=0; i<4; i++)  //i=0:4 <-> 脚顺序：RF RH LF LH
    {
        for(int j=0; j<3; j++)
        {
            Serial.print(ps.SV[i][j]);
            Serial.print(",");
        }
    }
   Serial.println(" ");

   analogWrite(10, int(0.09/0.9*255)); // 充气电气比例阀电压设置
   analogWrite(11, int(0.25/0.9*255)); // 吸气电气比例阀电压设置
   lcd.init(); 
   lcd.backlight();
}


void loop() 
{
  String temp_string;
  int temp_int;
  if (Serial.available()>0) 
  {   
//    temp_string = Serial.readString();
//    temp_int = temp_string.toInt();
//    presentPressureStatus = separateFlag(temp_int);
    lcd.setCursor(0, 0);
    lcd.print("S");
    Serial.readBytes(temp, 4);
    if(temp[0] >= 48 && temp[1] >= 48 && temp[2] >= 48 &&temp[3] >= 48 )
    {
      for(int i=0; i<4; i++)
      {
        presentPressureStatus[i] = temp[i] - 48;
      }
    }
    
    lcd.setCursor(8, 0);
    lcd.print(presentPressureStatus[0]);
    lcd.setCursor(10, 0);
    lcd.print(presentPressureStatus[1]);
    lcd.setCursor(8, 1);
    lcd.print(presentPressureStatus[3]);
    lcd.setCursor(10, 1);
    lcd.print(presentPressureStatus[2]);
  }
    for (int i=0; i<4; i++)
   {
        switch(presentPressureStatus[i])
        {
          case 0:ps.enableNormalPneumatic(i);  break;
          case 1:ps.enablePositivePneumatic(i);  break;
          case 2:ps.enableNegtivePneumatic(i);  break;
        }
   }
   
//     delay(500);
//      for (int i=0; i<4; i++)
//     {
//        if (operatingArray[i] == 1) 
//        {
//           ps.holdPressure(i);
//        }
//     }

//     Serial.print("当前状态：");
//     for(int i=0; i<4; i++)
//     {   
//        Serial.print(presentPressureStatus[i]);
//        Serial.print(",");
//     }
//     Serial.println(" ");
     
      
}
