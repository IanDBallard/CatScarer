#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    // Constructor: Initializes the buzzer with the given pin.
    Buzzer(int pin);

    // Initializes the buzzer pin as an output.
    void begin();

    // Turns the buzzer on with continuous tone.
    void turnOn();

    // Turns the buzzer off.
    void turnOff();

    // Starts siren mode (non-blocking).
    void startSiren();

    // Stops siren mode.
    void stopSiren();

    // Updates siren state - call this in main loop for non-blocking operation.
    void update();

    // Returns true if siren is currently active.
    bool isSirenActive() const;

private:
    int _buzzerPin;           // Private member to store the digital pin connected to the buzzer.
    bool _sirenActive;        // Whether siren mode is active
    bool _currentTone;        // Current tone state (true = high freq, false = low freq)
    unsigned long _lastToneChange; // Last time the tone changed
    unsigned long _toneDuration;   // Duration of each tone in milliseconds
    int _highFreq;            // High frequency for siren (Hz)
    int _lowFreq;             // Low frequency for siren (Hz)
};

#endif // BUZZER_H