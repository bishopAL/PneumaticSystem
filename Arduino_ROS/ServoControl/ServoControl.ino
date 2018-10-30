/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>

ros::NodeHandle  nh;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


class Servocontrol: public Servo
{
public:
  int present_pos = 90;
  int delay_per_degree = 15;
  void setNewPosition(int newpos){
    if (present_pos <= newpos){
    for (int i = present_pos; i <= newpos; i++){
      write(i);
      delay(delay_per_degree); 
      }
    }
    else{
      for (int i = present_pos; i >= newpos; i--){
      write(i);
      delay(delay_per_degree); 
      }
    }
    present_pos = newpos;
  }
};


Servocontrol servo0;//for the joint on Pri_Base
Servocontrol servo1;//for another joint
Servo myservo0;//for end effecter
Servo myservo1; 
Servo myservo2;
Servo myservo3;

#define pls 3
#define dir 4
#define ena 5

void servo_cb0( const std_msgs::UInt16& cmd_msg0){
  //servo0.write(cmd_msg0.data); //set servo angle, should be from 0-180 
  servo0.setNewPosition(cmd_msg0.data);
  lcd.setCursor(8,0);
  lcd.print(cmd_msg0.data); 
  //digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}
void servo_cb1( const std_msgs::UInt16& cmd_msg1){
  //servo1.write(cmd_msg1.data); //set servo angle, should be from 0-180 
  servo1.setNewPosition(cmd_msg1.data);
  lcd.setCursor(8,1);
  lcd.print(cmd_msg1.data); 
  //digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}
void stepperup_cb( const std_msgs::Bool& cmd_msg2){
  if (cmd_msg2.data == true)
    {
        digitalWrite(pls,HIGH);
        digitalWrite(dir,LOW);
        digitalWrite(ena,HIGH);
        tone(pls,800);
        digitalWrite(13, HIGH-digitalRead(13));
    }
  
}


void stepperdown_cb( const std_msgs::Bool& cmd_msg3){
  if (cmd_msg3.data == true)
    {
        digitalWrite(pls,HIGH);
        digitalWrite(dir,HIGH);
        digitalWrite(ena,HIGH);
        tone(pls,800);
        digitalWrite(13, HIGH-digitalRead(13));
    }
  
}


void stepperstop_cb( const std_msgs::Bool& cmd_msg4){
  if (cmd_msg4.data == true)
    {
        digitalWrite(ena,LOW);
        digitalWrite(13, HIGH-digitalRead(13));
    }
  
}

void end_cb( const std_msgs::UInt16& cmd_msg5){
  int a;
  a = cmd_msg5.data;
  if (a == 1){
      myservo0.write(90);//初始化
      myservo1.write(90);
      myservo2.write(90);
      myservo3.write(90);
    }
    if (a == 2){
      myservo0.write(100);//张角15°
      myservo3.write(80);
    }
    if (a == 3){
      myservo0.write(110);//张角30°
      myservo3.write(70);
    }
    if (a == 4){
      myservo0.write(120);//张角45°
      myservo3.write(60);
    }
    if (a == 5){
      myservo0.write(130);//张角60°
      myservo3.write(50);
    }
    if (a == 6){
      myservo0.write(140);//张角75°
      myservo3.write(40);
    }
    if (a == 7){
      myservo0.write(150);//张角90°
      myservo3.write(30);
    }
    if (a == 8){
      myservo1.write(136);//黏附：约70度
      myservo2.write(44);
    }
    if (a == 9){
      myservo1.write(90);//脱附
      myservo2.write(90);
    }
    
}


ros::Subscriber<std_msgs::UInt16> sub0("servo0", servo_cb0);
ros::Subscriber<std_msgs::UInt16> sub1("servo1", servo_cb1);
ros::Subscriber<std_msgs::Bool> sub2("stepperUP", stepperup_cb);
ros::Subscriber<std_msgs::Bool> sub3("stepperDOWN", stepperdown_cb);
ros::Subscriber<std_msgs::Bool> sub4("stepperSTOP", stepperstop_cb);
ros::Subscriber<std_msgs::UInt16> sub5("endeffecter", end_cb);

void setup(){
  pinMode(pls, OUTPUT);//Stepper Motor
  pinMode(dir, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(ena, LOW);
  
  lcd.init(); 
  
  nh.initNode();
  nh.subscribe(sub0);
  nh.subscribe(sub1);//for servo
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);//for stepper motor
  nh.subscribe(sub5);//for end effecter
  
  servo0.attach(7); //attach it to pin 10
  servo1.attach(8); //attach it to pin 11
  myservo0.attach(9);
  myservo1.attach(10);
  myservo2.attach(11);
  myservo3.attach(12);
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("srv0:");
  lcd.setCursor(8,0);
  lcd.print(0);
  
  lcd.setCursor(1,1);
  lcd.print("srv1:");
  lcd.setCursor(8,1);
  lcd.print(0);
  servo0.write(90);
  servo1.write(90);
}

void loop(){
  nh.spinOnce();
  delay(1);
}
