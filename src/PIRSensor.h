#ifndef PIR_SENSOR_H
#define PIR_SENSOR_H

#include <Arduino.h>

class PIRSensor {
public:
    // Constructor: Initializes the PIR sensor with the given pin.
    PIRSensor(int pin);

    // Initializes the sensor pin as an input and starts warm-up timer.
    void begin();

    // Updates the sensor state (should be called in main loop).
    void update();

    // Checks if motion is currently detected.
    bool isMotionDetected();
    
    // Returns true if sensor is still in warm-up period.
    bool isInitializing();

private:
    int _pirPin; // Private member to store the digital pin connected to the PIR sensor.
    unsigned long _warmUpStartTime; // When warm-up period started
    unsigned long _warmUpDuration; // How long warm-up should take (45 seconds)
    bool _isInitialized; // Whether warm-up is complete
};

#endif // PIR_SENSOR_H