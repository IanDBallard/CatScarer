// CatScareDevice.ino

// Include our custom classes
#include "PIRSensor.h"
#include "PWMFan.h"
#include "Buzzer.h"
#include "RGBLED.h"
#include "IRRemote.h"
#include "DeviceStateMachine.h"

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

// IR Receiver Pin (TSOP1838)
const int IR_RECEIVER_PIN = 4; // Using D4 for IR receiver

// --- Device Behavior Parameters ---
const unsigned long ACTIVATION_DURATION_MS = 5000; // How long the fan/buzzer stays on (5 seconds)
const int FAN_SPEED_ACTIVATED = 255; // Fan speed when activated (0-255, 255 is full speed)

// --- Object Instantiation ---
// Create instances of our component classes
PIRSensor myPIR(PIR_PIN);
PWMFan myFan(FAN_PWM_PIN);
Buzzer myBuzzer(BUZZER_PIN);
RGBLED myLED(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN);
IRRemote myIRRemote(IR_RECEIVER_PIN);

// Create state machine instance
DeviceStateMachine stateMachine(myPIR, myFan, myBuzzer, myLED, myIRRemote, 
                                ACTIVATION_DURATION_MS, FAN_SPEED_ACTIVATED);

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Cat Scare Device Starting...");

  // Initialize all components
  myPIR.begin();
  myFan.begin();
  myBuzzer.begin();
  myLED.begin();
  myIRRemote.begin();
  stateMachine.begin();

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
  myIRRemote.update();
  
  // Update state machine
  stateMachine.update();
}

