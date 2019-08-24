#include <ATX2.h>	// ATX2 Board
/*
#define DRIVER1_IN1 19
#define DRIVER1_IN2 16
#define DRIVER1_IN3 17
#define DRIVER1_IN4 20
#define DRIVER1_EN1 15
#define DRIVER1_EN2 30


#define DRIVER2_IN1 6
#define DRIVER2_IN2 5
#define DRIVER2_IN3 4
#define DRIVER2_IN4 7 
#define DRIVER2_EN1 14
#define DRIVER2_EN2 13
*/
//RC channel Pins
int ch1 =13;
int ch2 =15;
int ch3 =14;
int ch4 =24;

//Averaging
const int numReadings = 5;
int readings_ch1[numReadings];      // the readings from the analog input
int readings_ch2[numReadings];
/*int readings_ch3[numReadings];
int readings_ch4[numReadings];*/
int readIndex = 0;              // the index of the current reading

int total_ch1 = 0;                  
int total_ch2 = 0;
/*int total_ch3 = 0;
int total_ch4 = 0;*/
int average_ch1 = 0;                
int average_ch2 = 0;
/*int average_ch3 = 0;
int average_ch4 = 0;*/


void setup() {
  XIO();
  /*pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(19,OUTPUT);
  pinMode(20,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(30,OUTPUT);*/
  
  pinMode(ch1,INPUT);
  pinMode(ch2,INPUT);
  /*pinMode(ch3,INPUT);
  pinMode(ch4,INPUT);*/
  Serial.begin(9600);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings_ch1[thisReading] = 0;
    readings_ch2[thisReading] = 0;
    /*readings_ch3[thisReading] = 0;
    readings_ch4[thisReading] = 0;*/
  }
}

void loop() {
  
  total_ch1 = total_ch1 - readings_ch1[readIndex];
  total_ch2 = total_ch2 - readings_ch2[readIndex];
  /*total_ch3 = total_ch3 - readings_ch3[readIndex];
  total_ch4 = total_ch4 - readings_ch3[readIndex];*/
  /*double rc1 = pulseIn(ch1, HIGH, 25000);
  double rc2 = pulseIn(ch2, HIGH, 25000);
  double rc3 = pulseIn(ch3, HIGH, 25000);
  double rc4 = pulseIn(ch4, HIGH, 25000);*/
  readings_ch1[readIndex] = pulseIn(ch1, HIGH, 25000);
  readings_ch2[readIndex] = pulseIn(ch2, HIGH, 25000);
  /*readings_ch3[readIndex]= pulseIn(ch3, HIGH, 25000);
  readings_ch4[readIndex]= pulseIn(ch4, HIGH, 25000);*/
  
  total_ch1= total_ch1 + readings_ch1[readIndex];
  total_ch2= total_ch2 + readings_ch2[readIndex];
  /*total_ch3= total_ch3 + readings_ch3[readIndex];
  total_ch4= total_ch4 + readings_ch4[readIndex];*/
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  
  average_ch1 = total_ch1 / numReadings;
  average_ch2 = total_ch2 / numReadings;
  /*average_ch3 = total_ch3 / numReadings;
  average_ch4 = total_ch4 / numReadings;*/
  Serial.print(" AVG RC1: ");
  Serial.print(average_ch1);
  Serial.print(" | ");
  Serial.print(" AVG RC2: ");
  Serial.println(average_ch2);
  /*Serial.print(" | ");
  Serial.print(" AVG RC3: ");
  Serial.print(average_ch3);
  Serial.print(" | ");
  Serial.print(" AVG RC4: ");
  Serial.println(average_ch4);*/
  delay(10);
  
  /*
  if(rc4==0){
      Serial.println(" no signal");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enable1, 0);
  }
  else if(rc4 > 1530){ //right stick
      pwm = map(rc4, 1530, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enable1, pwm);
      Serial.print(" right stick speed: ");
      Serial.println(pwm);
  }
  else if(rc4 < 1460){
      pwm = map(rc4, 1460, 1000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" left stick speed: ");
      Serial.println(pwm);
  }else{
      Serial.println(" stick centered");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enable1, 0);
  }
  
  delay(10);*/
}
