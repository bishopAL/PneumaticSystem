#include "PneumaticSys.hpp"
#include "Arduino.h"

PneumaticSys::PneumaticSys()
{
    for(int i=0; i<4; i++)  //i=0:4 <-> 脚顺序：LF RF RH LH
    {
        for(int j=0; j<3; j++)
        {
            SV[i][j] = i*3 + j + 2;
        }
    }
    SV[3][0] = SV[3][0] + 3; //最后三个电磁阀用14，15，16，把digital口给电气比例阀用
    SV[3][1] = SV[3][1] + 3;
    SV[3][2] = SV[3][2] + 3;
  	for(int i=0; i<4; i++)
  	{
  		pinMode(SV[i][0], OUTPUT); //一号电磁阀，正压气路 所有电磁阀设为断电常闭
   		pinMode(SV[i][1], OUTPUT); //二号电磁阀，负压气路
      pinMode(SV[i][2], OUTPUT); //三号电磁阀，泄压阀
      //pinMode(SV[i][3], OUTPUT); //四号电磁阀，总阀门
  	}
    for(int i=0; i<4; i++)
    {
        digitalWrite(SV[i][0], LOW); //一号电磁阀，正压气路 所有电磁阀设为断电常闭
        digitalWrite(SV[i][1], LOW); //二号电磁阀，负压气路
        digitalWrite(SV[i][2], LOW); //三号电磁阀，泄压阀
        //digitalWrite(SV[i][3], LOW); //四号电磁阀，总阀门
    }
    pinMode(12, OUTPUT); // 电气比例阀1号，负责充气气压
    pinMode(13, OUTPUT); // 电气比例阀2号，负责吸气气压
}


PneumaticSys::~PneumaticSys()
{
  Serial.println("Done!");
}

void PneumaticSys::enableNormalPneumatic(int i) // 
{
	  digitalWrite(SV[i][0],LOW);
    digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],HIGH);
    //digitalWrite(SV[i][3],HIGH);
}

void PneumaticSys::enablePositivePneumatic(int i)
{
    digitalWrite(SV[i][0],HIGH);
    digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],LOW);
    //digitalWrite(SV[i][3],HIGH);
}

void PneumaticSys::enableNegtivePneumatic(int i)
{
    digitalWrite(SV[i][0],LOW);
    digitalWrite(SV[i][1],HIGH);
    digitalWrite(SV[i][2],LOW);
    //digitalWrite(SV[i][3],HIGH);
}

void PneumaticSys::holdPressure(int i)
{
    digitalWrite(SV[i][0],LOW);
    digitalWrite(SV[i][1],LOW);
    digitalWrite(SV[i][2],LOW);
    //digitalWrite(SV[i][3],LOW);
}
