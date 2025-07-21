# CatScarer

An Arduino Nano-based cat deterrent system using PlatformIO for development.

## Project Structure

```
CatScarer/
├── src/              # Main source code
│   └── main.cpp      # Arduino sketch
├── include/          # Header files
├── lib/              # Custom libraries
├── test/             # Unit tests
├── platformio.ini    # PlatformIO configuration
└── README.md         # This file
```

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

2. Initialize the project:
   ```bash
   pio init
   ```

3. Install dependencies:
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

Upload to other boards:
```bash
pio run -e uno -t upload
pio run -e esp32dev -t upload
```

### Monitoring

Monitor serial output:
```bash
pio device monitor
```

### Testing

Run all tests:
```bash
pio test
```

Run tests for specific environment:
```bash
pio test -e uno
```

## Supported Boards

- **Arduino Nano** (Primary target)
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

### Project Configuration

Edit `platformio.ini` to customize:
- Board settings
- Build flags
- Upload settings
- Monitor configuration

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

[Add your license here] 