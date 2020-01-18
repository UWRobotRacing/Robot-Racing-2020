#include <Servo.h>

class SteeringServo {

private:
    int8_t angle;
    uint8_t PIN;
    Servo motor;

public:
    
    enum direction {Clockwise = -1, Counterclockwise = 1};

    SteeringServo();
    SteeringServo (uint8_t PIN);

    void setAngle(uint8_t angle); //angle in degrees, positive CW, negative CCW

    void incrementAngle(direction);

    int8_t getAngle();
};