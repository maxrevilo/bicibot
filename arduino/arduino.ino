#include <SoftTimer.h>
#include <Servo.h>
#include "AcceleroMMA7361.h"

Servo head_act;
Servo right_act;
Servo left_act;

const int ok_led = 2;

void turnOn(Task* me) { digitalWrite(ok_led, HIGH); }
void turnOff(Task* me) { digitalWrite(ok_led, LOW); }
Task taskOn(2000, turnOn);
Task taskOff(1111, turnOff);

AcceleroMMA7361 accelero;
int x, y ,z;

Task servo_update(5, servo_loop);
Task accel_update(500, print_accel);

int pos = 0;
int dir = 1;
void servo_loop(Task* me) {
  if(dir > 0) pos += 1;
  else pos -= 1;
  if(pos >= 180) dir = -1;
  else if(pos <= 0) dir = 1;
  
  /*Serial.print("R: ");
  Serial.print(analogRead(3));
  Serial.print(", L: ");
  Serial.print(analogRead(4));
  Serial.println(".");*/
  head_act.write(pos);
  right_act.write(pos);
  left_act.write(pos);
}

void print_accel(Task* me)
{
  x = accelero.getXAccel();
  y = accelero.getYAccel();
  z = accelero.getZAccel();
  Serial.print("\nx: ");
  Serial.print(x);
  Serial.print(" \ty: ");
  Serial.print(y);
  Serial.print(" \tz: ");
  Serial.print(z);
  Serial.print("\tG*10^-2");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initiating...");
  // "OK" Led:
  pinMode(ok_led, OUTPUT);
  
  //Ok Led callbacks
  SoftTimer.add(&taskOn);
  SoftTimer.add(&taskOff);
  
  
  head_act.attach(11);
  right_act.attach(10);
  left_act.attach(9);
  SoftTimer.add(&servo_update);
  
  accelero.begin(13, 12, 7, 4, A2, A1, A0);
  accelero.calibrate();
  SoftTimer.add(&accel_update);
  
  Serial.println("Initiated");
}


