#include "ESC.h"
#include "Steering_Servo.h"
#include "Serial_com.h"

#include "debug.h"

ESC rearMotor;
SteeringServo servo;
SerialConnection conn;

void setup() {
    conn = SerialConnection(9600);
    rearMotor = ESC(9);
    servo = SteeringServo(10);
    delay(1000);
    rearMotor.arm();
}

void loop() {

    if (conn.dataAvailable()) {
        char command = conn.getCommandType();
        int value = conn.getCommandValue();
        
        switch (command)
        {
        case 'D': //Set the dive speed
            rearMotor.setSpeed(value);
            break;
        
        case 'S': //Set the Steering Angle
            servo.setAngle(value);
            break;

        case 'I': //Increment the steering Angle
            value >= 0 ? servo.incrementAngle(servo.Clockwise) 
                            : servo.incrementAngle(servo.Counterclockwise);
            break;

        case 'A': //Arm the ESC
            rearMotor.arm();
            break;

        default:
            DEBUG("Not a valid command");
            break;
        }   
    }
}


