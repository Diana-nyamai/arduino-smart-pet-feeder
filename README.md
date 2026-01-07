# Arduino Smart Pet Feeder

An automated pet feeding system using an Arduino microcontroller to control a servo motor that opens and closes a food dispenser at predefined times.

## Project Overview

The Smart Cat Feeder uses an Arduino microcontroller to control a servo motor that opens and closes a food dispenser at predefined times. This project is ideal for pet owners who want to ensure their pets are fed on a consistent schedule, even when away from home.

## Core Features

- ⏰ **Scheduled Feeding** - Time-based feeding using Real-Time Clock (RTC)
- 🔧 **Servo-Controlled Dispenser** - Precise food portion control
- 💡 **Simple & Low-Cost** - Uses readily available components
- 🔋 **Power Efficient** - Can run on battery or AC adapter
- 📝 **Customizable Schedule** - Easy to program multiple feeding times
- 🎯 **Reliable Operation** - Set-and-forget automated feeding

## Hardware Requirements

### Core Components (Minimum)

- Arduino UNO R3 Board
- Servo motor (SG90 / MG90)
- RTC module (DS3231 or DS1302)
- Jumper wires (M-M, M-F)
- 830-point Breadboard
- External power supply (5-9V for servo motor)
- USB cable for programming

### Optional Components (For Enhanced Features)

- **LCD 1602 Display** - Show feeding schedule and status
- **Push Buttons (2-3)** - Manual feeding control and menu navigation
- **Active/Passive Buzzer** - Audible feeding alerts
- **LEDs (Red, Green, Yellow)** - Visual status indicators
- **HC-SR04 Ultrasonic Sensor** - Detect food level in container
- **220Ω Resistors** - For LED current limiting
- **10KΩ Resistors** - For button pull-down/pull-up

### Complete Arduino UNO R3 Starter Kit

This project is built using components from a comprehensive Arduino starter kit that includes:

- 300+ electronic components
- 15+ different sensors (motion, temperature, humidity, ultrasonic, etc.)
- Multiple display options (LCD, 7-segment, LED matrix)
- Various motors and drivers
- Complete resistor and capacitor sets
- See the [Component Inventory](docs/component-inventory.md) for the full list

## Software Requirements

- **Arduino IDE** (v1.8.x or higher) or **PlatformIO**
- **Required Libraries:**
  - `Servo.h` - Control servo motor
  - `RTClib.h` (by Adafruit) - Real-time clock functionality
  - `Wire.h` - I2C communication (built-in)
- **Optional Libraries (for enhanced features):**
  - `LiquidCrystal.h` or `LiquidCrystal_I2C.h` - LCD display
  - `EEPROM.h` - Save feeding schedule to memory

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/Diana-nyamai/arduino-smart-pet-feeder.git
cd arduino-smart-pet-feeder
```

### 2. Install Required Software

- Download and install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/)

### 3. Install Required Libraries

**Using Arduino IDE:**

- Go to: `Sketch` > `Include Library` > `Manage Libraries`
- Search for and install:
  - "Servo" (by Arduino)
  - "RTClib" (by Adafruit)

**Using PlatformIO:**

- Libraries are auto-installed from `platformio.ini`

### 4. Hardware Setup

- Connect components according to the [Setup Guide](docs/setup-guide.md)
- Use the wiring diagram for proper connections
- Ensure servo motor has adequate power supply

### 5. Upload Code

- Open `src/main.cpp` in your IDE
- Select your Arduino board: `Tools` > `Board` > `Arduino Uno`
- Select correct COM port: `Tools` > `Port`
- Click **Upload** button

### 6. Configure Feeding Times

- Modify feeding schedule in the code
- Set current time on RTC module
- Test manual feeding before deploying

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

- 📘 [Setup Guide](docs/setup-guide.md) - Detailed wiring and assembly instructions
- 🔮 [Future Improvements](docs/future-improvements.md) - Planned features and enhancements
- 📦 [Component Inventory](docs/component-inventory.md) - Complete kit component list

## Usage

1. **Power On**: Connect Arduino to power source
2. **Set Time**: RTC keeps time automatically (set once during initial setup)
3. **Feeding Schedule**: Pre-programmed feeding times activate servo motor
4. **Food Dispensing**: Servo rotates to open dispenser, then closes after set duration
5. **Monitoring**: Check serial monitor for feeding logs and debug info

## Troubleshooting

| Issue               | Possible Solution                                                          |
| ------------------- | -------------------------------------------------------------------------- |
| Servo not moving    | Check power supply, verify servo connections, test servo separately        |
| Wrong feeding times | Set RTC time correctly, check timezone settings                            |
| Food not dispensing | Adjust servo angle, check dispenser mechanism, ensure adequate food supply |
| Arduino resets      | Use external power for servo, add capacitor across servo power lines       |

For more help, see the [Setup Guide](docs/setup-guide.md).

## Contributing

Contributions are welcome! Here's how you can help:

1. 🍴 Fork the repository
2. 🌟 Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. 💾 Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. 📤 Push to the branch (`git push origin feature/AmazingFeature`)
5. 🔃 Open a Pull Request

**Ideas for Contributions:**

- Add LCD display support
- Implement manual feeding button
- Add food level detection
- Create mobile app integration
- Improve documentation

## License

This project is open source and available for educational and personal use.

## Author

**Diana Ndinda Nyamai**  
Integration Engineer | Embedded & IoT Enthusiast

## Acknowledgments

- Built as part of learning embedded systems and IoT development
- Inspired by the maker community and DIY pet care solutions
- Thanks to Arduino and Adafruit for excellent libraries and documentation
- Special thanks to the open-source hardware community

## Connect

- 💼 [LinkedIn](https://www.linkedin.com/in/diana-nyamai)
- 🐱 [GitHub](https://github.com/Diana-nyamai)
- 📧 Email: diana.nyamai@example.com

---

**Note:** This is an educational project. Always ensure proper safety measures when working with electronic components and pet feeding systems.

---

⭐ **If you find this project helpful, please give it a star!** ⭐
