#include "PneumaticSys.hpp"
#include "Arduino.h"

PneumaticSys::PneumaticSys()
{
    for(int i=0; i<4; i++)  //i=0:4 <-> 脚顺序：RF RH LF LH
    {
        for(int j=0; j<4; j++)
        {
            SV[i][j] = i*4 + j + 22;
        }
    }

  	for(int i=0; i<4; i++)
  	{
  		pinMode(SV[i][1], OUTPUT); //一号电磁阀，正压气路 所有电磁阀设为断电常闭
   		pinMode(SV[i][2], OUTPUT); //二号电磁阀，负压气路
      pinMode(SV[i][3], OUTPUT); //三号电磁阀，泄压阀
      pinMode(SV[i][4], OUTPUT); //四号电磁阀，总阀门
  	}
    for(int i=0; i<4; i++)
    {
        digitalWrite(SV[i][1], LOW); //一号电磁阀，正压气路 所有电磁阀设为断电常闭
        digitalWrite(SV[i][2], LOW); //二号电磁阀，负压气路
        digitalWrite(SV[i][3], LOW); //三号电磁阀，泄压阀
        digitalWrite(SV[i][4], LOW); //四号电磁阀，总阀门
    }
}


PneumaticSys::~PneumaticSys()
{
  Serial.println("Done!");
}

void PneumaticSys::enableNormalPneumatic(int i)
{
	digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],LOW);
    digitalWrite(SV[i][3],HIGH);
    digitalWrite(SV[i][4],HIGH);
}

void PneumaticSys::enablePositivePneumatic(int i)
{
    digitalWrite(SV[i][1],HIGH);
    digitalWrite(SV[i][2],LOW);
    digitalWrite(SV[i][3],LOW);
    digitalWrite(SV[i][4],HIGH);
}

void PneumaticSys::enableNegtivePneumatic(int i)
{
    digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],HIGH);
    digitalWrite(SV[i][3],LOW);
    digitalWrite(SV[i][4],HIGH);
}

void PneumaticSys::holdPressure(int i)
{
    digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],LOW);
    digitalWrite(SV[i][3],LOW);
    digitalWrite(SV[i][4],LOW);
}
