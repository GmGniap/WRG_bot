#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define encoder0PinA 2
#define encoder0PinB 5

#define MotorPWM  8
#define MotorPin1 10
#define MotorPin2 11

int       counts = 0.0;
double    MotorVolt, myBit, Vsupply, myFreq;
double    now_time, now_act_angle, des_angle, now_error;
double    samplingTime, prv_time, prv_error, edot;

void setup() {
  myFreq          = 10.0;
  Serial.begin(9600);
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(MotorPWM, OUTPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  digitalWrite(encoder0PinA, LOW);
  digitalWrite(encoder0PinB, LOW);
  attachInterrupt(0, readEncoder, CHANGE);
}

void readEncoder()
{
  if (digitalRead(encoder0PinB) == digitalRead(encoder0PinA))
  {
    counts = counts - 1;
  }
  else
  {
    counts = counts + 1;
  }
}

void loop() {
  now_time    = millis() / 1000.0;
  now_act_angle = ( (360.0*2.0) / (64*19.0)) * counts;
  des_angle = 90.0*sin(2*PI*0.9*now_time);
  
  now_error = des_angle - now_act_angle;
   
  edot      = (now_error - prv_error)/(now_time - prv_time); // viscus fricition eqn; in Physics  // Watch this eqn; if don't know, Ask Sayar  // Why this happen oil?
  
  MotorVolt = 0.2*now_error + 0.01*edot;      // edot is force is proportional to velocity/speed
  myBit     = (abs(MotorVolt) / 12.0) * 255;
  if (myBit > 255)  {
    myBit = 255;
  }
  else              {
    myBit = myBit;
  }
  if (MotorVolt > 0)  {
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, HIGH);
  }
  else          {
    digitalWrite(MotorPin1, HIGH);
    digitalWrite(MotorPin2, LOW);
  }
  analogWrite(MotorPWM, myBit);

  Serial.print (now_act_angle);
  Serial.print(" ");
  Serial.print (des_angle);
  Serial.print(" "); 
  Serial.println(" ");
  prv_error = now_error;
  prv_time  = now_time;
}

