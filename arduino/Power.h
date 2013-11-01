#ifndef Power_h
#define Power_h
#include <Arduino.h>
#include "BTask.h"
#include "Settings.h"

struct Power {
    public:
        /// constructor
        Power();
        void begin(Settings *settings);

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