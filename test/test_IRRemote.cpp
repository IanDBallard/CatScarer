#include <unity.h>
#include "IRRemote.h"

// Mock Arduino functions for testing
unsigned long mockMillis = 0;
unsigned long millis() { return mockMillis; }

// Mock IR library functions
bool mockIrReceiverDecode = false;
bool mockIrReceiverDecoded = false;
int mockIrReceiverProtocol = 0;
int mockIrReceiverCommand = 0;
bool mockIrReceiverResumeCalled = false;

// Mock IR library structure
struct MockIrReceiver {
    bool decode() { return mockIrReceiverDecode; }
    void resume() { mockIrReceiverResumeCalled = true; }
    int decodedIRData_protocol;
    int decodedIRData_command;
} mockIrReceiver;

// Mock Serial functions
bool mockSerialAvailable = false;
char mockSerialReadChar = 0;

bool Serial_available() { return mockSerialAvailable; }
char Serial_read() { return mockSerialReadChar; }

// Test fixture
IRRemote* testIR;

void setUp(void) {
    testIR = new IRRemote(4); // Pin 4
    mockMillis = 0;
    mockIrReceiverDecode = false;
    mockIrReceiverDecoded = false;
    mockIrReceiverProtocol = 0;
    mockIrReceiverCommand = 0;
    mockIrReceiverResumeCalled = false;
    mockSerialAvailable = false;
    mockSerialReadChar = 0;
}

void tearDown(void) {
    delete testIR;
}

// Test constructor
void test_IRRemote_constructor(void) {
    IRRemote ir(5);
    TEST_ASSERT_EQUAL(5, ir.getPin());
}

// Test begin method
void test_IRRemote_begin(void) {
    testIR->begin();
    TEST_PASS(); // Should not crash
}

// Test update with no IR signal
void test_IRRemote_update_no_signal(void) {
    testIR->begin();
    testIR->update();
    
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed());
}

// Test update with IR signal but wrong command
void test_IRRemote_update_wrong_command(void) {
    testIR->begin();
    
    // Simulate IR signal with wrong command
    mockIrReceiverDecode = true;
    mockIrReceiverProtocol = 1; // NEC
    mockIrReceiverCommand = 0x44; // Wrong command (not 0x45)
    
    testIR->update();
    
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed());
    TEST_ASSERT_TRUE(mockIrReceiverResumeCalled);
}

// Test update with correct power command
void test_IRRemote_update_power_command(void) {
    testIR->begin();
    
    // Simulate IR signal with power command
    mockIrReceiverDecode = true;
    mockIrReceiverProtocol = 1; // NEC
    mockIrReceiverCommand = 0x45; // Power command
    
    testIR->update();
    
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
    TEST_ASSERT_TRUE(mockIrReceiverResumeCalled);
}

// Test debouncing
void test_IRRemote_debouncing(void) {
    testIR->begin();
    
    // First power command
    mockIrReceiverDecode = true;
    mockIrReceiverProtocol = 1;
    mockIrReceiverCommand = 0x45;
    testIR->update();
    
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
    
    // Clear the flag
    testIR->clearPowerToggle();
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed());
    
    // Second power command within debounce period (200ms)
    mockMillis = 100; // Less than 200ms
    mockIrReceiverDecode = true;
    mockIrReceiverCommand = 0x45;
    testIR->update();
    
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed()); // Should be debounced
    
    // Third power command after debounce period
    mockMillis = 250; // More than 200ms
    mockIrReceiverDecode = true;
    mockIrReceiverCommand = 0x45;
    testIR->update();
    
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed()); // Should work
}

// Test serial simulation
void test_IRRemote_serial_simulation(void) {
    testIR->begin();
    
    // Simulate 'P' command via serial
    mockSerialAvailable = true;
    mockSerialReadChar = 'P';
    
    testIR->update();
    
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
}

// Test serial simulation lowercase
void test_IRRemote_serial_simulation_lowercase(void) {
    testIR->begin();
    
    // Simulate 'p' command via serial
    mockSerialAvailable = true;
    mockSerialReadChar = 'p';
    
    testIR->update();
    
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
}

// Test clearPowerToggle method
void test_IRRemote_clearPowerToggle(void) {
    testIR->begin();
    
    // Set power toggle
    testIR->simulatePowerToggle();
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
    
    // Clear it
    testIR->clearPowerToggle();
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed());
}

// Test checkPowerToggle method
void test_IRRemote_checkPowerToggle(void) {
    testIR->begin();
    
    // Initially no power toggle
    TEST_ASSERT_FALSE(testIR->checkPowerToggle());
    
    // Set power toggle
    testIR->simulatePowerToggle();
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
    
    // Check and clear
    TEST_ASSERT_TRUE(testIR->checkPowerToggle());
    TEST_ASSERT_FALSE(testIR->isPowerTogglePressed());
    
    // Should be cleared after check
    TEST_ASSERT_FALSE(testIR->checkPowerToggle());
}

// Test simulatePowerToggle method
void test_IRRemote_simulatePowerToggle(void) {
    testIR->begin();
    
    testIR->simulatePowerToggle();
    TEST_ASSERT_TRUE(testIR->isPowerTogglePressed());
}

// Test pin getter
void test_IRRemote_getPin(void) {
    IRRemote ir(7);
    TEST_ASSERT_EQUAL(7, ir.getPin());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_IRRemote_constructor);
    RUN_TEST(test_IRRemote_begin);
    RUN_TEST(test_IRRemote_update_no_signal);
    RUN_TEST(test_IRRemote_update_wrong_command);
    RUN_TEST(test_IRRemote_update_power_command);
    RUN_TEST(test_IRRemote_debouncing);
    RUN_TEST(test_IRRemote_serial_simulation);
    RUN_TEST(test_IRRemote_serial_simulation_lowercase);
    RUN_TEST(test_IRRemote_clearPowerToggle);
    RUN_TEST(test_IRRemote_checkPowerToggle);
    RUN_TEST(test_IRRemote_simulatePowerToggle);
    RUN_TEST(test_IRRemote_getPin);
    
    return UNITY_END();
} 