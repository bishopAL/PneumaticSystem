#include "PneumaticSys.hpp"

uint8_t *separateFlag(int flag)
{
  uint8_t *res = new uint8_t[4];
  res[0] = flag / 1000;
  res[1] = (flag - res[0]*1000) / 100;
  res[2] = (flag - res[0]*1000 - res[1]*100) / 10;
  res[3] = (flag - res[0]*1000 - res[1]*100 - res[2]* 10) / 1;
  return res;
}

PneumaticSys ps;
uint8_t *presentPressureStatus = new uint8_t[4]; //当前的气压状态
uint8_t *previousPressureStatus = new uint8_t[4]; //先前的气压状态
uint8_t *operatingArray =  new uint8_t[4];

void setup() {
  Serial.begin(9600);
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
  
  if (Serial.available()>0)  //蓝牙发数字是调整当前气腔工作状态，FLAG 0：常压，1：充气，2：吸气
      {
        temp_string = Serial.readString();
        temp_int = temp_string.toInt();
        presentPressureStatus = separateFlag(temp_int); //获取当前气压状态
        
       for (int i=0; i<4; i++)
       {
          if (previousPressureStatus[i]!=presentPressureStatus[i]) operatingArray[i] = 1; //判断有哪几个与之前的气压状态不同，不同为1，相同为0
          else operatingArray[i] = 0;
       }
        for (int i=0; i<4; i++)
       {
          if (operatingArray[i] == 1) 
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
