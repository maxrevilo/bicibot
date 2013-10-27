#include <Math.h>
#include "Actuators.h"
#include "consts.h"
#include "helpers.h"

void Actuators::_fun_task(Task* task) {
    Actuators *self = (Actuators *) ((BTask *) task)->getContext();

    // self->_right_pos = analogRead(RIGHT_FEEDBACK);
    // self->_left_pos = analogRead(LEFT_FEEDBACK);
    self->_right_pos = analogReadProm(A4, 3, 5);
    self->_left_pos = analogReadProm(A5, 3, 5);

    if(abs(self->getRightPosition() - self->_dest_ang) > 100) return;
    if(abs(self->getLeftPosition() - self->_dest_ang) > 100) return;

    if(self->_dest_pos > 5000) {
        self->_ang_dir = -3;
    }
    if(self->_dest_pos < 0) {
        self->_ang_dir = 3;
    }

    self->_dest_pos += self->_ang_dir;
    float fpos = (float) self->_dest_pos;

    self->_dest_ang = (int)( (sin( fpos * MATH_TWO_PI / 5000.0 - MATH_HALF_PI ) + 1.0)/2.0*(MAX_MU_SERVO-MIN_MU_SERVO) ) + MIN_MU_SERVO;

    //Serial.println(self->_dest_ang);

    //self->_head_act.writeMicroseconds(self->_dest_ang);
    self->_right_act.writeMicroseconds(self->_dest_ang);
    self->_left_act.writeMicroseconds(self->_dest_ang);
}


/// constructor
Actuators::Actuators():
    _task(0, &(Actuators::_fun_task), this)
    {
    _head_pos  = -1;
    _right_pos = -1;
    _left_pos  = -1;
}

void Actuators::begin(Power *power) {
    _head_act.attach(HEAD_SERVO);
    _right_act.attach(RIGHT_SERVO);
    _left_act.attach(LEFT_SERVO);

    _power = power;

    _test_feedback_limits();

    //From MIN_MU_SERVO to MAX_MU_SERVO
    _dest_ang = MIN_MU_SERVO;
    //From 0 to 5000
    _dest_pos = 0;
    //1 or -1
    _ang_dir = 3;

    _right_act.writeMicroseconds(_dest_ang);
    _left_act.writeMicroseconds(_dest_ang);

    SoftTimer.add(&_task);
}


int Actuators::getHeadPosition(){
    return _head_pos;
}

int Actuators::getRightPosition(){
    return map(_right_pos, _right_min_pos, _right_max_pos, MIN_MU_SERVO, MAX_MU_SERVO);
}

int Actuators::getLeftPosition(){
    return map(_left_pos, _left_min_pos, _left_max_pos, MIN_MU_SERVO, MAX_MU_SERVO);
}


void Actuators::_test_feedback_limits() {
    delay(4*MAX_SERVO_SPEED);

    _right_act.writeMicroseconds(MAX_MU_SERVO);
    _left_act.writeMicroseconds(MAX_MU_SERVO);
    delay(4*MAX_SERVO_SPEED);
    _right_max_pos = analogReadProm(A4, 10000, 100);
    _left_max_pos = analogReadProm(A5, 10000, 100);
    Serial.print("Max Right: ");
    Serial.print(_right_max_pos);
    Serial.print(" \tMax Left: ");
    Serial.println(_left_max_pos);

    _right_act.writeMicroseconds(MIN_MU_SERVO);
    _left_act.writeMicroseconds(MIN_MU_SERVO);
    delay(4*MAX_SERVO_SPEED);
    _right_min_pos = analogReadProm(A4, 10000, 100);
    _left_min_pos = analogReadProm(A5, 10000, 100);
    Serial.print("Min Right: ");
    Serial.print(_right_min_pos);
    Serial.print(" \tMin Left: ");
    Serial.println(_left_min_pos);
}