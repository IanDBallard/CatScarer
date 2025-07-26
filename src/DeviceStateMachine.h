#ifndef DEVICESTATEMACHINE_H
#define DEVICESTATEMACHINE_H

#include <Arduino.h>
#include "PIRSensor.h"
#include "PWMFan.h"
#include "Buzzer.h"
#include "RGBLED.h"
#include "IRRemote.h"

// Device states
enum DeviceState {
    WARMUP,    // PIR sensor is warming up
    STANDBY,   // Ready for motion detection
    ACTIVE,    // Deterrent is active
    INACTIVE   // Device disabled, ignoring PIR input
};

class DeviceStateMachine {
private:
    // Component references
    PIRSensor& pir;
    PWMFan& fan;
    Buzzer& buzzer;
    RGBLED& led;
    IRRemote& ir;
    
    // State variables
    DeviceState currentState;
    unsigned long activationStartTime;
    unsigned long lastFlicker;
    bool ledState;
    
    // Configuration
    unsigned long activationDurationMs;
    int fanSpeedActivated;
    
    // State handling methods
    void handleWarmupState();
    void handleStandbyState();
    void handleActiveState();
    void handleInactiveState();
    
public:
    // Constructor
    DeviceStateMachine(PIRSensor& pirSensor, PWMFan& pwmFan, Buzzer& buzzerObj, 
                      RGBLED& rgbLed, IRRemote& irRemote, 
                      unsigned long durationMs = 5000, int fanSpeed = 255);
    
    // Initialize the state machine
    void begin();
    
    // Update state machine (call in main loop)
    void update();
    
    // Get current state
    DeviceState getCurrentState() const;
    
    // Force state change (for testing)
    void setState(DeviceState newState);
    
    // Get state name as string
    const char* getStateName() const;
};

#endif // DEVICESTATEMACHINE_H 