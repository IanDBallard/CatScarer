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
├── Parts/                  # 3D printable enclosure parts
│   ├── Cat Scarer Body.3mf # Main enclosure body
│   └── Cat Scarer Lid.3mf  # Enclosure lid/cover
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

## 3D Printable Enclosure

### Available Parts

The project includes 3D printable enclosure parts for a complete, professional-looking cat deterrent system:

- **Cat Scarer Body.3mf** - Main enclosure housing for electronics
- **Cat Scarer Lid.3mf** - Removable lid for easy access to components

### Printing Specifications

#### **Recommended Settings:**
- **Printer**: Any FDM 3D printer (tested on Bambu Lab X1C)
- **Material**: PLA+ (recommended) or standard PLA
- **Layer Height**: 0.2mm (standard quality)
- **Infill**: 20-30% (adequate strength, reasonable print time)
- **Supports**: **Required** - Enable supports for overhanging features
- **Bed Temperature**: 60°C (PLA)
- **Hotend Temperature**: 210-220°C (PLA+)

#### **Alternative Materials:**
- **PETG**: More durable, higher temperature resistance
- **ABS**: Higher temperature resistance, requires enclosure
- **TPU**: Flexible, impact resistant (for outdoor use)

### Assembly Instructions

1. **Print both parts** using the recommended settings
2. **Remove supports** carefully using pliers or flush cutters
3. **Clean up** any stringing or remaining support material
4. **Test fit** the lid on the body before electronics installation
5. **Install electronics** into the body cavity
6. **Secure lid** to complete the assembly

### Enclosure Features

- **Compact design** - Fits all electronics components
- **Ventilation holes** - Proper airflow for fan operation
- **Cable management** - Organized routing for power and sensor cables
- **Mounting options** - Can be wall-mounted or placed on surface
- **Weather resistance** - Suitable for indoor/outdoor use (with appropriate material)

### Customization

The 3D models can be modified for:
- **Different fan sizes** - Adjust cavity dimensions
- **Additional sensors** - Add mounting points
- **Different mounting** - Modify base or mounting holes
- **Material optimization** - Adjust wall thickness for different materials

## Hardware Components

### Required Components

- **Arduino Nano** (ATmega328P) - Main controller
- **PIR Motion Sensor** - Detects cat movement
- **PWM Fan** - Physical deterrent (with P30N06LE MOSFET circuit)
- **Buzzer** - Audio deterrent (with 2N2222 transistor circuit)
- **RGB LED** - Status indicator (common cathode)
- **Current-limiting resistors** - 220Ω-330Ω for RGB LED protection

### Complete Component List

#### **Microcontrollers (Choose One)**
| MCU | Package | Voltage | Flash | RAM | Notes |
|-----|---------|---------|-------|-----|-------|
| **Arduino Nano** | DIP-28 | 5V | 32KB | 2KB | **Primary Target** |
| Arduino Uno | DIP-28 | 5V | 32KB | 2KB | Direct replacement |
| Arduino Pro Mini | SMD | 5V | 32KB | 2KB | Smaller footprint |
| ESP32 Dev Board | SMD | 3.3V | 4MB | 520KB | WiFi/Bluetooth |
| ESP8266 NodeMCU | SMD | 3.3V | 4MB | 80KB | WiFi enabled |
| STM32F103C8T6 | SMD | 3.3V | 64KB | 20KB | ARM Cortex-M3 |

#### **Power Supply Components**
| Component | Specification | Quantity | Notes |
|-----------|---------------|----------|-------|
| **12V Power Supply** | 12V, 2A+ | 1 | For fan and buzzer |
| **Buck Converter** | 12V→5V, 1A+ | 1 | LM2596 or MP2307 |
| **5V Regulator** | 7805 or AMS1117 | 1 | Backup 5V source |
| **Capacitors** | 100µF, 25V | 2 | Power filtering |
| **Capacitors** | 10µF, 16V | 2 | Decoupling |

#### **Transistors & MOSFETs**
| Component | Package | Rating | Quantity | Purpose |
|-----------|---------|--------|----------|---------|
| **P30N06LE** | TO-220 | 30A, 60V | 1 | Fan control |
| **2N2222** | TO-92 | 800mA, 40V | 1 | Buzzer control |
| **TIP120** | TO-220 | 5A, 60V | 1 | Fan control (alt) |
| **IRF530** | TO-220 | 14A, 100V | 1 | Fan control (alt) |

#### **Diodes**
| Component | Package | Rating | Quantity | Purpose |
|-----------|---------|--------|----------|---------|
| **1N4007** | DO-41 | 1A, 1000V | 2 | Flyback protection |
| **1N4004** | DO-41 | 1A, 400V | 2 | Flyback protection (alt) |
| **1N4001** | DO-41 | 1A, 50V | 2 | Flyback protection (alt) |

#### **Resistors**
| Value | Power | Quantity | Purpose |
|-------|-------|----------|---------|
| **220Ω** | 1/4W | 3 | RGB LED current limiting |
| **330Ω** | 1/4W | 3 | RGB LED current limiting (alt) |
| **1kΩ** | 1/4W | 1 | Buzzer base current limiting |
| **10kΩ** | 1/4W | 1 | MOSFET gate pull-down |
| **4.7kΩ** | 1/4W | 1 | MOSFET gate pull-down (alt) |

#### **Sensors & Actuators**
| Component | Specification | Quantity | Notes |
|-----------|---------------|----------|-------|
| **PIR Sensor** | HC-SR501 | 1 | Motion detection |
| **RGB LED** | Common Cathode | 1 | Status indicator |
| **PWM Fan** | 12V, 80-120mm | 1 | Physical deterrent |
| **Piezo Buzzer** | 5V or 12V | 1 | Audio deterrent |

#### **Connectors & Hardware**
| Component | Specification | Quantity | Purpose |
|-----------|---------------|----------|---------|
| **Breadboard** | 830 points | 1 | Prototyping |
| **Jumper Wires** | Male-Male | 20 | Connections |
| **Jumper Wires** | Male-Female | 10 | Sensor connections |
| **Power Jack** | 2.1mm DC | 1 | 12V input |
| **USB Cable** | Type B | 1 | Programming |

### MCU Compatibility Notes

#### **Arduino Nano (Primary)**
- **Voltage**: 5V operation
- **PWM Pins**: 3, 5, 6, 9, 10, 11
- **Digital Pins**: All pins available
- **Memory**: Sufficient for all features

#### **ESP32/ESP8266 Compatibility**
- **Voltage**: 3.3V operation (requires level shifting)
- **PWM**: Software PWM on any pin
- **WiFi**: Built-in connectivity for remote monitoring
- **Memory**: Abundant for advanced features
- **Pin Changes**: Update pin definitions in `src/main.cpp`

#### **STM32 Compatibility**
- **Voltage**: 3.3V operation
- **PWM**: Hardware PWM on specific pins
- **Performance**: Higher clock speed, more memory
- **Development**: Requires STM32duino framework

### Power Supply Considerations

#### **12V Power Supply Requirements**
- **Minimum Current**: 2A for reliable operation
- **Recommended**: 3A for headroom
- **Voltage Stability**: ±5% tolerance
- **Protection**: Overcurrent and short-circuit protection

#### **Buck Converter Selection**
- **Input**: 12V from power supply
- **Output**: 5V for Arduino and sensors
- **Current**: 1A minimum (Arduino + sensors)
- **Efficiency**: 85%+ for heat management
- **Popular Modules**: LM2596, MP2307, XL6009

#### **Power Distribution**
```
12V Power Supply
    ↓
Buck Converter (12V→5V)
    ↓
Arduino Nano (5V)
    ↓
PIR Sensor (5V)
    ↓
RGB LED (5V via resistors)
```

#### **Alternative Power Solutions**
- **USB Power**: 5V directly (fan needs separate 12V)
- **Battery**: 12V lead-acid or LiPo with buck converter
- **Solar**: 12V solar panel with charge controller

### Pin Connections

| Component | Pin | Description |
|-----------|-----|-------------|
| PIR Sensor | D2 | Motion detection input |
| Fan PWM | D9 | PWM fan speed control |
| Buzzer | D3 | Audio output control |
| RGB LED Red | D5 | Red LED control (PWM) |
| RGB LED Green | D6 | Green LED control (PWM) |
| RGB LED Blue | D8 | Blue LED control (Digital) |

## Features

### Motion Detection

- PIR sensor continuously monitors for movement
- **45-second warm-up period** to establish baseline readings
- Configurable sensitivity and detection range
- **Encapsulated warm-up logic** within PIRSensor class

### Deterrent Mechanisms

- **PWM Fan**: Variable speed control for physical deterrent
- **Buzzer**: Audio deterrent with transistor amplification and siren mode
- **RGB LED**: Visual status indication
  - **Blue flickering**: PIR sensor warming up
  - **Green solid**: Ready/Standby mode
  - **Red solid**: Active deterrent mode

### Behavior

- **Initialization**: 45-second PIR warm-up with blue LED flickering
- **Activation**: Triggers when motion is detected (after warm-up)
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

### PIR Sensor Configuration

Edit `src/PIRSensor.cpp` to customize warm-up time:

```cpp
// In constructor - change warm-up duration (default: 45 seconds)
_warmUpDuration(45000) // 45 seconds in milliseconds
```

### Pin Assignments

Modify pin definitions in `src/main.cpp`:

```cpp
const int PIR_PIN = 2;        // PIR sensor pin
const int FAN_PWM_PIN = 9;    // Fan PWM control pin
const int BUZZER_PIN = 3;     // Buzzer control pin
const int LED_RED_PIN = 5;    // RGB LED red pin
const int LED_GREEN_PIN = 6;  // RGB LED green pin
const int LED_BLUE_PIN = 8;   // RGB LED blue pin
```

## Hardware Circuit

### Fan Control Circuit (P30N06LE MOSFET)

```
Arduino D9 ──┬── 10kΩ Resistor ── GND
            │
            └── P30N06LE Gate
                    ↓
                P30N06LE Source ── GND
                    ↓
                P30N06LE Drain ── Fan (+)
                          ↓
                      Fan (-) ── GND
                          │
                      Flyback Diode (1N4007)
```

**Component Details:**
- **P30N06LE**: N-channel MOSFET (30A, 60V)
- **10kΩ Resistor**: Pull-down resistor for gate
- **Fan**: 12V or 5V PC fan (4-pin PWM fan supported)
- **1N4007 Diode**: Flyback protection diode (cathode to fan +, anode to fan -)

### Buzzer Circuit (2N2222 Transistor)

```
Arduino D3 ──┬── 1kΩ Resistor ── 2N2222 Base
            │
            └── 2N2222 Emitter ── GND
                    ↓
                2N2222 Collector ── Buzzer (+)
                          ↓
                      Buzzer (-) ── GND
                          │
                      Flyback Diode (1N4007)
```

**Component Details:**
- **2N2222**: NPN transistor for current amplification
- **1kΩ Resistor**: Base current limiting resistor
- **Buzzer**: 5V or 12V piezo buzzer
- **1N4007 Diode**: Flyback protection diode (cathode to buzzer +, anode to buzzer -)

### RGB LED Circuit (Common Cathode)

```
Arduino D5 ── 220Ω Resistor ── LED Red Anode
Arduino D6 ── 220Ω Resistor ── LED Green Anode  
Arduino D8 ── 220Ω Resistor ── LED Blue Anode
                    │
                LED Common Cathode ── GND
```

**Component Details:**
- **220Ω Resistors**: Current-limiting resistors (220Ω-330Ω acceptable)
- **RGB LED**: Common cathode type (longest pin = cathode)
- **Pin Configuration**: Red, Green, Blue anodes + Common cathode

### Complete Wiring Diagram

```
Arduino Nano
┌─────────────────────────────────────────────────────────┐
│                                                         │
│  D2 ────────────────── PIR Sensor OUT                   │
│                                                         │
│  D3 ── 1kΩ ── 2N2222 Base                              │
│             2N2222 Emitter ── GND                       │
│             2N2222 Collector ── Buzzer (+)              │
│                                    Buzzer (-) ── GND    │
│                                    │                    │
│                                    └─ 1N4007 Diode ─────┘
│                                                         │
│  D5 ── 220Ω ── RGB LED Red Anode                        │
│  D6 ── 220Ω ── RGB LED Green Anode                      │
│  D8 ── 220Ω ── RGB LED Blue Anode                       │
│                                    RGB LED Cathode ── GND│
│                                                         │
│  D9 ── 10kΩ ── P30N06LE Gate                            │
│              P30N06LE Source ── GND                     │
│              P30N06LE Drain ── Fan (+)                  │
│                                    Fan (-) ── GND       │
│                                    │                    │
│                                    └─ 1N4007 Diode ─────┘
│                                                         │
│  VIN ── 12V Power Supply (for fan)                      │
│  5V ── 5V Power Supply (for Arduino)                    │
│  GND ── Common Ground                                   │
└─────────────────────────────────────────────────────────┘
```

### Power Supply Requirements

- **Arduino Nano**: 5V via USB or VIN pin
- **Fan**: 12V (or 5V depending on fan type)
- **Buzzer**: 5V or 12V (check buzzer specifications)
- **RGB LED**: 5V (regulated by resistors)
- **PIR Sensor**: 5V

### Component Specifications

| Component | Specification | Notes |
|-----------|---------------|-------|
| P30N06LE | 30A, 60V N-MOSFET | TO-220 package |
| 2N2222 | 800mA, 40V NPN | TO-92 package |
| RGB LED | Common Cathode | 20mA per color |
| Resistors | 220Ω-330Ω | 1/4W or higher |
| Fan | 12V PWM | 4-pin connector supported |
| Buzzer | 5V/12V Piezo | Check voltage rating |
| 1N4007 | 1A, 1000V Diode | Flyback protection (2x) |

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

The project uses object-oriented design with encapsulated classes:

- `PIRSensor`: Motion detection interface with built-in warm-up logic
- `PWMFan`: Fan speed control
- `Buzzer`: Audio output control with siren mode
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
2. **PIR not detecting**: Verify wiring and wait for 45-second warm-up
3. **Fan not spinning**: Check MOSFET circuit and PWM pin
4. **Buzzer not working**: Verify transistor circuit and pin connections
5. **LED dim or wrong colors**: Check resistor values (should be 220Ω-330Ω)

### LED Status Indicators

- **Blue flickering**: PIR sensor warming up (45 seconds)
- **Green solid**: Ready for motion detection
- **Red solid**: Motion detected, deterrents active

### Debug Output

Enable serial monitoring to see debug messages:

```bash
pio device monitor
```

Expected output:

```text
Cat Scare Device Starting...
Testing LED colors...
Testing RED pin (D5)...
Testing GREEN pin (D6)...
Testing BLUE pin (D8)...
ALL LEDS OFF
PIR sensor warming up...
Device ready.
Motion detected! Activating deterrent...
Setting LED to RED (255,0,0)
Deactivating deterrent...
Setting LED to GREEN (0,255,0)
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

[Add your license here] 