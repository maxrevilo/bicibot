#include "Power.h"
#include "consts.h"

//Private
void Power::_fun_taskOnOff(Task* task) {
    Power *self = (Power *) ((BTask *) task)->getContext();

    //if(self->isOn()) digitalWrite(OK_LED, HIGH);
    /*else*/ digitalWrite(OK_LED, self->_led_on);

    self->_led_on = !self->_led_on;
}

/// constructor
Power::Power():
    _taskOnOff(1000, &(Power::_fun_taskOnOff), this)
    {

}


void Power::begin(Settings *settings) {
    pinMode(OK_LED, OUTPUT);

    //Ok Led callbacks
    SoftTimer.add(&_taskOnOff);
    _led_on = false;
}


void Power::turn_on() {
    _isOn = true;
}

void Power::turn_off() {
    _isOn = false;
}

bool Power::isOn() { return _isOn; }

