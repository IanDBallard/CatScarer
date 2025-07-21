# Test Directory

This directory contains unit tests for your Arduino project.

## Usage

- Place test files here with the `.cpp` extension
- Tests will run when you use `pio test`
- PlatformIO supports Unity test framework by default

## Example Test

```cpp
#include <unity.h>
#include "your_header.h"

void setUp(void) {
    // Set up code that runs before each test
}

void tearDown(void) {
    // Clean up code that runs after each test
}

void test_function_should_do_something(void) {
    // Your test code here
    TEST_ASSERT_EQUAL(1, 1);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_do_something);
    return UNITY_END();
}
```

## Running Tests

```bash
pio test
pio test -e uno
pio test -f test_function_should_do_something
``` 