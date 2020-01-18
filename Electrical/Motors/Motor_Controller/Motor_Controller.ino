#include "ESC.h"
#include "Steering_Servo.h"
#include "debug.h"

ESC rearMotor;
SteeringServo servo;

void setup() {
    beginSerial(9600);
    rearMotor = ESC(9);
    servo = SteeringServo(10);
    delay(1000);
    rearMotor.arm();
}

void loop() {

    //Get available serial input    
    if (Serial.available() > 0) {
        char prefix = Serial.read();
        int received = Serial.parseInt();

        DEBUG("Received: ");
        DEBUG(prefix);
        DEBUG(received);
        DEBUG("\n");


        
        if (prefix == 'D')//prefix 'D' to the speed to set drive speed
        {
            rearMotor.setSpeed(received);
        }
        else if (prefix == 'S') //prefix 'S' for steering angle
        {
            servo.setAngle(received);
        }
        else if (prefix == 'I') //prefix 'I' for increment
        {
            received >= 0 ? servo.incrementAngle(servo.Clockwise) 
                            : servo.incrementAngle(servo.Counterclockwise);
        }
        else if (prefix == 'A') //'A' for arm ESC
        {
            rearMotor.arm();
        }         

    }
}

//PURPOSE: Waits for serial connection to be established between PC/arduino
void beginSerial(int baudRate) {
    Serial.begin(baudRate);
    //Wait for serial connection to be established
    while (!Serial){
        ;
    }
    Serial.println("Serial connection established.");
}

