#include "consts.h"
#include <Arduino.h>
#include <Servo.h>
#include <EEPROM.h>
#include <SoftTimer.h>
#include "Settings.h"
#include "AcceleroMMA7361.h"
#include "Power.h"
#include "Actuators.h"

Settings settings;

AcceleroMMA7361 accelero;
int x, y ,z;

Power power;
Actuators actuators;

int YOffset = 0;

void print_accel(Task* me);
Task accel_update(1000, print_accel);

void update_head(Task* me);
Task accel_head(0, update_head);

void setup() {
    Serial.begin(115200);
    Serial.println("Initiating...");

    //settings.load();

    power.begin(&settings);
    
    accelero.begin(13, 12, 7, 4, A2, A1, A0);
    accelero.calibrate();
    YOffset = accelero.getYRaw();
    //SoftTimer.add(&accel_update);
    SoftTimer.add(&accel_head);
    
    //actuators.calibrate();
    //actuators.begin(&settings);
    
    Serial.println("Initiated");
    power.turn_on();
}

void update_head(Task* me)
{
    int movement = (accelero.getYRaw()-YOffset) / 2 * 7; // 7/2 ~ (1000/300);
    actuators.moveHead(movement);
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
}


