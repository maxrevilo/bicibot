#ifndef helpers_h
#define helpers_h
#include <Arduino.h>

int analogReadProm(int pin, int samples, int wait_time) {
    unsigned long sum = 0;
    word i;
    for(i=0; i < samples; i++) {
        sum += analogRead(pin);
        delayMicroseconds(wait_time);
    }
    return sum/samples;
}

#endif