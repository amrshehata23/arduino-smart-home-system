# Components Used

This file lists the main hardware components used in the Arduino Smart Home System.

## Main Controller

### Arduino Uno

The Arduino Uno is used as the main microcontroller. It reads sensor inputs and controls output components such as LEDs, servo motors, and the fan.

## Sensors

### LM35 Temperature Sensor

Used to measure the surrounding temperature. The measured value is used to control the fan automatically.

### LDR Light Sensor

Used to detect the surrounding light level. If the room is dark, the light turns on automatically.

### Motion Sensor

Used to detect movement near the garage door. When motion is detected, the garage door opens automatically.

## Input Component

### Keypad

Used to enter a password for the door access system. The Arduino checks the entered password and controls the door servo based on the result.

## Output Components

### Servo Motors

Used to simulate the opening and closing of the main door and the garage door.

### LEDs

Used to indicate system status, such as correct password, wrong password, and automatic lighting.

### Fan Module

Used to simulate automatic ventilation or cooling when the temperature is above the defined limit.

## Additional Components

- Resistors
- Breadboard
- Jumper wires
- Power supply
