#include "PWMFan.h"

// Constructor implementation
PWMFan::PWMFan(int pwmPin) : _pwmPin(pwmPin), _currentSpeed(0) {
    // Initialize _pwmPin and _currentSpeed.
}

// begin() method implementation
void PWMFan::begin() {
    pinMode(_pwmPin, OUTPUT); // Set the fan PWM pin as an output.
    turnOff(); // Ensure the fan starts in an off state.
}

// turnOn() method implementation
void PWMFan::turnOn(int speed) {
    setSpeed(speed); // Set the speed and turn the fan on.
}

// turnOff() method implementation
void PWMFan::turnOff() {
    analogWrite(_pwmPin, 0); // Write 0 to turn the fan off.
    _currentSpeed = 0;       // Update current speed.
}

// setSpeed() method implementation
void PWMFan::setSpeed(int speed) {
    // Constrain speed to the valid range of 0-255 for analogWrite.
    _currentSpeed = constrain(speed, 0, 255);
    analogWrite(_pwmPin, _currentSpeed); // Write the speed to the PWM pin.
}