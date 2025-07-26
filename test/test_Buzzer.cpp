#include <unity.h>
#include "Buzzer.h"

// Mock Arduino functions for testing
unsigned long mockMillis = 0;
unsigned long millis() { return mockMillis; }

// Mock tone and noTone functions
bool mockToneCalled = false;
int mockTonePin = -1;
int mockToneFreq = -1;
bool mockNoToneCalled = false;
int mockNoTonePin = -1;

void tone(int pin, int frequency) {
    mockToneCalled = true;
    mockTonePin = pin;
    mockToneFreq = frequency;
}

void noTone(int pin) {
    mockNoToneCalled = true;
    mockNoTonePin = pin;
}

// Test fixture
Buzzer* testBuzzer;

void setUp(void) {
    testBuzzer = new Buzzer(3); // Pin 3
    mockMillis = 0;
    mockToneCalled = false;
    mockNoToneCalled = false;
    mockTonePin = -1;
    mockToneFreq = -1;
    mockNoTonePin = -1;
}

void tearDown(void) {
    delete testBuzzer;
}

// Test constructor
void test_Buzzer_constructor(void) {
    Buzzer buzzer(5);
    TEST_ASSERT_EQUAL(5, buzzer.getPin());
}

// Test begin method
void test_Buzzer_begin(void) {
    testBuzzer->begin();
    TEST_PASS(); // Should not crash
}

// Test turnOn method
void test_Buzzer_turnOn(void) {
    testBuzzer->begin();
    testBuzzer->turnOn();
    
    // Should stop siren if active
    TEST_ASSERT_FALSE(testBuzzer->isSirenActive());
}

// Test turnOff method
void test_Buzzer_turnOff(void) {
    testBuzzer->begin();
    testBuzzer->turnOff();
    
    // Should stop siren if active
    TEST_ASSERT_FALSE(testBuzzer->isSirenActive());
}

// Test startSiren method
void test_Buzzer_startSiren(void) {
    testBuzzer->begin();
    testBuzzer->startSiren();
    
    TEST_ASSERT_TRUE(testBuzzer->isSirenActive());
    TEST_ASSERT_TRUE(mockToneCalled);
    TEST_ASSERT_EQUAL(3, mockTonePin);
    TEST_ASSERT_EQUAL(800, mockToneFreq); // High frequency
}

// Test stopSiren method
void test_Buzzer_stopSiren(void) {
    testBuzzer->begin();
    testBuzzer->startSiren();
    testBuzzer->stopSiren();
    
    TEST_ASSERT_FALSE(testBuzzer->isSirenActive());
    TEST_ASSERT_TRUE(mockNoToneCalled);
    TEST_ASSERT_EQUAL(3, mockNoTonePin);
}

// Test siren update - tone switching
void test_Buzzer_siren_update_tone_switching(void) {
    testBuzzer->begin();
    testBuzzer->startSiren();
    
    // Reset mock
    mockToneCalled = false;
    mockToneFreq = -1;
    
    // Wait for tone change (300ms)
    mockMillis = 300;
    testBuzzer->update();
    
    TEST_ASSERT_TRUE(mockToneCalled);
    TEST_ASSERT_EQUAL(400, mockToneFreq); // Low frequency
    
    // Wait for next tone change
    mockMillis = 600;
    mockToneCalled = false;
    testBuzzer->update();
    
    TEST_ASSERT_TRUE(mockToneCalled);
    TEST_ASSERT_EQUAL(800, mockToneFreq); // Back to high frequency
}

// Test siren update - no change before duration
void test_Buzzer_siren_update_no_change_before_duration(void) {
    testBuzzer->begin();
    testBuzzer->startSiren();
    
    // Reset mock
    mockToneCalled = false;
    
    // Update before tone change duration
    mockMillis = 150;
    testBuzzer->update();
    
    TEST_ASSERT_FALSE(mockToneCalled); // Should not change tone yet
}

// Test siren update when not active
void test_Buzzer_siren_update_when_not_active(void) {
    testBuzzer->begin();
    
    // Update without starting siren
    testBuzzer->update();
    
    TEST_ASSERT_FALSE(mockToneCalled);
    TEST_ASSERT_FALSE(mockNoToneCalled);
}

// Test isSirenActive method
void test_Buzzer_isSirenActive(void) {
    testBuzzer->begin();
    
    // Initially not active
    TEST_ASSERT_FALSE(testBuzzer->isSirenActive());
    
    // Start siren
    testBuzzer->startSiren();
    TEST_ASSERT_TRUE(testBuzzer->isSirenActive());
    
    // Stop siren
    testBuzzer->stopSiren();
    TEST_ASSERT_FALSE(testBuzzer->isSirenActive());
}

// Test pin getter
void test_Buzzer_getPin(void) {
    Buzzer buzzer(7);
    TEST_ASSERT_EQUAL(7, buzzer.getPin());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_Buzzer_constructor);
    RUN_TEST(test_Buzzer_begin);
    RUN_TEST(test_Buzzer_turnOn);
    RUN_TEST(test_Buzzer_turnOff);
    RUN_TEST(test_Buzzer_startSiren);
    RUN_TEST(test_Buzzer_stopSiren);
    RUN_TEST(test_Buzzer_siren_update_tone_switching);
    RUN_TEST(test_Buzzer_siren_update_no_change_before_duration);
    RUN_TEST(test_Buzzer_siren_update_when_not_active);
    RUN_TEST(test_Buzzer_isSirenActive);
    RUN_TEST(test_Buzzer_getPin);
    
    return UNITY_END();
} 