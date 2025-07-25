#include "IRRemote.h"
#include <IRremote.hpp>

// Constructor implementation
IRRemote::IRRemote(int pin) {
    irPin = pin;
    powerTogglePressed = false;
    lastDebounceTime = 0;
}

// begin() method implementation
void IRRemote::begin() {
    // Initialize the IR receiver using the correct API
    IrReceiver.begin(irPin);
    Serial.println("IR Receiver initialized on pin " + String(irPin));
    Serial.println("For testing: Send 'P' via serial to simulate power toggle");
}

// update() method implementation
void IRRemote::update() {
    // Check for IR input using the correct API
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.protocol == NEC || IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // Check if this is the power command
            if (IrReceiver.decodedIRData.command == POWER_COMMAND) {
                unsigned long currentTime = millis();
                if (currentTime - lastDebounceTime >= DEBOUNCE_DELAY) {
                    powerTogglePressed = true;
                    Serial.println("Power toggle received via IR!");
                    lastDebounceTime = currentTime;
                }
            }
        }
        IrReceiver.resume(); // Receive the next value
    }
    
    // Check for serial command to simulate power toggle (for testing)
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'P' || command == 'p') {
            simulatePowerToggle();
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