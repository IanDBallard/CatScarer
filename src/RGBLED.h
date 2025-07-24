#ifndef RGB_LED_H
#define RGB_LED_H

#include <Arduino.h>

class RGBLED {
public:
    // Constructor: Initializes the RGB LED with the pins for Red, Green, and Blue.
    // Assumes a COMMON CATHODE RGB LED.
    RGBLED(int redPin, int greenPin, int bluePin);

    // Initializes the LED pins as outputs.
    void begin();

    // Sets the color of the LED using RGB values (0-255 for each color).
    void setColor(int r, int g, int b);

    // Convenience method to turn the LED off.
    void turnOff();

private:
    int _redPin;
    int _greenPin;
    int _bluePin;
};

#endif // RGB_LED_H