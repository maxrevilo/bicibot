#include "consts.h"
#include <Arduino.h>
#include <Servo.h>
#include <SoftTimer.h>
#include "AcceleroMMA7361.h"
#include "Power.h"
#include "Actuators.h"


AcceleroMMA7361 accelero;
int x, y ,z;
int pos = 0;
int dir = 1;

Power power;
Actuators actuators;

void print_accel(Task* me);
Task accel_update(1000, print_accel);

void setup() {
    Serial.begin(115200);
    Serial.println("Initiating...");

    power.begin();
    
    accelero.begin(13, 12, 7, 4, A2, A1, A0);
    accelero.calibrate();
    SoftTimer.add(&accel_update);
    
    actuators.calibrate();
    actuators.begin();
    
    Serial.println("Initiated");
    power.turn_on();
}

void print_accel(Task* me)
{
    x = accelero.getXAccel();
    y = accelero.getYAccel();
    z = accelero.getZAccel();
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" \ty: ");
    Serial.print(y);
    Serial.print(" \tz: ");
    Serial.print(z);
    Serial.println("\tG*10^-2");

    //actuators.getRightPosition();
    //actuators.getLeftPosition();
}


