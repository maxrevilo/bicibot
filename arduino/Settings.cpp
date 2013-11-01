#include <Arduino.h>
#include "Settings.h"
#include "EEPROMAnything.h"

Settings::Settings() {
    this->_code = 0xA1;
    this->actuators.calibrated = false;
    this->sensors.calibrated = false;
}

void Settings::load() {
    int size = EEPROM_read(0, this);
    Serial.println(size);
    Serial.print("Bytes loaded to Settings");
}

void Settings::save() {
    int size = EEPROM_write(0, this);
    Serial.println(size);
    Serial.print("Bytes saved from Settings");
}

void Settings::reset() {

}

void Settings::toString(char *str) {

}