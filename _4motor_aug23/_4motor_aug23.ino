#include <ATX2.h>

//RIGHT MOTOR0
#define DRIVER2_IN1 6  
#define DRIVER2_IN2 5  
#define DRIVER2_IN3 4 
#define DRIVER2_IN4 7

//LEFT MOTOR
#define DRIVER1_IN1 19   //19  
#define DRIVER1_IN2 16   //16
//#define DRIVER1_EN1 13

#define DRIVER1_IN3 20 
#define DRIVER1_IN4 17
//#define DRIVER1_EN2 14

#define ch1 13
#define ch2 14

const int numReadings = 5;
int readings_ch1[numReadings];      // the readings from the analog input
int readings_ch2[numReadings];
int readIndex = 0;              // the index of the current reading
int total_ch1 = 0;                  
int total_ch2 = 0;
int average_ch1 = 0;                
int average_ch2 = 0;


/*void RC();
void FW(int pwm);
void BW(int pwm);
void TUL(int pwm);
void TUR(int pwm);
void STOP();*/


void setup(){
  //OK();
  XIO();
  pinMode(DRIVER2_IN1,OUTPUT);
  pinMode(DRIVER2_IN2,OUTPUT);
  
  pinMode(DRIVER2_IN4,OUTPUT);
  pinMode(DRIVER2_IN3,OUTPUT);
  
  pinMode(DRIVER1_IN1,OUTPUT);
  pinMode(DRIVER1_IN2,OUTPUT);
  //pinMode(DRIVER1_EN1,OUTPUT);
  
  pinMode(DRIVER1_IN4,OUTPUT);
  pinMode(DRIVER1_IN3,OUTPUT);
  //pinMode(DRIVER1_EN2,OUTPUT);
  
  pinMode(ch1,INPUT);
  pinMode(ch2,INPUT);
  Serial.begin(9600);
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings_ch1[thisReading] = 0;
    readings_ch2[thisReading] = 0;
  }
}

//  average_ch1 = total_ch1 / numReadings;
//  average_ch2 = total_ch2 / numReadings;
//  Serial.print("Average RC1: ");
//  Serial.print(average_ch1);
//  Serial.print(" Average RC2: ");
//  Serial.println(average_ch2);
//  glcd(0,1,"%d",average_ch1);
//  glcd(1,1,"%d",average_ch2);
//  if(average_ch2 > 1400 && average_ch2 < 1600 && average_ch1 > 1400 && average_ch1 < 1600)
//  {
//    STOP();
//  }
//  else if(average_ch2 > 1600 && average_ch2 <= 2900 )
//  {
//      int pwm = map(average_ch2, 1600, 2900, 150, 255); //map our speed to 0-255 range
//      FW(pwm);
//  }
//  else if(average_ch2 < 1600 && average_ch2 >= 800)
//  {
//   int pwm = map(average_ch2, 800, 1600, 150, 255); 
//   BW(pwm);
//  }
//  else if(average_ch2 <= 9999 && average_ch2 >= 8999){
//   int pwm = map(average_ch2/1000.0,800,1600,150,255);
//   BW(pwm);
//  }
//  else if(average_ch1 > 1600 && average_ch1 <= 2900)
//  {
//  int pwm = map(average_ch2, 1600, 2900, 150, 255); //map our speed to 0-255 range
//  TUL(pwm);
//  }
//  else if(average_ch1 < 1600 && average_ch1 >= 800)
//  {
//  int pwm = map(average_ch2, 800, 1600, 150, 255); 
//  TUR(pwm);
//  }
void loop(){
  double rc1 = pulseIn(ch1, HIGH, 25000);
  double rc2 = pulseIn(ch2, HIGH, 25000);
  Serial.print("Normal RC1: ");
  Serial.print(rc1);
  Serial.print(" | ");
  Serial.print("Normal RC2: ");
  Serial.println(rc2);
  
  if(rc2 > 1400 && rc2 < 1600 && rc1 > 1400 && rc1 < 1600)
  {
    Serial.println("Stop");
  digitalWrite(DRIVER1_IN1,LOW); 
  digitalWrite(DRIVER1_IN2,LOW);
  //analogWrite(DRIVER1_EN1,100);
  digitalWrite(DRIVER2_IN1,LOW); 
  digitalWrite(DRIVER2_IN2,LOW);

  digitalWrite(DRIVER1_IN4,LOW); 
  digitalWrite(DRIVER1_IN3,LOW);
  //analogWrite(DRIVER1_EN2,100);
  digitalWrite(DRIVER2_IN4,LOW); 
  digitalWrite(DRIVER2_IN3,LOW);
 }
 
 else if(rc2 > 1600 && rc2 <= 2900 )
 {
   Serial.println("Forward");
  digitalWrite(DRIVER2_IN1,HIGH); //LEFT
  digitalWrite(DRIVER2_IN2,LOW);
  //analogWrite(DRIVER1_EN1,255);R
  digitalWrite(DRIVER2_IN4,HIGH); //RIGHT
  digitalWrite(DRIVER2_IN3,LOW);
  
  digitalWrite(DRIVER1_IN4,LOW); //RIGHT
  digitalWrite(DRIVER1_IN3,HIGH);
  //analogWrite(DRIVER1_EN2,255);
  digitalWrite(DRIVER1_IN1,HIGH); //RIGHT
  digitalWrite(DRIVER1_IN2,LOW);
 }
 else if (rc2 < 1600 && rc2 >= 800)
 {
  Serial.println("Reverse");
  digitalWrite(DRIVER1_IN1,HIGH); //LEFT-HIGH HIGH reverse
  digitalWrite(DRIVER1_IN2,HIGH);
  //analogWrite(DRIVER1_EN1,255);
  digitalWrite(DRIVER2_IN1,HIGH); //RIGHT-HIGH HIGH reverse
  digitalWrite(DRIVER2_IN2,HIGH);
  
  digitalWrite(DRIVER1_IN4,HIGH); //LEFT - reverse
  digitalWrite(DRIVER1_IN3,HIGH);
  //analogWrite(DRIVER1_EN2,255);
  digitalWrite(DRIVER2_IN4,HIGH); //RIGHT - reverse
  digitalWrite(DRIVER2_IN3,HIGH); 
 }
}
 
 /*
  char user_input;
  while(Serial.available())
  {
    user_input = Serial.read();
    if(user_input == '1')
    {
      Serial.println("Stop");
  digitalWrite(DRIVER1_IN1,LOW); 
  digitalWrite(DRIVER1_IN2,LOW);
  //analogWrite(DRIVER1_EN1,100);
  digitalWrite(DRIVER2_IN1,LOW); 
  digitalWrite(DRIVER2_IN2,LOW);

  digitalWrite(DRIVER1_IN4,LOW); 
  digitalWrite(DRIVER1_IN3,LOW);
  //analogWrite(DRIVER1_EN2,100);
  digitalWrite(DRIVER2_IN4,LOW); 
  digitalWrite(DRIVER2_IN3,LOW);
}
    else if(user_input == '3')
    {
      Serial.println("Reverse");
  digitalWrite(DRIVER1_IN1,HIGH); //LEFT-HIGH HIGH reverse
  digitalWrite(DRIVER1_IN2,HIGH);
  //analogWrite(DRIVER1_EN1,255);
  digitalWrite(DRIVER2_IN1,HIGH); //RIGHT-HIGH HIGH reverse
  digitalWrite(DRIVER2_IN2,HIGH);
  
  digitalWrite(DRIVER1_IN4,HIGH); //LEFT - reverse
  digitalWrite(DRIVER1_IN3,HIGH);
  //analogWrite(DRIVER1_EN2,255);
  digitalWrite(DRIVER2_IN4,HIGH); //RIGHT - reverse
  digitalWrite(DRIVER2_IN3,HIGH);
}
  else if(user_input == '2')
  {
  Serial.println("Forward");
  digitalWrite(DRIVER2_IN1,HIGH); //LEFT
  digitalWrite(DRIVER2_IN2,LOW);
  //analogWrite(DRIVER1_EN1,255);R
  digitalWrite(DRIVER2_IN4,HIGH); //RIGHT
  digitalWrite(DRIVER2_IN3,LOW);
  
  digitalWrite(DRIVER1_IN4,LOW); //RIGHT
  digitalWrite(DRIVER1_IN3,HIGH);
  //analogWrite(DRIVER1_EN2,255);
  digitalWrite(DRIVER1_IN1,HIGH); //RIGHT
  digitalWrite(DRIVER1_IN2,LOW);
  }
  }
}
*/


