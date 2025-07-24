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
// Make sure these are PWM-capable pins for full color control
const int LED_RED_PIN   = 5; // Using D5 for Red LED (PWM)
const int LED_GREEN_PIN = 6; // Using D6 for Green LED (PWM)
const int LED_BLUE_PIN  = 8; // Using D8 for Blue LED (digital only)

// --- Device Behavior Parameters ---
const unsigned long ACTIVATION_DURATION_MS = 5000; // How long the fan/buzzer stays on (5 seconds)
const int FAN_SPEED_ACTIVATED = 255; // Fan speed when activated (0-255, 255 is full speed)

// --- Object Instantiation ---
// Create instances of our component classes
PIRSensor myPIR(PIR_PIN);
PWMFan myFan(FAN_PWM_PIN);
Buzzer myBuzzer(BUZZER_PIN);
RGBLED myLED(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);

// --- State Variables ---
bool isActive = false; // True if the deterrent is currently activated
unsigned long activationStartTime = 0; // Stores the millis() when activation started

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
  // Update buzzer siren state (non-blocking)
  myBuzzer.update();
  
  // Check if PIR sensor is still initializing
  if (myPIR.isInitializing()) {
    // Flicker blue LED during warm-up
    static unsigned long lastFlicker = 0;
    static bool ledState = false;
    
    if (millis() - lastFlicker >= 500) { // Flicker every 500ms
      ledState = !ledState;
      myLED.setColor(0, 0, ledState ? 255 : 0); // Blue on/off
      lastFlicker = millis();
    }
    return; // Don't process motion detection during warm-up
  }
  
  // PIR is ready - normal operation
  if (!isActive) {
    myLED.setColor(0, 255, 0); // Green = ready
  }
  
  // Check if motion is detected
  if (myPIR.isMotionDetected()) {
    if (!isActive) {
      // Motion detected and device is not currently active: ACTIVATE!
      Serial.println("Motion detected! Activating deterrent...");
      Serial.println("Setting LED to RED (255,0,0)");
      myLED.setColor(255, 0, 0); // Red
      myFan.turnOn(FAN_SPEED_ACTIVATED);
      myBuzzer.startSiren(); // Start siren instead of simple turnOn
      isActive = true; // Set activation flag
      activationStartTime = millis(); // Record activation start time
    }
    // If motion is detected while already active, refresh the timer
    activationStartTime = millis();
  }

  // Check if the deterrent needs to be deactivated
  if (isActive && (millis() - activationStartTime >= ACTIVATION_DURATION_MS)) {
    // Deterrent was active and the duration has passed, or motion stopped.
    Serial.println("Deactivating deterrent...");
    Serial.println("Setting LED to GREEN (0,255,0)");
    myLED.setColor(0, 255, 0); // Green
    myFan.turnOff();
    myBuzzer.stopSiren(); // Stop siren instead of simple turnOff
    isActive = false; // Reset activation flag
  }

  // Small delay to prevent continuous reading and reduce CPU load
  delay(50);
}