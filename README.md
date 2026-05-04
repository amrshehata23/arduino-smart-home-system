# Arduino Smart Home System

This project is a physical Arduino-based smart home automation prototype. It combines sensors, LCD displays, servo motors, LEDs, a fan, a keypad, and embedded control logic inside a small smart-home model.

The system demonstrates basic embedded systems and mechatronics concepts by connecting hardware and software components in one complete automation project.

## Main Features

### Password-Protected Door System

- A keypad is used to enter a password
- If the correct password is entered, the door opens using a servo motor
- LCD display shows system messages such as password input and access status
- LEDs indicate correct or wrong access status
- This simulates a basic smart access control system

### Automatic Garage Door

- Motion/IR sensors are used to detect movement near the garage
- When movement is detected, the garage door opens automatically using a servo motor
- This simulates a simple automatic garage system

### Temperature-Based Fan Control

- A temperature sensor measures the surrounding temperature
- If the temperature is higher than the defined limit, the fan turns on automatically
- When the temperature returns to a normal range, the fan turns off
- This simulates basic automatic climate control

### Automatic Light Control

- An LDR light sensor measures the surrounding light level
- If the environment becomes dark, LEDs turn on automatically
- If there is enough light, LEDs turn off
- This simulates automatic day/night lighting control

### Light-Dependent Solar Tracking Concept

- Light sensors are used to detect the direction of stronger light
- A motorized mechanism changes the panel direction based on light conditions
- This simulates a simple solar-tracking concept for improving light exposure

## Project Demonstration

This project was implemented as a real physical prototype. The model includes a keypad access system, LCD status displays, automatic lighting, temperature-based fan control, servo-controlled doors, internal wiring, and a light-dependent solar-tracking mechanism.

### Final Smart Home Model

![Final Smart Home Model](images/final_model_front.jpg)

### Internal Wiring and Components

![Internal Wiring](images/internal_wiring.jpg)

### Solar Tracking Mechanism

![Solar Tracking Mechanism](images/solar_tracking_mechanism.jpg)

## Technologies Used

- Arduino Uno
- Arduino IDE
- Embedded C/C++
- Sensor integration
- Servo motor control
- LCD display control
- Basic electronics
- Embedded systems concepts

## Required Arduino Libraries

- Keypad
- Servo

## Components Used

- Arduino Uno
- LM35 temperature sensor
- LDR light sensor
- IR/motion sensors
- Keypad
- LCD displays
- Servo motors
- LEDs
- Fan module
- Resistors
- Breadboard
- Jumper wires
- External power supply

## System Logic

The Arduino reads input signals from the keypad, temperature sensor, LDR sensor, and motion/IR sensors.

Based on these inputs, the Arduino controls output components such as servo motors, LEDs, LCD displays, a fan, and the solar-tracking mechanism.

Example logic:

- If the correct password is entered, the door servo opens
- If motion is detected, the garage servo opens
- If the temperature is above the limit, the fan turns on
- If the light level is low, the LED lighting turns on
- If stronger light is detected from one side, the panel mechanism changes direction

## Project Demonstration

This project was implemented as a real physical prototype. The model includes a keypad access system, LCD status displays, automatic lighting, temperature-based fan control, servo-controlled doors, internal wiring, and a light-dependent solar-tracking mechanism.

### Final Smart Home Model

![Final Smart Home Model](images/final_model_front.jpg)

### Internal Wiring and Components

![Internal Wiring](images/internal_wiring.jpg)

### Solar Tracking Mechanism

![Solar Tracking Mechanism](images/solar_tracking_mechanism.jpg)

## Circuit Overview

```text
                  +----------------------+
                  |      Arduino Uno     |
                  |                      |
 LDR Sensor ------| A0                   |
 LM35 Sensor -----| A1                   |
 Motion Sensor ---| D2                   |
                  |                      |
 Keypad Rows -----| D3, D4, D5, D6       |
 Keypad Columns --| D7, D12, D13, A2     |
                  |                      |
 Light LED -------| D8                   |
 Fan Module ------| D9                   |
 Door Servo ------| D10                  |
 Garage Servo ----| D11                  |
 Correct LED -----| A3                   |
 Wrong LED -------| A4                   |
                  +----------------------+
Project Structure
arduino-smart-home-system/
│
├── smart_home_system.ino
├── README.md
├── components.md
├── circuit_description.md
├── images/
│   ├── final_model_front.jpg
│   ├── internal_wiring.jpg
│   └── solar_tracking_mechanism.jpg
└── .gitignore

How to Run

Open smart_home_system.ino in the Arduino IDE
Install the required Arduino libraries:
Keypad
Servo
Connect the components according to the circuit description
Select the correct board, for example Arduino Uno
Select the correct COM port
Upload the code to the Arduino board
Test the keypad, LCD displays, sensors, servo motors, LEDs, fan, and light-dependent panel mechanism

Hardware Notes

Use resistors with LEDs to protect them.
Servo motors may need an external power supply if they require more current.
The fan should be controlled through a transistor, relay, or motor driver module.
The fan should not be powered directly from an Arduino digital pin.
Connect all grounds together when using external power.
The physical model was built as a prototype, so the wiring and mechanical structure can be improved in future versions.

Skills Demonstrated

Embedded C/C++ programming
Digital and analog input handling
Sensor integration
Keypad input handling
LCD display output
Servo motor control
Basic automation logic
Hardware and software integration
Testing and troubleshooting of an embedded system
Building a physical mechatronic prototype

What I Learned

Programming an Arduino Uno using Embedded C/C++
Reading values from analog and digital sensors
Controlling LCD displays, LEDs, a fan, and servo motors
Using a keypad for password input
Building simple automation logic
Connecting hardware and software in a mechatronic system
Testing a physical prototype and improving the system step by step

Future Improvements

Improve cable management and internal wiring structure
Improve password handling and security logic
Add Bluetooth or Wi-Fi control
Add temperature and light data monitoring
Add a mobile or web dashboard for system status
