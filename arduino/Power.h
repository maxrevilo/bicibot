#ifndef Power_h
#define Power_h
#include <Arduino.h>
#include "BTask.h"

class Power {
    public:
        /// constructor
        Power();
        void begin();

        //Getters
        void turn_on();
        void turn_off();
        bool isOn();
    private:
        bool _isOn;

        static void _fun_taskOnOff(Task* task);
        BTask _taskOnOff;
        bool _led_on;
};

#endif