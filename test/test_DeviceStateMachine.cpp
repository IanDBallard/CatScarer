#include <unity.h>
#include "DeviceStateMachine.h"
#include "PIRSensor.h"
#include "PWMFan.h"
#include "Buzzer.h"
#include "RGBLED.h"
#include "IRRemote.h"

// Mock Arduino functions for testing
unsigned long mockMillis = 0;
unsigned long millis() { return mockMillis; }

// Mock component classes for testing
class MockPIRSensor : public PIRSensor {
public:
    MockPIRSensor(int pin) : PIRSensor(pin) {}
    bool mockIsInitializing = true;
    bool mockIsMotionDetected = false;
    
    bool isInitializing() override { return mockIsInitializing; }
    bool isMotionDetected() override { return mockIsMotionDetected; }
    void update() override {} // No-op for testing
};

class MockPWMFan : public PWMFan {
public:
    MockPWMFan(int pin) : PWMFan(pin) {}
    bool mockIsOn = false;
    int mockSpeed = 0;
    
    void turnOn(int speed) override { mockIsOn = true; mockSpeed = speed; }
    void turnOff() override { mockIsOn = false; mockSpeed = 0; }
    bool isOn() const { return mockIsOn; }
    int getSpeed() const { return mockSpeed; }
};

class MockBuzzer : public Buzzer {
public:
    MockBuzzer(int pin) : Buzzer(pin) {}
    bool mockSirenActive = false;
    
    void startSiren() override { mockSirenActive = true; }
    void stopSiren() override { mockSirenActive = false; }
    bool isSirenActive() const override { return mockSirenActive; }
    void update() override {} // No-op for testing
};

class MockRGBLED : public RGBLED {
public:
    MockRGBLED(int redPin, int greenPin, int bluePin) : RGBLED(redPin, greenPin, bluePin) {}
    int mockRed = 0, mockGreen = 0, mockBlue = 0;
    
    void setColor(int red, int green, int blue) override {
        mockRed = red; mockGreen = green; mockBlue = blue;
    }
};

class MockIRRemote : public IRRemote {
public:
    MockIRRemote(int pin) : IRRemote(pin) {}
    bool mockPowerToggle = false;
    
    bool checkPowerToggle() override { 
        if (mockPowerToggle) {
            mockPowerToggle = false;
            return true;
        }
        return false;
    }
};

// Test fixture
MockPIRSensor* mockPIR;
MockPWMFan* mockFan;
MockBuzzer* mockBuzzer;
MockRGBLED* mockLED;
MockIRRemote* mockIR;
DeviceStateMachine* stateMachine;

void setUp(void) {
    mockPIR = new MockPIRSensor(2);
    mockFan = new MockPWMFan(9);
    mockBuzzer = new MockBuzzer(3);
    mockLED = new MockRGBLED(5, 6, 8);
    mockIR = new MockIRRemote(4);
    
    stateMachine = new DeviceStateMachine(*mockPIR, *mockFan, *mockBuzzer, *mockLED, *mockIR, 5000, 255);
    mockMillis = 0;
}

void tearDown(void) {
    delete stateMachine;
    delete mockIR;
    delete mockLED;
    delete mockBuzzer;
    delete mockFan;
    delete mockPIR;
}

// Test constructor
void test_DeviceStateMachine_constructor(void) {
    TEST_ASSERT_EQUAL(WARMUP, stateMachine->getCurrentState());
}

// Test begin method
void test_DeviceStateMachine_begin(void) {
    stateMachine->begin();
    TEST_ASSERT_EQUAL(WARMUP, stateMachine->getCurrentState());
}

// Test warmup state
void test_DeviceStateMachine_warmup_state(void) {
    stateMachine->begin();
    
    // Should start in warmup
    TEST_ASSERT_EQUAL(WARMUP, stateMachine->getCurrentState());
    
    // PIR should be initializing
    mockPIR->mockIsInitializing = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(WARMUP, stateMachine->getCurrentState());
    
    // After PIR finishes initializing, should go to standby
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
}

// Test warmup state with IR power toggle
void test_DeviceStateMachine_warmup_with_ir_toggle(void) {
    stateMachine->begin();
    
    // In warmup state
    TEST_ASSERT_EQUAL(WARMUP, stateMachine->getCurrentState());
    
    // IR power toggle should go to inactive
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(INACTIVE, stateMachine->getCurrentState());
}

// Test standby state
void test_DeviceStateMachine_standby_state(void) {
    stateMachine->begin();
    
    // Complete warmup
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
    
    // Should show green LED
    TEST_ASSERT_EQUAL(0, mockLED->mockRed);
    TEST_ASSERT_EQUAL(255, mockLED->mockGreen);
    TEST_ASSERT_EQUAL(0, mockLED->mockBlue);
}

// Test standby to active transition
void test_DeviceStateMachine_standby_to_active(void) {
    stateMachine->begin();
    
    // Complete warmup
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
    
    // Motion detected should go to active
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    // Should show red LED
    TEST_ASSERT_EQUAL(255, mockLED->mockRed);
    TEST_ASSERT_EQUAL(0, mockLED->mockGreen);
    TEST_ASSERT_EQUAL(0, mockLED->mockBlue);
    
    // Fan should be on
    TEST_ASSERT_TRUE(mockFan->isOn());
    TEST_ASSERT_EQUAL(255, mockFan->getSpeed());
    
    // Buzzer should be active
    TEST_ASSERT_TRUE(mockBuzzer->isSirenActive());
}

// Test active state duration
void test_DeviceStateMachine_active_duration(void) {
    stateMachine->begin();
    
    // Go to active state
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    // After duration expires, should go back to standby
    mockMillis = 5000; // 5 seconds
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
    
    // Fan should be off
    TEST_ASSERT_FALSE(mockFan->isOn());
    
    // Buzzer should be off
    TEST_ASSERT_FALSE(mockBuzzer->isSirenActive());
}

// Test active state with motion refresh
void test_DeviceStateMachine_active_motion_refresh(void) {
    stateMachine->begin();
    
    // Go to active state
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    // Motion continues, should stay active
    mockMillis = 2000;
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    // After duration expires, should go back to standby
    mockMillis = 7000; // 5 seconds from last motion
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
}

// Test active state with IR power toggle
void test_DeviceStateMachine_active_with_ir_toggle(void) {
    stateMachine->begin();
    
    // Go to active state
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    // IR power toggle should go to inactive and stop deterrents
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(INACTIVE, stateMachine->getCurrentState());
    
    // Fan should be off
    TEST_ASSERT_FALSE(mockFan->isOn());
    
    // Buzzer should be off
    TEST_ASSERT_FALSE(mockBuzzer->isSirenActive());
}

// Test inactive state
void test_DeviceStateMachine_inactive_state(void) {
    stateMachine->begin();
    
    // Go to inactive state
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(INACTIVE, stateMachine->getCurrentState());
    
    // Should show yellow LED
    TEST_ASSERT_EQUAL(255, mockLED->mockRed);
    TEST_ASSERT_EQUAL(255, mockLED->mockGreen);
    TEST_ASSERT_EQUAL(0, mockLED->mockBlue);
}

// Test inactive to standby transition
void test_DeviceStateMachine_inactive_to_standby(void) {
    stateMachine->begin();
    
    // Go to inactive state
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(INACTIVE, stateMachine->getCurrentState());
    
    // IR power toggle should go to standby
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
}

// Test getStateName method
void test_DeviceStateMachine_getStateName(void) {
    stateMachine->begin();
    
    TEST_ASSERT_EQUAL_STRING("WARMUP", stateMachine->getStateName());
    
    // Go to standby
    mockPIR->mockIsInitializing = false;
    stateMachine->update();
    TEST_ASSERT_EQUAL_STRING("STANDBY", stateMachine->getStateName());
    
    // Go to active
    mockPIR->mockIsMotionDetected = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL_STRING("ACTIVE", stateMachine->getStateName());
    
    // Go to inactive
    mockIR->mockPowerToggle = true;
    stateMachine->update();
    TEST_ASSERT_EQUAL_STRING("INACTIVE", stateMachine->getStateName());
}

// Test setState method
void test_DeviceStateMachine_setState(void) {
    stateMachine->begin();
    
    stateMachine->setState(STANDBY);
    TEST_ASSERT_EQUAL(STANDBY, stateMachine->getCurrentState());
    
    stateMachine->setState(ACTIVE);
    TEST_ASSERT_EQUAL(ACTIVE, stateMachine->getCurrentState());
    
    stateMachine->setState(INACTIVE);
    TEST_ASSERT_EQUAL(INACTIVE, stateMachine->getCurrentState());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_DeviceStateMachine_constructor);
    RUN_TEST(test_DeviceStateMachine_begin);
    RUN_TEST(test_DeviceStateMachine_warmup_state);
    RUN_TEST(test_DeviceStateMachine_warmup_with_ir_toggle);
    RUN_TEST(test_DeviceStateMachine_standby_state);
    RUN_TEST(test_DeviceStateMachine_standby_to_active);
    RUN_TEST(test_DeviceStateMachine_active_duration);
    RUN_TEST(test_DeviceStateMachine_active_motion_refresh);
    RUN_TEST(test_DeviceStateMachine_active_with_ir_toggle);
    RUN_TEST(test_DeviceStateMachine_inactive_state);
    RUN_TEST(test_DeviceStateMachine_inactive_to_standby);
    RUN_TEST(test_DeviceStateMachine_getStateName);
    RUN_TEST(test_DeviceStateMachine_setState);
    
    return UNITY_END();
} 