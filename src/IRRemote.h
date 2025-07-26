#ifndef IRREMOTE_H
#define IRREMOTE_H

#include <Arduino.h>

class IRRemote {
private:
    int irPin;
    bool powerTogglePressed;
    unsigned long lastDebounceTime;
    static const unsigned long DEBOUNCE_DELAY = 200; // 200ms debounce
    
    // IR codes for Elegoo remote (adjust as needed)
    const unsigned int POWER_COMMAND = 0x45; // Example power button code
    
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
    
    // Checks and clears power toggle in one call (convenience method)
    bool checkPowerToggle();
    
    // For testing - simulate power toggle via serial command
    void simulatePowerToggle();
};

#endif // IRREMOTE_H 