#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define encoder0PinA 2
#define encoder0PinB 5
#define MotorPWM 8
#define MotorPin1 10
#define MotorPin2 11

long      counts = 0;//long 
float    actual_angleDegree, prv_actual_angleDegree, actual_angleRevolution;
float    desired_speedRPM, actual_speedRPM, actual_speedDegreeperSec;
float    now_time, samp_time, prv_time, Vsupply;
float    now_err, K, PWM, prv_err, Volt, UI, prv_UI;

void setup() {
  K = 0.15;
  Serial.begin(57600);
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(MotorPWM, OUTPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  digitalWrite(encoder0PinA, LOW);
  digitalWrite(encoder0PinB, LOW);
  attachInterrupt(digitalPinToInterrupt(2), readEncoder, CHANGE);
}

void readEncoder() {
  if (digitalRead(encoder0PinB) == digitalRead(encoder0PinA)) {
    counts = counts - 1;
  }
  else                                                        {
    counts = counts + 1;
  }
}

void loop() {
  now_time                 = micros() / 1000000.0;// micros
  samp_time                = now_time - prv_time;//t(n)-t(n-1)
  actual_angleDegree       = ((360.0 * 2.0) / (64*19)) * counts; // degree
  actual_angleRevolution   = actual_angleDegree / 360.0; // revolution
  actual_speedDegreeperSec = (actual_angleDegree - prv_actual_angleDegree) / samp_time;
  actual_speedRPM          = actual_speedDegreeperSec * (1 / 360.0) * (60); //
  desired_speedRPM         = 150.0*sin(2*PI*0.5*now_time); // revolution per minute
  now_err                  = desired_speedRPM -  actual_speedRPM;
  Volt                     = (K * now_err);
  PWM                      = (Volt / 12.0) * 255; // digital pin hold 8 bit register in Arduino.so, we multiply 255
  PWM                      = abs(PWM);
  if ( PWM > 255 ) {
    PWM = 255;
  }
  else             {
    PWM = PWM;
  }

  if (Volt > 0)  {
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, HIGH);
  }
  else if (Volt < 0)  {
    digitalWrite(MotorPin1, HIGH);
    digitalWrite(MotorPin2, LOW);
  }

  analogWrite (MotorPWM, PWM);//PWM
  prv_actual_angleDegree = actual_angleDegree; //update theta, prv_ = previous
  prv_time               = now_time;
  prv_err                = now_err;

// Serial.print ( actual_angleDegree);              Serial.print("  ");
//  Serial.print (samp_time);              Serial.print("  ");
  Serial.print (desired_speedRPM);      Serial.print("  ");
  Serial.print (actual_speedRPM);       Serial.print("  ");
//  Serial.print (now_err);               Serial.print("  ");
//  Serial.print (Volt);    Serial.print("  ");
  Serial.println("  ");
}



