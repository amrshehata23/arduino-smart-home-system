# Arduino Smart Home System

This project is an Arduino-based smart home automation system. It combines sensors, actuators, LEDs, a fan, a keypad, and simple embedded control logic.

The system demonstrates basic embedded systems and mechatronics concepts by connecting hardware and software components in one complete automation project.

## Main Features

### Password-Protected Door System

- A keypad is used to enter a password
- If the correct password is entered, the door opens using a servo motor
- LEDs indicate correct or wrong access status
- This simulates a basic smart access control system

### Automatic Garage Door

- A motion sensor detects movement near the garage
- When motion is detected, the garage door opens automatically using a servo motor
- This simulates a simple automatic garage system

### Temperature-Based Fan Control

- A temperature sensor measures the surrounding temperature
- If the temperature is higher than the defined limit, the fan turns on automatically
- When the temperature returns to a normal range, the fan turns off
- This simulates basic automatic climate control

### Automatic Light Control

- An LDR sensor measures the surrounding light level
- If the environment becomes dark, LEDs turn on automatically
- If there is enough light, LEDs turn off
- This simulates automatic day/night lighting control

## Technologies Used

- Arduino Uno
- Arduino IDE
- Embedded C/C++
- Sensor integration
- Motor control
- Basic electronics
- Embedded systems concepts

## Components Used

- Arduino Uno
- LM35 temperature sensor
- LDR light sensor
- Motion sensor
- Keypad
- Servo motors
- LEDs
- Fan module
- Resistors
- Breadboard
- Jumper wires

## System Logic

The Arduino reads input signals from the keypad, temperature sensor, LDR sensor, and motion sensor.

Based on these inputs, the Arduino controls output components such as servo motors, LEDs, and a fan.

Example logic:

- If the correct password is entered, the door servo opens
- If motion is detected, the garage servo opens
- If the temperature is above the limit, the fan turns on
- If the light level is low, the LED light turns on

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
## Project Structure

arduino-smart-home-system/
│
├── smart_home_system.ino
├── README.md
├── components.md
├── circuit_description.md
└── .gitignore

How to Run
Open smart_home_system.ino in the Arduino IDE
Connect the components according to the circuit description
Select the correct board, for example Arduino Uno
Select the correct COM port
Upload the code to the Arduino board
Test the keypad, sensors, motors, LEDs, and fan
Skills Demonstrated
Embedded C/C++ programming
Digital and analog input handling
Sensor integration
Servo motor control
Basic automation logic
Hardware and software integration
Testing and troubleshooting of an embedded system

What I Learned
Programming an Arduino Uno using Embedded C/C++
Reading values from analog and digital sensors
Controlling LEDs, a fan, and servo motors
Using a keypad for password input
Building simple automation logic
Connecting hardware and software in a mechatronic system

Future Improvements
Add LCD display for system status
Improve password handling
Add Bluetooth or Wi-Fi control
Add temperature and light data monitoring
