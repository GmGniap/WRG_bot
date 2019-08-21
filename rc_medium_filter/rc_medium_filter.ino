#include <ATX2.h>	// ATX2 Board
#include <medianFilter.h>
medianFilter Filter;
int value;
int filtered;

int ch1 =13;
int ch2 =14;
int ch3 =15;
int ch4 =9;

void setup() {
  XIO();	// ATX2 initialize
  OK();
  // user setup code below this line..
pinMode(ch1,INPUT);
pinMode(ch2,INPUT);
pinMode(ch3,INPUT);
pinMode(ch4,INPUT);
Serial.begin(115200);
Filter.begin()
}

void loop() {
  // user loop code below this line..
value = pulseIn(ch1, HIGH, 25000);
filtered = Filter.run(value);
Serial.print("In: ");
Serial.print(value);
Serial.print(" - Out: ");
Serial.println(filtered);
delay(10);
/*double rc1 = pulseIn(ch1, HIGH, 25000);
double rc2 = pulseIn(ch2, HIGH, 25000);
double rc3 = pulseIn(ch3, HIGH, 25000);
double rc4 = pulseIn(ch4, HIGH, 25000);

Serial.print("rc1: ");
Serial.print(rc1);
Serial.print("|");
Serial.print("rc2:");
Serial.print(rc2);
Serial.print("|");
Serial.print("rc3:");
Serial.print(rc3);
Serial.print("|");
Serial.print("rc4: ");
Serial.print(rc4);
Serial.println("|");*/
}
