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
    // Simple on/off control using digitalWrite
    // For common cathode: HIGH = on, LOW = off
    // For common anode: HIGH = off, LOW = on
    
    // Using common cathode logic (HIGH = on, LOW = off)
    digitalWrite(_redPin, r > 0 ? HIGH : LOW);   // HIGH = on, LOW = off
    digitalWrite(_greenPin, g > 0 ? HIGH : LOW); // HIGH = on, LOW = off  
    digitalWrite(_bluePin, b > 0 ? HIGH : LOW);  // HIGH = on, LOW = off
}

// turnOff() method implementation
void RGBLED::turnOff() {
    setColor(0, 0, 0); // Setting all colors to 0 effectively turns the LED off.
}