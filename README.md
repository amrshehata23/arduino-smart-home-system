# Arduino Smart Home System

## Overview
This project is a smart home automation system developed using an Arduino Uno, sensors, motors, LEDs, a fan and a keypad.

The system combines several home automation functions, including password-based door access, automatic garage opening, temperature-based fan control and light control using an LDR sensor.

The goal of this project was to apply embedded systems and mechatronics concepts by connecting hardware and software components in one complete system.

## Main Features

### 1. Password-Protected Door System
- A keypad is used to enter a password.
- If the correct password is entered, the door opens automatically using a motor.
- LEDs indicate the access status, for example correct or wrong password.
- This simulates a basic smart access control system.

### 2. Automatic Garage Door
- A motion sensor detects movement near the garage.
- When motion is detected, the garage door opens automatically using a motor.
- This simulates an automatic garage system for vehicles or people.

### 3. Temperature-Based Fan Control
- A temperature sensor measures the indoor temperature.
- If the temperature becomes too high, the fan turns on automatically.
- When the temperature returns to a normal range, the fan can be turned off again.
- This simulates basic automatic climate control inside a house.

### 4. Automatic Light Control Using LDR
- An LDR sensor detects the surrounding light level.
- If the environment becomes dark, LEDs turn on automatically.
- If there is enough light, the LEDs turn off.
- This simulates automatic lighting based on day and night conditions.

## Components Used
- Arduino Uno
- Temperature sensor
- LDR light sensor
- Motion sensor
- Keypad
- DC motor / servo motor
- LEDs
- Fan
- Resistors
- Breadboard
- Jumper wires

## Technologies Used
- Arduino Uno
- Arduino IDE
- Embedded C/C++
- Sensor Integration
- Motor Control
- Basic Electronics
- Embedded Systems Concepts

## System Logic
The Arduino Uno reads input signals from the keypad, temperature sensor, LDR sensor and motion sensor.  
Based on these inputs, the Arduino controls different output components such as motors, LEDs and the fan.

### Example Logic
- If the correct password is entered, the door motor is activated.
- If motion is detected, the garage motor opens the garage door.
- If the temperature is higher than the defined limit, the fan turns on.
- If the light level is low, the LEDs turn on automatically.

## Project Purpose
The purpose of this project was to apply mechatronics and embedded systems knowledge in a practical smart home application.

The project combines:
- Programming
- Electronics
- Sensors
- Motors
- Automation logic
- Hardware and software integration

## What I Learned
- Programming an Arduino Uno using Embedded C/C++
- Reading data from different sensors
- Controlling motors, LEDs and a fan
- Using a keypad for password input
- Building basic automation logic
- Connecting hardware and software components
- Testing and troubleshooting an embedded system
- Understanding basic smart home automation concepts

## Possible Applications
- Smart home access control
- Automatic garage systems
- Temperature-based fan control
- Automatic light control
- Basic home automation learning projects

## Future Improvements
- Add a circuit diagram
- Add real project pictures
- Add full Arduino source code
- Add LCD display for system status
- Improve password security
- Add Bluetooth or Wi-Fi control
- Add mobile app control
- Add data monitoring for temperature and light levels

## Project Status
This project was developed as an academic embedded systems / mechatronics project.
