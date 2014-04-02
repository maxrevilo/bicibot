#include "consts.h"
#include <Arduino.h>

const float MATH_PI = 3.14159265359;
const float MATH_TWO_PI = 6.28318530718;
const float MATH_HALF_PI = 1.57079632679;

const int OK_LED = 8;
const int BUTTON_PIN = 2;

const int HEAD_SERVO  = 9;
const int RIGHT_SERVO = 10;
const int LEFT_SERVO  = 11;
const int MIN_MU_SERVO = 600;
const int MAX_MU_SERVO = 2400;
const int MAX_SERVO_SPEED = 900;

//Corriente máxima (sin peso) jalada por los 3 servos 0.35Amp