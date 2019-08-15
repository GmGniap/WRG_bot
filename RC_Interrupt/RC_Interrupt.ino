#define SIGNAL 30
#define NEUTRAL 1500

volatile int nSIGNAL = NEUTRAL;
volatile unsigned long PERIOD = 0;
volatile boolean newSIGNAL = false;
void setup() {
  // put your setup code here, to run once:
  attachInterrupt(SIGNAL,calcInput,CHANGE);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(newSIGNAL)
{
  Serial.println(SIGNAL);
  newSIGNAL = false;
}
}

void calcInput()
{
  if(digitalRead(SIGNAL == HIGH))
  {
    PERIOD = micros();
  }
  else
  {
    if(PERIOD && (newSIGNAL == false))
    {
      nSIGNAL =(int)(micros() - PERIOD);
      PERIOD = 0;
      newSIGNAL = true;
    }
  }
}
