int sv1=2;
int sv2=4;
float b_avgf,a_tgt;
int b_avgi,a;
int mark,flag=0;//flag=1时是打气模式，flag=2是吸气模式d
int blf=9;
String a_tgt2;
void setup() {
  Serial.begin(9600);
pinMode(sv1,OUTPUT);//一号电磁阀，电气比例阀
pinMode(sv2,OUTPUT);//二号电磁阀，真空发生器
//pinMode(2,INPUT);//充气模式
//pinMode(3,INPUT);//吸气模式
pinMode(9,OUTPUT);//输出模拟信号给电气比例阀
pinMode(A0,INPUT);//反馈
digitalWrite(sv1,LOW);
digitalWrite(sv2,LOW);
analogWrite(blf,0);
Serial.setTimeout(50);
}

void loop() 
{
      if (Serial.available()>0)//蓝牙发数字是调节气压，c是关阀，d是打气，f是放气
      {
        mark=int(Serial.read()-'0');
        //Serial.println(mark);
        delay(20);
        if(mark>=0&&mark<=9)
        {
            a_tgt=0;
            delay(20);
//           while (Serial.available()>0)//启动前设定气压，输入值为目标气压乘1000,然后随便第一位打数字，比如05，050，0120
//            {
//              a_tgt=a_tgt*10+(int(Serial.read() - '0'));
//   
//              delay(20);
//            }
            a_tgt2 = Serial.readString();
            a_tgt = a_tgt2.toInt();
            a_tgt=a_tgt/1000;
            a=int(a_tgt/0.9*255);
            analogWrite(blf,a);
            Serial.print("当前目标气压为：");
            Serial.println(a_tgt,4);
            Serial.println(a,4);
            delay(400);//180329 1726新加的
         }
         else if(mark=='c'-'0')
         {
          flag=3;
            Serial.println("close!"); 
            digitalWrite(sv1,LOW);
            digitalWrite(sv2,LOW);
            analogWrite(blf,0);

         }
         else if(mark=='d'-'0')
         {
            flag=1;Serial.println("打气!");
          }
         else if(mark=='f'-'0')
         {
            flag=2;Serial.println("吸气!");
            digitalWrite(sv1,LOW);
            digitalWrite(sv2,HIGH);        
            analogWrite(blf,0);
          }

      }
      if(flag==1)
      {   
          int i;
          digitalWrite(sv1,HIGH);
          digitalWrite(sv2,LOW);        
//          b_avgi=0;
//          for(i=0;i<=19;i++)
//          {
//             b_avgi=b_avgi+analogRead(A0);
//             delay(10);
//           }
//          b_avgf=b_avgi/20;//均值滤波       
//          b_avgf=0.0011*b_avgf-0.24;//非常重要的比例公式，让模拟值转为气压值
//          if(((a/255)*0.9)<=1.2*a_tgt&&((a/255)*0.9)>=0.8*a_tgt)//如果离初始值距离过大。就停止调节
//            {
//             a=a-(b_avgf-a_tgt)*255/3;//除以3是比例系数
//             Serial.print("反馈值");
//             Serial.println(b_avgf,4);
//             Serial.print("给定值");
//             Serial.println(a_tgt,4);
//             Serial.print("输出量");
//             Serial.println(a);
//             Serial.println(' ');
//             analogWrite(9,a); 
//             }
      }
      if(flag==2)
      {
          digitalWrite(sv1,LOW);
          digitalWrite(sv2,HIGH);        
          analogWrite(blf,0);
      }
      if(flag==3)
      {            
            digitalWrite(sv1,LOW);
            digitalWrite(sv2,LOW);
            analogWrite(blf,0);
       }

}
