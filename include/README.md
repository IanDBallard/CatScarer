# Include Directory

This directory contains header files (.h) for your Arduino project.

## Usage

- Place custom header files here
- Include them in your main.cpp using: `#include "your_header.h"`
- PlatformIO will automatically include this directory in the build path

## Example

```cpp
// my_sensor.h
#ifndef MY_SENSOR_H
#define MY_SENSOR_H

class MySensor {
  public:
    void begin();
    int read();
};

#endif
``` 