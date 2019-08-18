#include <ATX2.h>	// ATX2 Board
#define BRAKE 0
#define CW    1
#define CCW   2
//#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 6
#define MOTOR_B1_PIN 7
#define PWM_MOTOR_1 19

//MOTOR 2
#define MOTOR_A2_PIN 14
#define MOTOR_B2_PIN 13
#define PWM_MOTOR_2 15

//MOTOR 3
#define MOTOR_A3_PIN 11
#define MOTOR_B3_PIN 11
#define PWM_MOTOR_3 11

//MOTOR 4
#define MOTOR_A4_PIN 11
#define MOTOR_B4_PIN 11
#define PWM_MOTOR_4 11

//#define EN_PIN_1 30
#define MOTOR_1 0
#define MOTOR_2 1
#define MOTOR_3 2
#define MOTOR_4 3

short usSpeed = 200;  //default motor speed
unsigned short usMotor_Status = BRAKE;
 
void setup()                         
{
  XIO();
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
  //pinMode(EN_PIN_1, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);
  
  //Motor 3 Pinout
  pinMode(MOTOR_A3_PIN, OUTPUT);
  pinMode(MOTOR_B3_PIN, OUTPUT);
  pinMode(PWM_MOTOR_3, OUTPUT);
  
  //Motor 4 Pinout
  pinMode(MOTOR_A4_PIN, OUTPUT);
  pinMode(MOTOR_B4_PIN, OUTPUT);
  pinMode(PWM_MOTOR_4, OUTPUT);
  
  Serial.begin(9600);              // Initiates the serial to do the monitoring 
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. FORWARD");
  Serial.println("3. REVERSE");
  Serial.println("4. READ CURRENT");
  Serial.println("+. INCREASE SPEED");
  Serial.println("-. DECREASE SPEED");
  Serial.println();

}

void loop() 
{
  char user_input;   

  
  
  while(Serial.available())
  {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    //digitalWrite(EN_PIN_1, HIGH);
     
    if (user_input =='1')
    {
       Stop();
    }
    else if(user_input =='2')
    {
      Forward();
    }
    else if(user_input =='3')
    {
      Reverse();
    }
    else if(user_input =='+')
    {
      IncreaseSpeed();
    }
    else if(user_input =='-')
    {
      DecreaseSpeed();
    }
    else
    {
      Serial.println("Invalid option entered.");
    }
      
  }
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
  motorGo(MOTOR_2, usMotor_Status, 0);
  motorGo(MOTOR_3, usMotor_Status, 0);
  motorGo(MOTOR_4, usMotor_Status, 0);
}

void Forward()
{
  Serial.println("Forward");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void Reverse()
{
  Serial.println("Reverse");
  usMotor_Status = CCW;
  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void IncreaseSpeed()
{
  usSpeed = usSpeed + 10;
  if(usSpeed > 255)
  {
    usSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void DecreaseSpeed()
{
  usSpeed = usSpeed - 10;
  if(usSpeed < 0)
  {
    usSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
  motorGo(MOTOR_2, usMotor_Status, usSpeed);
  motorGo(MOTOR_3, usMotor_Status, usSpeed);
  motorGo(MOTOR_4, usMotor_Status, usSpeed);
}

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
  else if(motor == MOTOR_2)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A2_PIN, LOW); 
      digitalWrite(MOTOR_B2_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A2_PIN, HIGH);
      digitalWrite(MOTOR_B2_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A2_PIN, LOW);
      digitalWrite(MOTOR_B2_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_2, pwm); 
  }
  else if(motor == MOTOR_3)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A3_PIN, LOW); 
      digitalWrite(MOTOR_B3_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A3_PIN, HIGH);
      digitalWrite(MOTOR_B3_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A3_PIN, LOW);
      digitalWrite(MOTOR_B3_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_3, pwm); 
  }
  else if(motor == MOTOR_4)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A4_PIN, LOW); 
      digitalWrite(MOTOR_B4_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A4_PIN, HIGH);
      digitalWrite(MOTOR_B4_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A4_PIN, LOW);
      digitalWrite(MOTOR_B4_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_4, pwm); 
  }
}
