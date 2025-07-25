// CatScareDevice.ino

// Include our custom classes
#include "PIRSensor.h"
#include "PWMFan.h"
#include "Buzzer.h"
#include "RGBLED.h"

// --- Pin Definitions ---
// Connect PIR Sensor OUT pin to this digital input pin
const int PIR_PIN = 2; // Using D2 for PIR sensor

// Connect Fan PWM input wire (usually yellow) to this PWM pin
// The fan's power is controlled by the TIP120 transistor circuit.
const int FAN_PWM_PIN = 9; // Using D9 for PWM fan control (must be a PWM pin)

// Connect Buzzer signal pin (via 2N2222 transistor circuit) to this digital output pin
const int BUZZER_PIN = 3; // Using D3 for buzzer control

// RGB LED Pins (connect via current-limiting resistors)
// Red and Green pins are PWM-capable for variable brightness
// Blue pin is digital only (on/off)
const int LED_RED_PIN   = 5; // Using D5 for Red LED (PWM)
const int LED_GREEN_PIN = 6; // Using D6 for Green LED (PWM)
const int LED_BLUE_PIN  = 8; // Using D8 for Blue LED (digital only)

// --- Device Behavior Parameters ---
const unsigned long ACTIVATION_DURATION_MS = 5000; // How long the fan/buzzer stays on (5 seconds)
const int FAN_SPEED_ACTIVATED = 255; // Fan speed when activated (0-255, 255 is full speed)

// --- State Machine ---
enum DeviceState {
    WARMUP,   // PIR sensor is warming up
    STANDBY,  // Ready for motion detection
    ACTIVE    // Deterrent is active
};

// --- Object Instantiation ---
// Create instances of our component classes
PIRSensor myPIR(PIR_PIN);
PWMFan myFan(FAN_PWM_PIN);
Buzzer myBuzzer(BUZZER_PIN);
RGBLED myLED(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);

// --- State Variables ---
DeviceState currentState = WARMUP;
unsigned long activationStartTime = 0; // Stores the millis() when activation started
unsigned long lastFlicker = 0; // For blue LED flickering during warm-up
bool ledState = false; // For blue LED flickering during warm-up

// --- Function Declarations ---
void handleWarmupState();
void handleStandbyState();
void handleActiveState();

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Cat Scare Device Starting...");

  // Initialize all components
  myPIR.begin();
  myFan.begin();
  myBuzzer.begin();
  myLED.begin();

  // LED Test - cycle through colors
  Serial.println("Testing LED colors...");
  Serial.println("NOTE: If LED is dim, check resistor value (should be 220-330Ω)");
  
  // Test each pin individually to identify connections
  Serial.println("Testing RED pin (D5)...");
  myLED.setColor(255, 0, 0); // Red ON, others OFF
  delay(3000);
  
  Serial.println("Testing GREEN pin (D6)...");
  myLED.setColor(0, 255, 0); // Green ON, others OFF
  delay(3000);
  
  Serial.println("Testing BLUE pin (D8)...");
  myLED.setColor(0, 0, 255); // Blue ON, others OFF
  delay(3000);
  
  // Test all off
  myLED.setColor(0, 0, 0); // All OFF
  Serial.println("ALL LEDS OFF");
  delay(2000);

  Serial.println("PIR sensor warming up...");
  Serial.println("Device ready.");
}

void loop() {
  // Update all component states
  myPIR.update();
  myBuzzer.update();
  
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
  }
}

void handleWarmupState() {
  // Flicker blue LED during warm-up
  if (millis() - lastFlicker >= 500) { // Flicker every 500ms
    ledState = !ledState;
    myLED.setColor(0, 0, ledState ? 255 : 0); // Blue on/off
    lastFlicker = millis();
  }
  
  // Check if warm-up is complete
  if (!myPIR.isInitializing()) {
    currentState = STANDBY;
    Serial.println("Warm-up complete. Entering standby mode.");
  }
}

void handleStandbyState() {
  // Show green LED to indicate ready state
  myLED.setColor(0, 255, 0); // Green = ready
  
  // Check for motion detection
  if (myPIR.isMotionDetected()) {
    // Transition to active state
    currentState = ACTIVE;
    activationStartTime = millis();
    
    Serial.println("Motion detected! Activating deterrent...");
    Serial.println("Setting LED to RED (255,0,0)");
    myLED.setColor(255, 0, 0); // Red
    myFan.turnOn(FAN_SPEED_ACTIVATED);
    myBuzzer.startSiren();
  }
}

void handleActiveState() {
  // Check if motion is still detected (refresh timer)
  if (myPIR.isMotionDetected()) {
    activationStartTime = millis(); // Refresh the timer
  }
  
  // Check if activation duration has expired
  if (millis() - activationStartTime >= ACTIVATION_DURATION_MS) {
    // Transition back to standby
    currentState = STANDBY;
    
    Serial.println("Deactivating deterrent...");
    Serial.println("Setting LED to GREEN (0,255,0)");
    myLED.setColor(0, 255, 0); // Green
    myFan.turnOff();
    myBuzzer.stopSiren();
  }
}