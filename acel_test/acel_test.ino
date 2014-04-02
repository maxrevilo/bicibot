#include <Arduino.h>
#include <Servo.h>
#include <SoftTimer.h>
#include "AcceleroMMA7361.h"


AcceleroMMA7361 accelero;
int x, y ,z;
//int dx, dy ,dz;

void fun_print_accel(Task* me);
Task task_print_accel(100, fun_print_accel);

int xPin = A5, yPin = A4, zPin = A3;

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
    x = (analogRead(xPin));
    y = (analogRead(yPin));
    z = (analogRead(zPin));
    //x = (100 * (analogRead(xPin) - 506)) / 64;
    //y = (100 * (analogRead(yPin) - 524)) / 64;
    //z = (100 * (analogRead(zPin) - 539)) / 64;
    /*
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" \ty: ");
    Serial.print(y);
    Serial.print(" \tz: ");
    Serial.print(z);
    Serial.print(" \tM: ");
    Serial.print(accelero.getTotalVector());
    Serial.println("\t");
    */
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
}
