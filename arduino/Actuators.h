#ifndef Actuators_h
#define Actuators_h
#include <Arduino.h>
#include <Servo.h>
#include <Power.h>
#include "BTask.h"

class Actuators {
    public:
        Actuators();
        void begin(Power *power);

        int getHeadPosition();
        int getRightPosition();
        int getLeftPosition();

    private:
        Power *_power;
        Servo _head_act;
        Servo _right_act;
        Servo _left_act;

        void _test_feedback_limits();
        int _head_pos;
        int _right_pos;
        int _left_pos;
        int _head_max_pos;
        int _right_max_pos;
        int _left_max_pos;
        int _head_min_pos;
        int _right_min_pos;
        int _left_min_pos;

        static void _fun_task(Task* task);
        BTask _task;
        int _dest_ang;
        int _dest_pos;
        char _ang_dir;


};

#endif