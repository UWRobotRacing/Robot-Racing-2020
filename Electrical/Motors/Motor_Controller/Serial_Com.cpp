#include <Arduino.h>
#include "Serial_com.h"

#include "debug.h"

SerialConnection::SerialConnection() {}

SerialConnection::SerialConnection(uint16_t baudrate) {
    this->autonomousMode = false;
    this->baudrate = baudrate;

    Serial.begin(this->baudrate);
    //Wait for serial connection to be established
    while (!Serial){ ; }
    Serial.println("Serial connection established.");
}

//Checks for serial data and gets it if it is available
bool SerialConnection::dataAvailable() {
    if (this->confirmAutonomy() && Serial.available() > 0)        
        return true;
    else
        return false;
}

//Parses data that has been collected
char SerialConnection::getCommandType() {
    char prefix = Serial.read();

    DEBUG("Command: ");
    DEBUG(prefix);
    DEBUG("\n");

    return prefix;
}

int SerialConnection::getCommandValue() {
    int value = Serial.parseInt();

    DEBUG("Value: ");
    DEBUG(value);
    DEBUG("\n");

    return value;
}


//Failsafe, if there is no connection to the
bool SerialConnection::confirmAutonomy() {

    //COMBAK: Need to read from the transmitter here
    return true;

}

bool SerialConnection::isAutonomous() {
    return this->autonomousMode;
}