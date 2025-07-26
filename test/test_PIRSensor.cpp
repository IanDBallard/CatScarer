#include <unity.h>
#include "PIRSensor.h"

// Mock Arduino functions for testing
unsigned long mockMillis = 0;
unsigned long millis() { return mockMillis; }

// Test fixture
PIRSensor* testPIR;

void setUp(void) {
    testPIR = new PIRSensor(2); // Pin 2
    mockMillis = 0;
}

void tearDown(void) {
    delete testPIR;
}

// Test constructor
void test_PIRSensor_constructor(void) {
    PIRSensor pir(5);
    TEST_ASSERT_EQUAL(5, pir.getPin());
}

// Test initialization
void test_PIRSensor_begin(void) {
    testPIR->begin();
    // Should start in initializing state
    TEST_ASSERT_TRUE(testPIR->isInitializing());
}

// Test warm-up period
void test_PIRSensor_warmup_period(void) {
    testPIR->begin();
    
    // Should be initializing for first 45 seconds
    for (int i = 0; i < 44; i++) {
        mockMillis += 1000; // 1 second increments
        testPIR->update();
        TEST_ASSERT_TRUE(testPIR->isInitializing());
    }
    
    // After 45 seconds, should be ready
    mockMillis += 1000;
    testPIR->update();
    TEST_ASSERT_FALSE(testPIR->isInitializing());
}

// Test motion detection after warm-up
void test_PIRSensor_motion_detection_after_warmup(void) {
    testPIR->begin();
    
    // Complete warm-up
    mockMillis = 45000;
    testPIR->update();
    TEST_ASSERT_FALSE(testPIR->isInitializing());
    
    // Initially no motion
    TEST_ASSERT_FALSE(testPIR->isMotionDetected());
    
    // Simulate motion detection (this would need mock digitalRead)
    // For now, test the interface
    TEST_ASSERT_FALSE(testPIR->isMotionDetected());
}

// Test motion detection during warm-up
void test_PIRSensor_motion_detection_during_warmup(void) {
    testPIR->begin();
    
    // During warm-up, motion detection should be false
    mockMillis = 10000; // 10 seconds into warm-up
    testPIR->update();
    TEST_ASSERT_TRUE(testPIR->isInitializing());
    TEST_ASSERT_FALSE(testPIR->isMotionDetected());
}

// Test pin getter
void test_PIRSensor_getPin(void) {
    PIRSensor pir(7);
    TEST_ASSERT_EQUAL(7, pir.getPin());
}

// Test update method
void test_PIRSensor_update(void) {
    testPIR->begin();
    
    // Update should not crash
    testPIR->update();
    TEST_PASS();
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_PIRSensor_constructor);
    RUN_TEST(test_PIRSensor_begin);
    RUN_TEST(test_PIRSensor_warmup_period);
    RUN_TEST(test_PIRSensor_motion_detection_after_warmup);
    RUN_TEST(test_PIRSensor_motion_detection_during_warmup);
    RUN_TEST(test_PIRSensor_getPin);
    RUN_TEST(test_PIRSensor_update);
    
    return UNITY_END();
} 