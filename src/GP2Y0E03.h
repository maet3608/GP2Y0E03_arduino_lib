#ifndef GP2Y0E03_H
#define GP2Y0E03_H

#include <Arduino.h>
#include <Wire.h>

class GP2Y0E03
{
public:
    // Constructor that accepts a TwoWire object
    GP2Y0E03(uint8_t address = 0x40);

    // Method to initialize with the default I2C address
    void init(int vout = -1);

#ifdef ESP32 || ESP8266
    // Method to initialize with custom SDA and SCL pins
    void init(int vout, int sda, int scl);

    // Method to initialize with custom SDA and SCL pins
    void init(int sda, int scl);

#endif

    // Method to read the distance in cm from the sensor
    int distDigital();

    // Method to read the distance in cm from the sensor
    int distAnalog();

    // Method to read analog voltage output (vout) from sensor
    int vout();

    // Method to calibrate vout to distance
    void calibrateAnalog(int voutMin, int voutMax, int distMin, int distMax);

private:
    int _addr; // I2C address of the sensor
    uint8_t _shift;
    int _vout;     // Pin for analog readings
    int _cal[4];   // Calibration params for analog readings
    TwoWire _wire; // TwoWire object

    void _init_sensor(int vout); // Initializes GP2Y0E03
};

#endif // GP2Y0E03_H