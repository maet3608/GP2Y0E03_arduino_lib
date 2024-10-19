# Readme

Arduino library for the GP2Y0E03 IR Laser Range Distance sensor.

Should work with most Arduino, ESP32 and ESP8266 boards. 

For more details see 
[GP2Y0E03 Distance Sensor with Arduino](https://www.makerguides.com/gp2y0e03-distance-sensor-with-arduino/)
[GP2Y0E03 Datasheet](https://www.makerguides.com/wp-content/uploads/2024/10/GP2Y0E03-datasheet.pdf)
[GP2Y0E03 Application Notes](https://www.makerguides.com/wp-content/uploads/2024/10/GP2Y0E03-application-notes.pdf)

## Packaging

Just zip up all the contents as zip file or download this repository as a .zip from GitHub via
`Code -> Download ZIP`

## Using library

In Arduino IDE menu, go to `Sketch -> Include Libray -> Add .ZIP Library...` and then select the zipped library.

After including it, you can add the include headers to your current sketch with `Sketch -> Include Library -> TOF10120`.

## Running examples

You can open the example from the Arduino IDE by going to the menu `File -> Examples -> GP2Y0E03 -> GP2Y0E03_example`.

## Example 

A simple example that includes the library and uses the distDigital()
and the distAnalog() functions to print the distance measured by the 
GP2Y0E03 sensor to the Serial Monitor.

The example assumes that SCL and SDA of the GP2Y0E03 are connected to the 
standard SCL and SDA pins of the Arduino and that vout of the GP2Y0E03 is 
connected to A3 of the Arduino

However, you can use `sensor.init(vout, sda, scl)` to set specific pins, e.g.
for software I2C on ESP32 and ESP8266 boards.

```
#include "GP2Y0E03.h"

GP2Y0E03 sensor = GP2Y0E03();

void setup() {
    Serial.begin(9600);
    sensor.init(A3);
}

void loop() {
    Serial.print("digital:");
    Serial.println(sensor.distDigital());
    Serial.print(" analog:");
    Serial.println(sensor.distAnalog());
    Serial.println();
    delay(1000);
}
```