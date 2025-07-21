# Library Directory

This directory contains custom libraries for your Arduino project.

## Usage

- Place custom library folders here
- Each library should have its own subdirectory
- PlatformIO will automatically include libraries from this directory

## Structure

```
lib/
├── MyCustomLibrary/
│   ├── src/
│   │   └── MyCustomLibrary.cpp
│   ├── include/
│   │   └── MyCustomLibrary.h
│   └── library.json
└── AnotherLibrary/
    └── ...
```

## Example Library

```cpp
// MyCustomLibrary.h
#ifndef MY_CUSTOM_LIBRARY_H
#define MY_CUSTOM_LIBRARY_H

class MyCustomLibrary {
  public:
    void begin();
    void doSomething();
};

#endif
``` 