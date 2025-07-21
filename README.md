# CatScarer

An Arduino Nano-based cat deterrent system using PlatformIO for development. This device uses a PIR motion sensor to detect cats and activates deterrent mechanisms including a PWM fan, buzzer, and RGB LED indicators.

## Project Structure

```text
CatScarer/
├── src/                    # Main source code
│   ├── main.cpp           # Main Arduino sketch (CatScareDevice.ino)
│   ├── PIRSensor.h        # PIR motion sensor class header
│   ├── PIRSensor.cpp      # PIR motion sensor class implementation
│   ├── PWMFan.h           # PWM fan control class header
│   ├── PWMFan.cpp         # PWM fan control class implementation
│   ├── Buzzer.h           # Buzzer control class header
│   ├── Buzzer.cpp         # Buzzer control class implementation
│   ├── RGBLED.h           # RGB LED control class header
│   └── RGBLED.cpp         # RGB LED control class implementation
├── include/               # Additional header files
├── lib/                   # Custom libraries
├── test/                  # Unit tests
├── .pio/                  # PlatformIO build artifacts
│   └── build/
│       └── nano/          # Arduino Nano build output
│           ├── firmware.hex    # Compiled firmware ready for upload
│           ├── firmware.elf    # Debug information
│           └── ...             # Other build files
├── platformio.ini         # PlatformIO configuration
├── .gitignore             # Git ignore rules
└── README.md              # This file
```

## Hardware Components

### Required Components

- **Arduino Nano** (ATmega328P) - Main controller
- **PIR Motion Sensor** - Detects cat movement
- **PWM Fan** - Physical deterrent (with TIP120 transistor circuit)
- **Buzzer** - Audio deterrent (with 2N2222 transistor circuit)
- **RGB LED** - Status indicator
- **Current-limiting resistors** - For RGB LED protection

### Pin Connections

| Component | Pin | Description |
|-----------|-----|-------------|
| PIR Sensor | D2 | Motion detection input |
| Fan PWM | D9 | PWM fan speed control |
| Buzzer | D3 | Audio output control |
| RGB LED Red | D5 | Red LED control (PWM) |
| RGB LED Green | D6 | Green LED control (PWM) |
| RGB LED Blue | D10 | Blue LED control (PWM) |

## Features

### Motion Detection

- PIR sensor continuously monitors for movement
- Configurable sensitivity and detection range

### Deterrent Mechanisms

- **PWM Fan**: Variable speed control for physical deterrent
- **Buzzer**: Audio deterrent with transistor amplification
- **RGB LED**: Visual status indication
  - Green: Ready/Standby mode
  - Red: Active deterrent mode

### Behavior

- **Activation**: Triggers when motion is detected
- **Duration**: Configurable activation time (default: 5 seconds)
- **Auto-reset**: Returns to standby after activation period
- **Continuous monitoring**: Refreshes timer if motion continues

## Setup

### Prerequisites

1. Install [PlatformIO Core](https://platformio.org/install/cli)
2. Install [Git](https://git-scm.com/)

### Installation

1. Clone this repository:

   ```bash
   git clone <your-repo-url>
   cd CatScarer
   ```

2. Install dependencies:

   ```bash
   pio lib install
   ```

## Usage

### Building

Build for Arduino Nano (default):

```bash
pio run
```

Build for Arduino Nano (explicit):

```bash
pio run -e nano
```

Build for other boards:

```bash
pio run -e uno
pio run -e esp32dev
```

### Uploading

Upload to Arduino Nano (default):

```bash
pio run -t upload
```

Upload to Arduino Nano (explicit):

```bash
pio run -e nano -t upload
```

### Monitoring

Monitor serial output for debugging:

```bash
pio device monitor
```

### Testing

Run all tests:

```bash
pio test
```

## Configuration

### Behavior Parameters

Edit `src/main.cpp` to customize:

```cpp
// Device behavior parameters
const unsigned long ACTIVATION_DURATION_MS = 5000; // Activation duration in milliseconds
const int FAN_SPEED_ACTIVATED = 255; // Fan speed when activated (0-255)
```

### Pin Assignments

Modify pin definitions in `src/main.cpp`:

```cpp
const int PIR_PIN = 2;        // PIR sensor pin
const int FAN_PWM_PIN = 9;    // Fan PWM control pin
const int BUZZER_PIN = 3;     // Buzzer control pin
const int LED_RED_PIN = 5;    // RGB LED red pin
const int LED_GREEN_PIN = 6;  // RGB LED green pin
const int LED_BLUE_PIN = 10;  // RGB LED blue pin
```

## Supported Boards

- **Arduino Nano** (Primary target - ATmega328P)
- Arduino Uno
- ESP32 Dev Board
- ESP8266 NodeMCU

## Development

### Adding Libraries

Add libraries to `platformio.ini`:

```ini
lib_deps = 
    library_name
    another_library
```

Or install via command line:

```bash
pio lib install "library_name"
```

### Custom Classes

The project uses object-oriented design with custom classes:

- `PIRSensor`: Motion detection interface
- `PWMFan`: Fan speed control
- `Buzzer`: Audio output control
- `RGBLED`: Color LED control

### Project Configuration

Edit `platformio.ini` to customize:

- Board settings
- Build flags
- Upload settings
- Monitor configuration

## Troubleshooting

### Common Issues

1. **Upload fails**: Check USB connection and COM port
2. **PIR not detecting**: Verify wiring and power supply
3. **Fan not spinning**: Check transistor circuit and PWM pin
4. **Buzzer not working**: Verify transistor circuit and pin connections

### Debug Output

Enable serial monitoring to see debug messages:

```bash
pio device monitor
```

Expected output:

```text
Cat Scare Device Starting...
Device ready.
Motion detected! Activating deterrent...
Deactivating deterrent...
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

[Add your license here] 