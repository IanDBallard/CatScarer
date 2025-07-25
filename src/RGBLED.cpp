#include "RGBLED.h"

// Constructor implementation
RGBLED::RGBLED(int redPin, int greenPin, int bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin) {
    // Initialize the pin numbers for Red, Green, and Blue.
}

// begin() method implementation
void RGBLED::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
    turnOff(); // Ensure the LED starts in an off state.
}

// setColor() method implementation
void RGBLED::setColor(int r, int g, int b) {
    // Constrain values to valid PWM range (0-255)
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);
    
    // Use PWM for red and green channels (PWM-capable pins)
    analogWrite(_redPin, r);
    analogWrite(_greenPin, g);
    
    // Use digital control for blue channel (non-PWM pin D8)
    digitalWrite(_bluePin, b > 0 ? HIGH : LOW);
}

// turnOff() method implementation
void RGBLED::turnOff() {
    setColor(0, 0, 0); // Setting all colors to 0 effectively turns the LED off.
}