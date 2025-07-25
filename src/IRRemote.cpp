#include "IRRemote.h"

// Constructor implementation
IRRemote::IRRemote(int pin) {
    irPin = pin;
    powerTogglePressed = false;
    lastDebounceTime = 0;
    powerCodeDetected = true; // For testing, assume power code is always detected
}

// begin() method implementation
void IRRemote::begin() {
    pinMode(irPin, INPUT_PULLUP); // Set as input with pull-up for button testing
    Serial.println("IR Receiver initialized on pin " + String(irPin));
    Serial.println("For testing: Send 'P' via serial to simulate power toggle");
}

// update() method implementation
void IRRemote::update() {
    // Check for serial command to simulate power toggle
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'P' || command == 'p') {
            simulatePowerToggle();
        }
    }
    
    // Check for button press on IR pin (for hardware testing)
    if (digitalRead(irPin) == LOW) {
        unsigned long currentTime = millis();
        if (currentTime - lastDebounceTime >= DEBOUNCE_DELAY) {
            simulatePowerToggle();
            lastDebounceTime = currentTime;
        }
    }
}

// isPowerTogglePressed() method implementation
bool IRRemote::isPowerTogglePressed() {
    return powerTogglePressed;
}

// clearPowerToggle() method implementation
void IRRemote::clearPowerToggle() {
    powerTogglePressed = false;
}

// simulatePowerToggle() method implementation
void IRRemote::simulatePowerToggle() {
    powerTogglePressed = true;
    Serial.println("Power toggle simulated!");
}

// isPowerCodeDetected() method implementation
bool IRRemote::isPowerCodeDetected() {
    return powerCodeDetected;
} 