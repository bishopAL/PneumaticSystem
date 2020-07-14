int SV1 = 3; //Solenoid valves电磁阀
int SV2 = 4;
int SV3 = 5;
int SV4 = 6;
int EPV = 9; //electric proportion valve电气比例阀
int FLAG;
void setup() {
  Serial.begin(9600);
  pinMode(SV1, OUTPUT); //一号电磁阀，电气比例阀
  pinMode(SV2, OUTPUT); //二号电磁阀，真空发生器
  pinMode(SV3, OUTPUT); //三号电磁阀，泄压阀
  pinMode(SV4, OUTPUT); //四号电磁阀，总阀门
  //pinMode(2,INPUT); //充气模式
  //pinMode(3,INPUT); //吸气模式
  pinMode(9,OUTPUT); //输出模拟信号给电气比例阀
  pinMode(A0,INPUT); //反馈
  digitalWrite(SV1,LOW);
  digitalWrite(SV2,LOW);
  analogWrite(EPV,0);
  Serial.setTimeout(50);
}

void enableNormalPneumatic()
{
    digitalWrite(SV1,LOW);
    digitalWrite(SV2,LOW);
    digitalWrite(SV3,HIGH);
    digitalWrite(SV4,HIGH);
}


void enablePositivePneumatic()
{
    digitalWrite(SV1,HIGH);
    digitalWrite(SV2,LOW);
    digitalWrite(SV3,LOW);
    digitalWrite(SV4,HIGH);
}


void enableNegtivePneumatic()
{
    digitalWrite(SV1,LOW);
    digitalWrite(SV2,HIGH);
    digitalWrite(SV3,LOW);
    digitalWrite(SV4,HIGH);
}


void disablePneumatic()
{
    digitalWrite(SV1,LOW);
    digitalWrite(SV2,LOW);
    digitalWrite(SV3,LOW);
    digitalWrite(SV4,LOW);
}

void loop() 
{
  String temp_string;
  if (Serial.available()>0)  //蓝牙发数字是调整当前气腔工作状态，FLAG 0：常压，1：充气，2：吸气
      {
        temp_string = Serial.readString();
        FLAG = temp_string.toInt();
        if (FLAG == 0)
        {
          enableNormalPneumatic();
          delay(1000);
          disablePneumatic();
          Serial.println("Normal-Pressure Mode actived.");
        }
        else if (FLAG == 1)
        {
          enablePositivePneumatic();
          delay(1000);
          disablePneumatic();
          Serial.println("Postive-Pressure Mode actived.");
        }
        else if(FLAG == 2)
        {
          enableNegtivePneumatic();
          delay(1000);
          disablePneumatic();
          Serial.println("Negtive-Pressure Mode actived.");
        }
      }
  
}
