#include "Steering_Servo.h"
#include <Servo.h>
#include <Arduino.h>

#include "debug.h"

SteeringServo::SteeringServo() {}

SteeringServo::SteeringServo(uint8_t PIN) {
    this->PIN = PIN;
    this->angle = 0;
    this->motor.attach(PIN, 25, 155);
    setAngle(90);
}

//Sets the speed of the ESC by percentage
void SteeringServo::setAngle(uint8_t angle) {

    //COMBAK: Need to experimentally determine these values.
    uint8_t max_angle = 155;
    uint8_t min_angle = 25;

    
    DEBUG("Value before constrain:");
    DEBUG(angle);
    DEBUG("\n");

    //Turn speed percentage to correct output
    angle = constrain(angle, min_angle, max_angle);
    
    this->angle = angle;
    
    DEBUG("Sent to steering servo:");
    DEBUG(angle);
    DEBUG("\n");
    
    this->motor.write(this->angle);    
}

void SteeringServo::incrementAngle(direction direction) {
    DEBUG("Incrementing angle: ");
    DEBUG(direction);
    DEBUG('\n');
    setAngle(this->angle + direction);
}

int8_t SteeringServo::getAngle() {
    return this->angle;
}
