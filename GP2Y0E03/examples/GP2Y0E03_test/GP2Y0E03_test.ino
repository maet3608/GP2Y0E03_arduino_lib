#include "GP2Y0E03.h"

GP2Y0E03 sensor = GP2Y0E03();

void setup()
{
    Serial.begin(9600);
    sensor.init(A3);
}

void loop()
{
    Serial.print("digital:");
    Serial.println(sensor.distDigital());
    Serial.print(" analog:");
    Serial.println(sensor.distAnalog());
    Serial.println();
    delay(1000);
}