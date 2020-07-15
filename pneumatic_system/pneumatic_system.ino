#include "PneumaticSys.hpp"

int *separateFlag(int flag)
{
  int *res = new int[4];
  res[0] = flag / 1000;
  res[1] = (flag - res[0]*1000) / 100;
  res[2] = (flag - res[0]*1000 - res[1]*100) / 10;
  res[3] = (flag - res[0]*1000 - res[1]*100 - res[2]* 10) / 1;
  return res;
}

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
}

PneumaticSys ps;
int *FLAG = new int[4];

void loop() 
{
  String temp_string;
  int temp_int;
  if (Serial.available()>0)  //蓝牙发数字是调整当前气腔工作状态，FLAG 0：常压，1：充气，2：吸气
      {
        temp_string = Serial.readString();
        temp_int = temp_string.toInt();
        FLAG = separateFlag(temp_int);
        if (FLAG[0] == 0)
        {
          ps.enableNormalPneumatic(0);
          delay(1000);
          ps.holdPressure(0);
          Serial.println("Normal-Pressure Mode actived.");
        }
        else if (FLAG[0] == 1)
        {
          ps.enablePositivePneumatic(0);
          delay(1000);
          ps.holdPressure(0);
          Serial.println("Postive-Pressure Mode actived.");
        }
        else if(FLAG[0] == 2)
        {
          ps.enableNegtivePneumatic(0);
          delay(1000);
          ps.holdPressure(0);
          Serial.println("Negtive-Pressure Mode actived.");
        }
      }
  
}
