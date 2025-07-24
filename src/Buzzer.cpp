#include "Buzzer.h"

// Constructor implementation
Buzzer::Buzzer(int pin) : _buzzerPin(pin), _sirenActive(false), _currentTone(false), 
                          _lastToneChange(0), _toneDuration(300), _highFreq(800), _lowFreq(400) {
    // Initialize all member variables.
}

// begin() method implementation
void Buzzer::begin() {
    pinMode(_buzzerPin, OUTPUT); // Set the buzzer pin as an output.
    turnOff(); // Ensure the buzzer starts in an off state.
}

// turnOn() method implementation
void Buzzer::turnOn() {
    stopSiren(); // Stop siren if active
    digitalWrite(_buzzerPin, HIGH); // Write HIGH to turn the buzzer on.
}

// turnOff() method implementation
void Buzzer::turnOff() {
    stopSiren(); // Stop siren if active
    digitalWrite(_buzzerPin, LOW); // Write LOW to turn the buzzer off.
}

// startSiren() method implementation
void Buzzer::startSiren() {
    _sirenActive = true;
    _currentTone = true; // Start with high frequency
    _lastToneChange = millis();
    tone(_buzzerPin, _highFreq); // Start with high frequency tone
}

// stopSiren() method implementation
void Buzzer::stopSiren() {
    _sirenActive = false;
    noTone(_buzzerPin); // Stop the tone
    digitalWrite(_buzzerPin, LOW); // Ensure pin is LOW
}

// update() method implementation - call this in main loop
void Buzzer::update() {
    if (!_sirenActive) return; // Do nothing if siren is not active
    
    unsigned long currentTime = millis();
    
    // Check if it's time to change the tone
    if (currentTime - _lastToneChange >= _toneDuration) {
        _currentTone = !_currentTone; // Toggle tone
        _lastToneChange = currentTime;
        
        // Play the appropriate frequency
        if (_currentTone) {
            tone(_buzzerPin, _highFreq);
        } else {
            tone(_buzzerPin, _lowFreq);
        }
    }
}

// isSirenActive() method implementation
bool Buzzer::isSirenActive() const {
    return _sirenActive;
}