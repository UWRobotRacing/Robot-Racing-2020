#include "Steering_Servo.h"
#include <Servo.h>
#include <Arduino.h>

#include "debug.h"

SteeringServo::SteeringServo() {}

SteeringServo::SteeringServo(uint8_t PIN) {
    this->PIN = PIN;
    this->angle = 0;
    this->percentAngle = 0;
    this->motor.attach(PIN);
    setAngle(0);
}

//Sets the angle of the wheels by percentage
void SteeringServo::setAngle(int8_t angle) {

    //COMBAK: Need to experimentally determine these values.
    uint8_t max_angle = 120;
    uint8_t min_angle = 60;

//    
//    DEBUG("Value before constrain:");
//    DEBUG(angle);
//    DEBUG("\n");

    this->percentAngle = angle;

    //Turn angle percentage to correct output
    angle = constrain(map(angle, -100, 100, min_angle, max_angle), min_angle, max_angle);
    
    this->angle = angle;
    
//    DEBUG("Sent to steering servo:");
    DEBUG(angle);
//    DEBUG("\n");
    
    this->motor.write(this->angle);    
}

void SteeringServo::incrementAngle(direction direction) {
    DEBUG("Incrementing angle: ");
    DEBUG(direction);
    DEBUG('\n');
    setAngle(this->percentAngle + direction);
}

int8_t SteeringServo::getAngle() {
    return this->angle;
}
