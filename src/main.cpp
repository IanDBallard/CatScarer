#include <Arduino.h>

// Pin definitions for Arduino Nano
const int LED_PIN = 13;  // Built-in LED on Arduino Nano
const int BUILTIN_LED = 13;  // Alternative name for clarity

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("CatScarer initialized!");
  
  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  
  // Initial LED blink to indicate startup
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Main program loop
  Serial.println("CatScarer running...");
  
  // Blink LED every 2 seconds
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  
  delay(2000);
} 