#ifndef PWM_FAN_H
#define PWM_FAN_H

#include <Arduino.h>

class PWMFan {
public:
    // Constructor: Initializes the fan with the given PWM pin.
    PWMFan(int pwmPin);

    // Initializes the fan pin as an output.
    void begin();

    // Turns the fan on with a specified speed (0-255 for analogWrite).
    void turnOn(int speed = 255); // Default to full speed if no speed is given.

    // Turns the fan off.
    void turnOff();

    // Sets the fan speed.
    void setSpeed(int speed);

private:
    int _pwmPin;      // Private member to store the PWM pin connected to the fan.
    int _currentSpeed; // Store the current speed for reference.
};

#endif // PWM_FAN_H