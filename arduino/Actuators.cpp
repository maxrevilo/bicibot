#include <Math.h>
#include "Actuators.h"
#include "consts.h"
#include "helpers.h"

/// constructor
Actuators::Actuators():
    _task(0, &(Actuators::_fun_task), this)
    {
    _head_pos  = -1;
    _right_pos = -1;
    _left_pos  = -1;
}

//Borrar
unsigned int last_pos = (MAX_MU_SERVO - MIN_MU_SERVO)/2;

void Actuators::begin(Settings *settings) {
    this->settings = settings;

    _head_act.attach(HEAD_SERVO);
    _right_act.attach(RIGHT_SERVO);
    _left_act.attach(LEFT_SERVO);

    //From MIN_MU_SERVO to MAX_MU_SERVO
    _dest_right_ang = _right_min_MU;
    _dest_left_ang = _left_min_MU;
    //From 0 to 5000
    _dest_pos = 0;
    //1 or -1
    _ang_dir = 3;

    _right_act.writeMicroseconds(_dest_right_ang);
    _left_act.writeMicroseconds(_dest_left_ang);
    _head_act.writeMicroseconds(last_pos);

    SoftTimer.add(&_task);
}

void Actuators::calibrate() {
    test_feedback_limits();
    set_MU_limits();
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


// pos va de -1000 a 1000, donde -1000 es grado 0 y 1000 es grado 180. 
void Actuators::moveHead(int pos) {
    unsigned long int Aux;
    unsigned int MU;
    Aux = (pos + 1000);
    Aux = Aux * (MAX_MU_SERVO - MIN_MU_SERVO);
    MU = Aux/2000 + MIN_MU_SERVO;

    //Low pass filter
    last_pos = ((float)last_pos) * 0.98f + ((float)MU) * 0.02f;
    //last_pos = MU;

    if(last_pos > MAX_MU_SERVO) last_pos = MAX_MU_SERVO;
    else if(last_pos < MIN_MU_SERVO) last_pos = MIN_MU_SERVO;

    _head_act.writeMicroseconds(last_pos);
}


/* Se prueban los valores máximos y mínimos del voltage del feedback
 * para hacer un mapeado con los MU de los servos.
 */
void Actuators::test_feedback_limits() {
    _head_act.attach(HEAD_SERVO);
    _right_act.attach(RIGHT_SERVO);
    _left_act.attach(LEFT_SERVO);

    delay(4*MAX_SERVO_SPEED);

    _right_act.writeMicroseconds(MAX_MU_SERVO);
    _left_act.writeMicroseconds(MAX_MU_SERVO);
    delay(4*MAX_SERVO_SPEED);
    _right_max_pos = analogReadProm(RIGHT_FEEDBACK, 10000, 100);
    _left_max_pos = analogReadProm(LEFT_FEEDBACK, 10000, 100);
    Serial.print("Max Right: ");
    Serial.print(_right_max_pos);
    Serial.print(" \tMax Left: ");
    Serial.println(_left_max_pos);

    _right_act.writeMicroseconds(MIN_MU_SERVO);
    _left_act.writeMicroseconds(MIN_MU_SERVO);
    delay(4*MAX_SERVO_SPEED);
    _right_min_pos = analogReadProm(RIGHT_FEEDBACK, 10000, 100);
    _left_min_pos = analogReadProm(LEFT_FEEDBACK, 10000, 100);
    Serial.print("Min Right: ");
    Serial.print(_right_min_pos);
    Serial.print(" \tMin Left: ");
    Serial.println(_left_min_pos);

    _head_act.detach();
    _right_act.detach();
    _left_act.detach();
}

/* Se capturan las poses de ambas piernas para establecer los limites
 * de movimiento en la bicicleta.
 */
void Actuators::set_MU_limits() {
    _head_act.detach();
    _right_act.detach();
    _left_act.detach();

    delay(3000);
    Serial.println("Set min servo position (and press \"a\" key when finished)");
    while(digitalRead(3) == LOW && (Serial.available()==0 || Serial.read() != 'a'))

    _right_pos = analogReadProm(RIGHT_FEEDBACK, 10, 50);
    _right_min_MU = getRightPosition();

    _left_pos = analogReadProm(LEFT_FEEDBACK, 10, 50);
    _left_min_MU = getLeftPosition();

    Serial.print("Servos Min MU <Right: ");
    Serial.print(_right_min_MU);
    Serial.print(",\tLeft: ");
    Serial.print(_left_min_MU);
    Serial.println(">");

    delay(3000);
    Serial.println("Set max servo position (and press \"a\" key when finished)");
    while(digitalRead(3) == LOW && (Serial.available()==0 || Serial.read() != 'a'));

    _right_pos = analogReadProm(RIGHT_FEEDBACK, 10, 50);
    _right_max_MU = getRightPosition();

    _left_pos = analogReadProm(LEFT_FEEDBACK, 10, 50);
    _left_max_MU = getLeftPosition();

    Serial.print("Servos Max MU <Right: ");
    Serial.print(_right_max_MU);
    Serial.print(",\tLeft: ");
    Serial.print(_left_max_MU);
    Serial.println(">");

    int aux;
    //Se reacomodan los valores para que en efecto max > min.
    if(_right_max_MU < _right_min_MU) {
        aux = _right_max_MU;
        _right_max_MU = _right_min_MU;
        _right_min_MU = aux;
    }
    if(_left_max_MU < _left_min_MU) {
        aux = _left_max_MU;
        _left_max_MU = _left_min_MU;
        _left_min_MU = aux;
    }
}

/* Cada que el procesador pueda se llamará este procedimiento para
 * actualizar la posición de las piernas segun una función sinusoidal.
 * Con el feedback de los servos se mantienen sincronizadas al mismo ritmo.
 */
// void Actuators::_fun_task(Task* task) {
//     Actuators *self = (Actuators *) ((BTask *) task)->getContext();

//     self->_right_pos = analogReadProm(RIGHT_FEEDBACK, 3, 5);
//     self->_left_pos = analogReadProm(LEFT_FEEDBACK, 3, 5);

//     // Serial.print("Left: ");
//     // Serial.print(self->getLeftPosition());
//     // Serial.print(", dest: ");
//     // Serial.println(self->getLeftPosition());

//     if(abs(self->getRightPosition() - self->_dest_right_ang) > 100) return;
//     if(abs(self->getLeftPosition() - self->_dest_left_ang) > 100) return;

//     if(self->_dest_pos > 5000) {
//         self->_ang_dir = -3;
//     }
//     if(self->_dest_pos < 0) {
//         self->_ang_dir = 3;
//     }

//     self->_dest_pos += self->_ang_dir;
//     float fpos = (float) self->_dest_pos;
//     float sin_factor = (sin( fpos * MATH_TWO_PI / 5000.0 - MATH_HALF_PI ) + 1.0) * 0.5;

//     self->_dest_right_ang = (int)( sin_factor * (self->_right_max_MU - self->_right_min_MU) ) + self->_right_min_MU;
//     self->_dest_left_ang = (int)( sin_factor * (self->_left_max_MU - self->_left_min_MU) ) + self->_left_min_MU;

//     self->_right_act.writeMicroseconds(self->_dest_right_ang);
//     self->_left_act.writeMicroseconds(self->_dest_left_ang);
// }

void Actuators::_fun_task(Task* task) {
    Actuators *self = (Actuators *) ((BTask *) task)->getContext();

    self->_right_pos = analogReadProm(RIGHT_FEEDBACK, 3, 5);
    self->_left_pos = analogReadProm(LEFT_FEEDBACK, 3, 5);

    self->_right_act.writeMicroseconds(self->_dest_right_ang);
    self->_left_act.writeMicroseconds(self->_dest_left_ang);

    if(abs(self->getRightPosition() - self->_dest_right_ang) > 60) return;
    if(abs(self->getLeftPosition() - self->_dest_left_ang) > 60) return;

    if(self->_dest_right_ang == self->_right_max_MU) {
        self->_dest_right_ang = self->_right_min_MU;
        self->_dest_left_ang = self->_right_min_MU;
    } else {
        self->_dest_right_ang = self->_right_max_MU;
        self->_dest_left_ang = self->_right_max_MU;
    }

    self->_right_act.detach();
    self->_left_act.detach();
    delay(300);
    self->_right_act.attach(RIGHT_SERVO);
    self->_left_act.attach(LEFT_SERVO);
}