#include "GP2Y0E03.h"

// Constructor implementation
GP2Y0E03::GP2Y0E03(TwoWire &wire, uint8_t address)
    : _wire(wire), _addr(address) {}

// Initialize using the default I2C address
void GP2Y0E03::init(int voutPin)
{
    _wire.begin();
    _init_sensor(voutPin);
}

// Initialize with a specified I2C address
void GP2Y0E03::init(int voutPin, uint8_t address)
{
    _addr = address;
    _wire.begin();
    _init_sensor(voutPin);
}

#ifdef ESP32 || ESP8266
// Initialize with custom SDA and SCL pins
void GP2Y0E03::init(int voutPin, int sda, int scl)
{
    _wire.begin(sda, scl);
    _init_sensor(voutPin);
}

// Initialize with custom SDA, SCL pins and a specific I2C address
void GP2Y0E03::init(int voutPin, int sda, int scl, uint8_t address)
{
    _addr = address;
    _wire.begin(sda, scl, address);
    _init_sensor(voutPin);
}
#endif

void GP2Y0E03::_init_sensor(int voutPin)
{
    _voutPin = voutPin;
    calibrateAnalog(448, 289, 3, 30);
    if (_voutPin != -1)
    {
        pinMode(_voutPin, INPUT);
    }

    _wire.beginTransmission(_addr);
    _wire.write(0x35);
    _wire.endTransmission();

    _wire.requestFrom(_addr, 1);
    if (1 <= Wire.available())
    {
        _shift = Wire.read();
    }
}

int GP2Y0E03::vout()
{
    return analogRead(_voutPin);
}

void GP2Y0E03::calibrateAnalog(int voutMin, int voutMax, int distMin, int distMax)
{
    _cal[0] = voutMin;
    _cal[1] = voutMax;
    _cal[2] = distMin;
    _cal[3] = distMax;
}

// Method to read the distance via from the sensor
int GP2Y0E03::distDigital()
{
    _wire.beginTransmission(_addr);
    _wire.write(0x5E);
    _wire.endTransmission();

    _wire.requestFrom(_addr, 2);
    if (_wire.available() != 2)
        return -1;

    uint8_t reg0 = _wire.read();
    uint8_t reg1 = _wire.read();
    int dist = (reg0 * 16 + reg1) / 16 / (int)pow(2, _shift);

    return dist > 60 ? -1 : dist;
}

// Method to read the distance via vout from the sensor
int GP2Y0E03::distAnalog()
{
    int dist = map(vout(), _cal[0], _cal[1], _cal[2], _cal[3]);
    return dist > 60 ? -1 : dist;
}
