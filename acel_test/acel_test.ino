#include <Arduino.h>
#include <Servo.h>
#include <SoftTimer.h>
#include "AcceleroMMA7361.h"


AcceleroMMA7361 accelero;
int x, y ,z;
int dx, dy ,dz;

void fun_print_accel(Task* me);
Task task_print_accel(100, fun_print_accel);


void setup() {
    Serial.begin(115200);
    Serial.println("Initiating...");
    
    accelero.begin(13, 12, 7, 2, A2, A1, A0);

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
    // x = dx + accelero.getXVolt();
    // y = dy + accelero.getYVolt();
    // z = dz + accelero.getZVolt();
    x = (100 * (analogRead(A2) - 550)) / 250;
    y = (100 * (analogRead(A1) - 580)) / 250;
    z = (100 * (analogRead(A0) - 460)) / 256;
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
