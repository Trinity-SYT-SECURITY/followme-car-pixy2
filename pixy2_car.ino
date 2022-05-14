//Pixy arduino robot
//Arduino IDE 1.6.4

#include "Pixy2.h"
#include "SPI.h"
#include "Wire.h"

Pixy2 pixy;

int signature = 0;//簽名
int x = 0;                      //X
int y = 0;                      //y
unsigned int width = 0;         //寬度
unsigned int height = 0;        //高度
unsigned int area = 0; //區域
unsigned int newarea = 0;//新區域
int Xmin = 70;                  //min x position70
int Xmax = 180;                 //max x position180
int maxArea = 180;//180
int minArea = 0;
int MotorR_I1 = 8 ;//motor1 on Pin 8
int MotorR_I2 = 9 ;
int MotorR_ENA = 5;                //enable1 on Pin D5
int MotorL_I3 = 10;//motor2 on Pin10
int MotorL_I4 = 11; 
int MotorL_ENB = 6;                //enable2 on Pi
int SPEED_R = 255;//定義右輪速度
int SPEED_L = 255 ;//定義左輪速度                 //speed for motor
static int i = 0; //靜態

void setup()
{ 
  pinMode(MotorR_I1,OUTPUT);
  pinMode(MotorR_I2,OUTPUT);
  pinMode(MotorL_I3,OUTPUT);
  pinMode(MotorL_I4,OUTPUT);
  pinMode(MotorR_ENA,OUTPUT);
  pinMode(MotorL_ENB,OUTPUT);
  Serial.begin(115200);
  Stop();
  pixy.init();
}

void loop()
{ 
  while(millis()<5000)//5000
  {
    scan();
    area = width * height; //長寬計算
    maxArea = area + 1000;//大1000
    minArea = area - 1000;
  }

    scan(); //掃描 

//    
  if(signature == 2 )// 檢測簽名
 
  {
    newarea = width * height; //計算寬乘高
    
      if (x < Xmin)//左轉當X  < max X 
      {     
       left();
      }
      else if (x > Xmax) //右轉當X  >  max       
      {
       right();
      }
      else if(newarea < minArea)//前進當物體遠離
      {
       forward(); 
      }
    else if(newarea > maxArea)//後退當物體靠近
      {
     
    backward();// 後退 
      }
      
  else
      {
        Stop(); 
      } 
   }
   else
   {
    Stop();
     }
}



void backward()//backward
  {
   analogWrite(MotorR_ENA,SPEED_L);    //設定馬達轉速
    analogWrite(MotorL_ENB,SPEED_R);
    digitalWrite(MotorR_I1,LOW);    //馬達（右）逆時針轉動LOW
    digitalWrite(MotorR_I2,HIGH);//HIGH
    digitalWrite(MotorL_I3,HIGH);    //馬達（左）順時針轉動LOW
    digitalWrite(MotorL_I4,LOW);//HIGH
    
 }

void forward()//forward
  {
   digitalWrite(MotorR_I1,LOW);   //馬達（右）順時針轉動
    digitalWrite(MotorR_I2,LOW);
    digitalWrite(MotorL_I3,HIGH);   //馬達（左）逆時針轉動high
    digitalWrite(MotorL_I4,LOW);//LOW
  analogWrite(MotorR_ENA, SPEED_R);
  analogWrite(MotorL_ENB, SPEED_L);
  }

void left()//turn right
  {
    digitalWrite(MotorR_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorR_I2,HIGH);
    digitalWrite(MotorL_I3,HIGH);   //馬達（左）逆時針轉動
    digitalWrite(MotorL_I4,LOW);
      analogWrite(MotorR_ENA,SPEED_R/2);     //設定馬達轉速r/2
   analogWrite(MotorL_ENB, SPEED_L/2);//L/2
  }

void right()//turn left
  {
  digitalWrite(MotorR_I1,HIGH);   //馬達（右）順時針轉動
    digitalWrite(MotorR_I2,LOW);
    digitalWrite(MotorL_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorL_I4,HIGH);
 analogWrite(MotorR_ENA,SPEED_R);     //設定馬達轉速SPEED_R/2
    analogWrite(MotorL_ENB,SPEED_L);//SPEED_L/2
  }

void Stop()//stop
  {
  digitalWrite(MotorR_I1,LOW);   //馬達（右）停止轉動
    digitalWrite(MotorR_I2,LOW);
    digitalWrite(MotorL_I3,LOW);   //馬達（左）停止轉動
    digitalWrite(MotorL_I4,LOW);
  }
void scan()
  {
  uint16_t blocks;
 pixy.ccc.getBlocks();  //receive data from pixy 
  signature = pixy.ccc.blocks[i].m_signature;    //
  x = pixy.ccc.blocks[i].m_x;                    //get x position
  y = pixy.ccc.blocks[i].m_y;                    //get y position
  width = pixy.ccc.blocks[i].m_width;            //get width
  height = pixy.ccc.blocks[i].m_height;          //get height
  }  
