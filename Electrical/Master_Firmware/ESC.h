#include <Servo.h>

class ESC {

private:
    uint16_t motorSpeed;
    bool reverse;
    uint8_t PIN;
    Servo motor;
public:
    ESC();
    ESC (uint8_t PIN);

    //PURPOSE: Sets the speed of the motor
    //INPUT: motorSpeed - speed as a percentage (-100% - 100%)
    void setSpeed(int8_t motorSpeed);

    void arm();

    int getSpeed();
    bool reversing();
    
};