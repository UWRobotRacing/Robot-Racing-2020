class SerialConnection {

private:
    bool autonomousMode;
    uint16_t baudrate;

public:
    
    SerialConnection();
    SerialConnection(uint16_t baudrate);

    bool dataAvailable();

    char getCommandType();

    int getCommandValue();

    bool confirmAutonomy();

    bool isAutonomous();
};