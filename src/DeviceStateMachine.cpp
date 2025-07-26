#include "DeviceStateMachine.h"

// Constructor implementation
DeviceStateMachine::DeviceStateMachine(PIRSensor& pirSensor, PWMFan& pwmFan, Buzzer& buzzerObj, 
                                       RGBLED& rgbLed, IRRemote& irRemote, 
                                       unsigned long durationMs, int fanSpeed)
    : pir(pirSensor), fan(pwmFan), buzzer(buzzerObj), led(rgbLed), ir(irRemote),
      currentState(WARMUP), activationStartTime(0), lastFlicker(0), ledState(false),
      activationDurationMs(durationMs), fanSpeedActivated(fanSpeed) {
}

// begin() method implementation
void DeviceStateMachine::begin() {
    currentState = WARMUP;
    activationStartTime = 0;
    lastFlicker = 0;
    ledState = false;
    Serial.println("Device State Machine initialized.");
}

// update() method implementation
void DeviceStateMachine::update() {
    // State machine logic
    switch (currentState) {
        case WARMUP:
            handleWarmupState();
            break;
            
        case STANDBY:
            handleStandbyState();
            break;
            
        case ACTIVE:
            handleActiveState();
            break;
            
        case INACTIVE:
            handleInactiveState();
            break;
    }
}

// handleWarmupState() method implementation
void DeviceStateMachine::handleWarmupState() {
    // Check for IR power toggle (can interrupt warm-up)
    if (ir.checkPowerToggle()) {
        currentState = INACTIVE;
        Serial.println("IR Power toggle: Entering inactive mode.");
        return;
    }
    
    // Flicker blue LED during warm-up
    if (millis() - lastFlicker >= 500) { // Flicker every 500ms
        ledState = !ledState;
        led.setColor(0, 0, ledState ? 255 : 0); // Blue on/off
        lastFlicker = millis();
    }
    
    // Check if warm-up is complete
    if (!pir.isInitializing()) {
        currentState = STANDBY;
        Serial.println("Warm-up complete. Entering standby mode.");
    }
}

// handleStandbyState() method implementation
void DeviceStateMachine::handleStandbyState() {
    // Check for IR power toggle
    if (ir.checkPowerToggle()) {
        currentState = INACTIVE;
        Serial.println("IR Power toggle: Entering inactive mode.");
        return;
    }
    
    // Show green LED to indicate ready state
    led.setColor(0, 255, 0); // Green = ready
    
    // Check for motion detection
    if (pir.isMotionDetected()) {
        // Transition to active state
        currentState = ACTIVE;
        activationStartTime = millis();
        
        Serial.println("Motion detected! Activating deterrent...");
        Serial.println("Setting LED to RED (255,0,0)");
        led.setColor(255, 0, 0); // Red
        fan.turnOn(fanSpeedActivated);
        buzzer.startSiren();
    }
}

// handleActiveState() method implementation
void DeviceStateMachine::handleActiveState() {
    // Check for IR power toggle (can interrupt active state)
    if (ir.checkPowerToggle()) {
        currentState = INACTIVE;
        Serial.println("IR Power toggle: Entering inactive mode.");
        // Stop deterrent immediately
        fan.turnOff();
        buzzer.stopSiren();
        return;
    }
    
    // Check if motion is still detected (refresh timer)
    if (pir.isMotionDetected()) {
        activationStartTime = millis(); // Refresh the timer
    }
    
    // Check if activation duration has expired
    if (millis() - activationStartTime >= activationDurationMs) {
        // Transition back to standby
        currentState = STANDBY;
        
        Serial.println("Deactivating deterrent...");
        Serial.println("Setting LED to GREEN (0,255,0)");
        led.setColor(0, 255, 0); // Green
        fan.turnOff();
        buzzer.stopSiren();
    }
}

// handleInactiveState() method implementation
void DeviceStateMachine::handleInactiveState() {
    // Check for IR power toggle to exit inactive state
    if (ir.checkPowerToggle()) {
        currentState = STANDBY;
        Serial.println("IR Power toggle: Exiting inactive mode, entering standby.");
        return;
    }
    
    // Show yellow LED to indicate inactive state (red + green)
    led.setColor(255, 255, 0); // Yellow = inactive
    
    // In inactive state, ignore all PIR motion detection
    // No deterrent activation occurs
}

// getCurrentState() method implementation
DeviceState DeviceStateMachine::getCurrentState() const {
    return currentState;
}

// setState() method implementation
void DeviceStateMachine::setState(DeviceState newState) {
    currentState = newState;
    Serial.print("State changed to: ");
    Serial.println(getStateName());
}

// getStateName() method implementation
const char* DeviceStateMachine::getStateName() const {
    switch (currentState) {
        case WARMUP: return "WARMUP";
        case STANDBY: return "STANDBY";
        case ACTIVE: return "ACTIVE";
        case INACTIVE: return "INACTIVE";
        default: return "UNKNOWN";
    }
} 