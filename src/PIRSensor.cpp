#include "PIRSensor.h"

// Constructor implementation
PIRSensor::PIRSensor(int pin) : _pirPin(pin), _warmUpStartTime(0), _warmUpDuration(45000), _isInitialized(false) {
    // Initialize member variables
}

// begin() method implementation
void PIRSensor::begin() {
    pinMode(_pirPin, INPUT); // Set the PIR sensor pin as an input.
    _warmUpStartTime = millis(); // Start warm-up timer
    _isInitialized = false; // Mark as not yet initialized
}

// update() method implementation
void PIRSensor::update() {
    // Check if warm-up period is complete
    if (!_isInitialized && (millis() - _warmUpStartTime >= _warmUpDuration)) {
        _isInitialized = true; // Mark as initialized
    }
}

// isMotionDetected() method implementation
bool PIRSensor::isMotionDetected() {
    // Don't detect motion during warm-up period
    if (!_isInitialized) {
        return false;
    }
    
    // Read the digital state of the PIR sensor pin.
    // Returns true if HIGH (motion detected), false if LOW (no motion).
    return digitalRead(_pirPin) == HIGH;
}

// isInitializing() method implementation
bool PIRSensor::isInitializing() {
    return !_isInitialized; // Return true if still initializing
}