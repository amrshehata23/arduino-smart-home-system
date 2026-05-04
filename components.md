# Components Used

This file lists the main hardware components used in the Arduino Smart Home System.

## Main Controller

### Arduino Mega 2560

The Arduino Mega 2560 is used as the main microcontroller. It reads input signals from the sensors and keypad, then controls output components such as LEDs, LCD display, servo motors, and the fan.

The Arduino Mega 2560 is suitable for the full version of this project because it provides more digital and analog pins than an Arduino Uno.

## Sensors

### LM35 Temperature Sensor

Used to measure the surrounding temperature. The measured value is used to control the fan automatically.

### Room LDR Light Sensor

Used to detect the surrounding light level. If the room is dark, the light turns on automatically.

### Solar Tracking LDR Sensors

Two LDR sensors are used to compare light intensity from two directions. Based on the difference between the two readings, the solar panel mechanism changes direction using a servo motor.

### Motion Sensor

Used to detect movement near the garage door. When motion is detected, the garage door opens automatically.

## Input Components

### 4x4 Keypad

Used to enter a password for the door access system. The Arduino checks the entered password and controls the door servo based on the result.

## Output Components

### LCD Display

Used to show system messages such as:

- system ready status
- password input
- access granted
- access denied
- door status
- garage status
- fan status
- light status

### Servo Motors

Used to simulate mechanical movement in the system:

- main door opening and closing
- garage door opening and closing
- solar panel direction adjustment

### LEDs

Used to indicate system status, such as:

- correct password
- wrong password
- automatic lighting

### Fan Module

Used to simulate automatic ventilation or cooling when the temperature is above the defined limit.

## Additional Components

- Resistors
- Breadboard
- Jumper wires
- External power supply
- Transistor, relay, or motor driver module for fan control

## Hardware Notes

- LEDs should be used with suitable resistors.
- Servo motors may need an external power supply if they require more current.
- The fan should not be powered directly from an Arduino digital pin.
- The fan should be controlled through a transistor, relay, or motor driver module.
- When using external power, all grounds should be connected together.
