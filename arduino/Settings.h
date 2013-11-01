#ifndef Settings_H
#define Settings_H

#include <Arduino.h>

struct Settings {
    public:
        Settings();

        void load();
        void save();
        void reset();

        void toString(char *str);

        //Public data
        struct _ACTUATORS
        {
            bool calibrated;

            //Actuators min and max voltage position
            //int _head_max_pos;
            int right_max_pos;
            int left_max_pos;
            //int _head_min_pos;
            int right_min_pos;
            int left_min_pos;

            //Actuators min and max boundaries of movement on MU
            int _head_max_MU;
            int _right_max_MU;
            int _left_max_MU;
            int _head_min_MU;
            int _right_min_MU;
            int _left_min_MU;
        } actuators;

        struct _SENSORS
        {
            bool calibrated;

            int x_offset;
            int y_offset;
            int z_offset;
        } sensors;

    private:
        //Code to avoid reading garbage
        char _code;
};

#endif
