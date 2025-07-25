#ifndef IRREMOTE_H
#define IRREMOTE_H

#include <Arduino.h>

class IRRemote {
private:
    int irPin;
    bool powerTogglePressed;
    unsigned long lastDebounceTime;
    static const unsigned long DEBOUNCE_DELAY = 200; // 200ms debounce
    
    // For testing purposes, we'll simulate IR input with a button or serial command
    bool powerCodeDetected;
    
public:
    // Constructor
    IRRemote(int pin);
    
    // Initializes the IR receiver
    void begin();
    
    // Updates the IR receiver state (should be called in main loop)
    void update();
    
    // Checks if power toggle button was pressed
    bool isPowerTogglePressed();
    
    // Clears the power toggle flag
    void clearPowerToggle();
    
    // For testing - simulate power toggle via serial command
    void simulatePowerToggle();
    
    // Checks if power code has been detected
    bool isPowerCodeDetected();
};

#endif // IRREMOTE_H 