#include <unity.h>

// Include all test suites
extern void test_PIRSensor_constructor(void);
extern void test_PIRSensor_begin(void);
extern void test_PIRSensor_warmup_period(void);
extern void test_PIRSensor_motion_detection_after_warmup(void);
extern void test_PIRSensor_motion_detection_during_warmup(void);
extern void test_PIRSensor_getPin(void);
extern void test_PIRSensor_update(void);

extern void test_Buzzer_constructor(void);
extern void test_Buzzer_begin(void);
extern void test_Buzzer_turnOn(void);
extern void test_Buzzer_turnOff(void);
extern void test_Buzzer_startSiren(void);
extern void test_Buzzer_stopSiren(void);
extern void test_Buzzer_siren_update_tone_switching(void);
extern void test_Buzzer_siren_update_no_change_before_duration(void);
extern void test_Buzzer_siren_update_when_not_active(void);
extern void test_Buzzer_isSirenActive(void);
extern void test_Buzzer_getPin(void);

extern void test_IRRemote_constructor(void);
extern void test_IRRemote_begin(void);
extern void test_IRRemote_update_no_signal(void);
extern void test_IRRemote_update_wrong_command(void);
extern void test_IRRemote_update_power_command(void);
extern void test_IRRemote_debouncing(void);
extern void test_IRRemote_serial_simulation(void);
extern void test_IRRemote_serial_simulation_lowercase(void);
extern void test_IRRemote_clearPowerToggle(void);
extern void test_IRRemote_checkPowerToggle(void);
extern void test_IRRemote_simulatePowerToggle(void);
extern void test_IRRemote_getPin(void);

extern void test_DeviceStateMachine_constructor(void);
extern void test_DeviceStateMachine_begin(void);
extern void test_DeviceStateMachine_warmup_state(void);
extern void test_DeviceStateMachine_warmup_with_ir_toggle(void);
extern void test_DeviceStateMachine_standby_state(void);
extern void test_DeviceStateMachine_standby_to_active(void);
extern void test_DeviceStateMachine_active_duration(void);
extern void test_DeviceStateMachine_active_motion_refresh(void);
extern void test_DeviceStateMachine_active_with_ir_toggle(void);
extern void test_DeviceStateMachine_inactive_state(void);
extern void test_DeviceStateMachine_inactive_to_standby(void);
extern void test_DeviceStateMachine_getStateName(void);
extern void test_DeviceStateMachine_setState(void);

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    // PIRSensor Tests
    printf("\n=== Running PIRSensor Tests ===\n");
    RUN_TEST(test_PIRSensor_constructor);
    RUN_TEST(test_PIRSensor_begin);
    RUN_TEST(test_PIRSensor_warmup_period);
    RUN_TEST(test_PIRSensor_motion_detection_after_warmup);
    RUN_TEST(test_PIRSensor_motion_detection_during_warmup);
    RUN_TEST(test_PIRSensor_getPin);
    RUN_TEST(test_PIRSensor_update);
    
    // Buzzer Tests
    printf("\n=== Running Buzzer Tests ===\n");
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
    
    // IRRemote Tests
    printf("\n=== Running IRRemote Tests ===\n");
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
    
    // DeviceStateMachine Tests
    printf("\n=== Running DeviceStateMachine Tests ===\n");
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
    
    printf("\n=== All Tests Complete ===\n");
    return UNITY_END();
} 