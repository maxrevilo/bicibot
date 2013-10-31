#ifndef Actuators_h
#define Actuators_h
#include <Arduino.h>
#include <Servo.h>
#include "BTask.h"

class Actuators {
    public:
        Actuators();
        void begin();
        void calibrate();

        int getHeadPosition();
        int getRightPosition();
        int getLeftPosition();

        void test_feedback_limits();
        void set_MU_limits();

    private:
        Servo _head_act;
        Servo _right_act;
        Servo _left_act;

        //Actuators actual voltage positions
        int _head_pos;
        int _right_pos;
        int _left_pos;

        //Actuators min and max voltage position
        int _head_max_pos;
        int _right_max_pos;
        int _left_max_pos;
        int _head_min_pos;
        int _right_min_pos;
        int _left_min_pos;

        //Actuators min and max boundaries of movement on MU
        int _head_max_MU;
        int _right_max_MU;
        int _left_max_MU;
        int _head_min_MU;
        int _right_min_MU;
        int _left_min_MU;

        static void _fun_task(Task* task);
        BTask _task;
        int _dest_right_ang;
        int _dest_left_ang;
        int _dest_pos;
        char _ang_dir;


};

#endif