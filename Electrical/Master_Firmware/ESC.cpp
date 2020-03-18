#include "ESC.h"
#include <Servo.h>
#include <Arduino.h>

#include "debug.h"

ESC::ESC() {}

ESC::ESC(uint8_t PIN) {
    this->PIN = PIN;
    this->reverse = false;
    this->motorSpeed = 1000;
    this->motor.attach(PIN, 1000, 2000);
}

//Sets the speed of the ESC by percentage
void ESC::setSpeed(int8_t motorSpeed) {

    //Turn speed percentage to correct output
    int16_t mappedSpeed = map(constrain(motorSpeed, -100, 100), -100, 100, 1000, 2000);
    
    this->motorSpeed = mappedSpeed;
    if (motorSpeed < 0)
        this->reverse = true;
    else
        this->reverse = false;

//    DEBUG("Sent to motor:");
    DEBUG(mappedSpeed);
//    DEBUG("\n");
    
    this->motor.writeMicroseconds(this->motorSpeed);    
}

int16_t ESC::getSpeed() {
    return this->motorSpeed;
}
bool ESC::reversing() {
    return this->reverse;
}

void ESC::arm() {
    this->motor.writeMicroseconds(1000);
    delay(500);
    DEBUG("ESC arm command sent");
    DEBUG("\n");
    this->setSpeed(0);
}
