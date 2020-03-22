#include "ESC.h"
#include "Steering_Servo.h"
#include "Serial_com.h"

#include "debug.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(7, 53); // CE, CSN
const byte address[6] = "00101";

// 32 bit Frame Structure
uint32_t buf = 0;//[MSB] 12 bit (steer) | 12 bit (spd) | 8 bit (6 bit pattern + 2 bit modes)
#define MASK_UNIQUE_PATTERN   0xA4 //8 bit for flags (6 pattern + 2 bit switch state)  101001XX  
#define MASK_BUFFER_FLAG      0x000000FF  
#define MASK_BUFFER_SPD       0x000FFF00
#define MASK_BUFFER_STEER     0xFFF00000   
//macro access funcs
#define GET_SPD(x)    (((x)&MASK_BUFFER_SPD)>>8)
#define GET_STEER(x)  (((x)&MASK_BUFFER_STEER)>>20)
#define GET_FLAG(x)   ((x)&MASK_BUFFER_FLAG)



ESC rearMotor;
SteeringServo servo;
SerialConnection conn;

void setup() {
    conn = SerialConnection(9600);
    rearMotor = ESC(9);
    servo = SteeringServo(10);
    delay(1000);
    //rearMotor.arm();

    radio.begin();
    radio.setDataRate( RF24_250KBPS );//low data rate => longer range and reliable
    radio.enableAckPayload();
    radio.setRetries(3,2);
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_HIGH);
    radio.startListening();
    Serial.println("temp1,temp2,temp3,speed,steer");
}

void loop() {
    //if the remote is not connected we are not going to do anything
    if (!radio.available()) {
        //TODO: implement a timer so after a few seconds of no new info we kill the car
        //failsafe();
    } else {
        radio.read(&buf, sizeof(buf));
        uint16_t temp1 = GET_SPD(buf);//speed
        uint16_t temp2 = GET_STEER(buf);//steer
        uint8_t temp3 =  GET_FLAG(buf); //pattern & buttons, estop is last bit, auto mode is second last bit

        if((temp3 >> 2) & (MASK_UNIQUE_PATTERN >> 2)) {
            
            //Remote estop
            if (bitRead(temp3, 0) == 1) {
//                Serial.println("estop");
                failsafe();
            } else {
                //auto mode
                if (bitRead(temp3, 1) == 1) {
//                  Serial.println("auto");
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
                            DEBUG("Not a valid command\n");
                            break;
                        }   
                    }
                } else { //remote mode
//                  Serial.println("remote");
                    Serial.print(temp1,DEC);  
                    Serial.print(",");
                    Serial.print(temp2,DEC);
                    Serial.print(",");
                    Serial.print(temp3,DEC); 
                    Serial.print(",");
                    int16_t tempSpeed = ((temp1) / 10 );
                    int16_t tempSteer = ((temp2) / 10 );
                    rearMotor.setSpeed(tempSpeed);
                    Serial.print(",");
                    servo.setAngle(tempSteer);
                    Serial.print("\n");
                }
            }
        } else {
            Serial.print(temp3,DEC);
            Serial.println(" Invalid msg");
        }    
    } 

    /*

    } else {
      //Serial.print(".");
    }
    */
}

void failsafe() {
  rearMotor.setSpeed(0);
  Serial.print("STOPPED");
}
