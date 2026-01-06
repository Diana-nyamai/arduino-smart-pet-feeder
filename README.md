# Arduino Smart Pet Feeder

An automated pet feeding system using an Arduino microcontroller to control a servo motor that opens and closes a food dispenser at predefined times.

## Project Overview

The Smart Cat Feeder uses an Arduino microcontroller to control a servo motor that opens and closes a food dispenser at predefined times. This project is ideal for pet owners who want to ensure their pets are fed on a consistent schedule, even when away from home.

## Core Features

- Time-based feeding using Real-Time Clock (RTC)
- Servo-controlled food dispensing mechanism
- Simple, low-cost hardware components

## Hardware Requirements

- Arduino Uno (or compatible board)
- Servo motor (SG90 / MG90)
- RTC module (DS3231 recommended)
- Jumper wires
- Breadboard
- External power supply (recommended for servo motor)

## Software Requirements

- Arduino IDE
- Required Libraries:
  - Servo
  - RTClib (by Adafruit)

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/Diana-nyamai/arduino-smart-pet-feeder.git
   cd arduino-smart-pet-feeder
   ```

2. Open `src/main.cpp` in Arduino IDE or PlatformIO

3. Install required libraries:

   - In Arduino IDE: Sketch > Include Library > Manage Libraries
   - Search for and install "Servo" and "RTClib"

4. Connect hardware components according to the wiring diagram (see docs/setup-guide.md)

5. Upload code to your Arduino board

6. Configure feeding times in the code as needed

## Project Structure

```
arduino-smart-pet-feeder/
├── src/              # Main source code
├── include/          # Header files
├── lib/              # Custom libraries
├── test/             # Test files
├── docs/             # Documentation
└── platformio.ini    # PlatformIO configuration
```


## Documentation

For detailed setup instructions and troubleshooting, see the [Setup Guide](docs/setup-guide.md).

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

## License

This project is open source and available for educational and personal use.

## Author

**Diana Ndinda Nyamai**  
Integration Engineer | Embedded & IoT Enthusiast

## Acknowledgments

This project is built as part of learning embedded systems and IoT development

---

**Note:** This is an educational project. Always ensure proper safety measures when working with electronic components and pet feeding systems.
