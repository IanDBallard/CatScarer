# CatScarer Test Suite

This directory contains comprehensive Unity test suites for all CatScarer classes to ensure code quality and reliability.

## Test Coverage

### **PIRSensor Tests** (`test_PIRSensor.cpp`)
- ✅ Constructor and pin assignment
- ✅ Initialization and warm-up period (45 seconds)
- ✅ Motion detection during and after warm-up
- ✅ State management and transitions
- ✅ Pin getter functionality

### **Buzzer Tests** (`test_Buzzer.cpp`)
- ✅ Constructor and pin assignment
- ✅ Basic turnOn/turnOff functionality
- ✅ Siren mode activation and deactivation
- ✅ Non-blocking tone switching (800Hz ↔ 400Hz)
- ✅ Timing and duration management
- ✅ State tracking and queries

### **IRRemote Tests** (`test_IRRemote.cpp`)
- ✅ Constructor and pin assignment
- ✅ IR signal detection and command parsing
- ✅ Power toggle functionality
- ✅ Debouncing (200ms delay)
- ✅ Serial simulation for testing
- ✅ State management and clearing

### **DeviceStateMachine Tests** (`test_DeviceStateMachine.cpp`)
- ✅ Constructor and initialization
- ✅ All state transitions (WARMUP → STANDBY → ACTIVE → INACTIVE)
- ✅ IR power toggle integration
- ✅ Motion detection integration
- ✅ Duration management and timeouts
- ✅ Component coordination (LED, Fan, Buzzer)
- ✅ State name resolution

## Running Tests

### **Run All Tests**
```bash
pio test -e native
```

### **Run Individual Test Suites**
```bash
# PIRSensor tests only
pio test -e native -f test_PIRSensor

# Buzzer tests only
pio test -e native -f test_Buzzer

# IRRemote tests only
pio test -e native -f test_IRRemote

# DeviceStateMachine tests only
pio test -e native -f test_DeviceStateMachine
```

### **Run Specific Test Functions**
```bash
# Run specific test function
pio test -e native -f test_PIRSensor_constructor
pio test -e native -f test_Buzzer_siren_update_tone_switching
pio test -e native -f test_DeviceStateMachine_standby_to_active
```

## Test Architecture

### **Mock System**
- **Arduino Functions**: Mocked `millis()`, `tone()`, `noTone()`, `Serial`
- **Hardware Abstraction**: Mock classes for all components
- **Time Control**: Controlled timing for testing time-based behavior

### **Test Fixtures**
Each test suite includes:
- `setUp()`: Initialize test objects and reset mocks
- `tearDown()`: Clean up allocated memory
- Mock objects for isolated testing

### **Mock Classes**
- `MockPIRSensor`: Simulates PIR sensor behavior
- `MockPWMFan`: Tracks fan state and speed
- `MockBuzzer`: Simulates buzzer and siren behavior
- `MockRGBLED`: Captures LED color commands
- `MockIRRemote`: Simulates IR remote interactions

## Test Categories

### **Unit Tests**
- Individual method functionality
- Constructor and initialization
- State management
- Error handling

### **Integration Tests**
- Component interaction
- State machine transitions
- Timing and coordination
- End-to-end workflows

### **Behavioral Tests**
- Real-world scenarios
- Edge cases and timing
- State transitions
- User interactions

## Expected Test Results

### **All Tests Should Pass**
```
=== Running PIRSensor Tests ===
test_PIRSensor_constructor:PASS
test_PIRSensor_begin:PASS
test_PIRSensor_warmup_period:PASS
...

=== Running Buzzer Tests ===
test_Buzzer_constructor:PASS
test_Buzzer_startSiren:PASS
test_Buzzer_siren_update_tone_switching:PASS
...

=== Running IRRemote Tests ===
test_IRRemote_constructor:PASS
test_IRRemote_update_power_command:PASS
test_IRRemote_debouncing:PASS
...

=== Running DeviceStateMachine Tests ===
test_DeviceStateMachine_constructor:PASS
test_DeviceStateMachine_standby_to_active:PASS
test_DeviceStateMachine_active_duration:PASS
...

=== All Tests Complete ===
```

## Adding New Tests

### **For New Classes**
1. Create `test_ClassName.cpp`
2. Include Unity and class header
3. Add mock functions as needed
4. Create test functions with descriptive names
5. Add to `run_all_tests.cpp`

### **For New Methods**
1. Add test function to existing test file
2. Test normal operation
3. Test edge cases
4. Test error conditions
5. Update test runner

### **Test Naming Convention**
- `test_ClassName_methodName_behavior()`
- `test_ClassName_methodName_edgeCase()`
- `test_ClassName_methodName_errorCondition()`

## Continuous Integration

These tests can be integrated into CI/CD pipelines to:
- ✅ Ensure code quality
- ✅ Prevent regressions
- ✅ Validate refactoring
- ✅ Document expected behavior
- ✅ Enable safe development

## Troubleshooting

### **Test Failures**
1. Check mock setup in `setUp()`
2. Verify timing in time-based tests
3. Ensure proper state initialization
4. Check for memory leaks in `tearDown()`

### **Compilation Issues**
1. Verify Unity library is installed
2. Check include paths
3. Ensure mock functions are defined
4. Validate C++ standard compatibility 