#include <Arduino.h>
#include <Servo.h>
#include <SoftTimer.h>
#include "AcceleroMMA7361.h"


AcceleroMMA7361 accelero;
int x, y ,z;
//int dx, dy ,dz;

void fun_print_accel(Task* me);
Task task_print_accel(100, fun_print_accel);

int xPin = A2, yPin = A1, zPin = A0;

void setup() {
    Serial.begin(115200);
    Serial.println("Initiating...");
    
    accelero.begin(13, 12, 7, 2, xPin, yPin, zPin);

    /*
    accelero.calibrate();
    accelero.setAveraging(5000);
    x = accelero.getXAccel();
    y = accelero.getYAccel();
    z = accelero.getZAccel();
    accelero.setAveraging(10);
    dx = -x;
    dy = -y;
    dz = -(100 + z);
    */
    
    Serial.println("Initiated");
    SoftTimer.add(&task_print_accel);
}

void fun_print_accel(Task* me)
{
    //x = (analogRead(xPin));
    //y = (analogRead(yPin));
    //z = (analogRead(zPin));
    
    x = analogRead(xPin) -75;
    y = analogRead(yPin) -78;
    z = analogRead(zPin) +126;

    x = (30 * (analogRead(xPin) -75  -512)) / 128 * 5 / 4;
    y = (30 * (analogRead(yPin) -78  -512)) / 128 * 5 / 4;
    z = (30 * (analogRead(zPin) +126  -512)) / 128 * 5 / 4;

    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
}
