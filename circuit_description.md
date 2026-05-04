# Circuit Description

This file describes the basic circuit connections for the Arduino Smart Home System.

## Arduino Board

The full version of this project is designed for an Arduino Mega 2560 or a compatible board.

The Arduino Mega 2560 is used because the system includes several sensors, a keypad, an LCD display, multiple servo motors, LEDs, and a fan module.

## Input Connections

| Component | Arduino Mega Pin | Purpose |
|---|---:|---|
| Room LDR Sensor | A0 | Measures surrounding light level |
| LM35 Temperature Sensor | A1 | Measures temperature |
| Solar Tracking LDR Sensor Left | A2 | Measures light from the left side |
| Solar Tracking LDR Sensor Right | A3 | Measures light from the right side |
| Motion Sensor | D2 | Detects movement near the garage |
| Keypad Row 1 | D22 | Password input |
| Keypad Row 2 | D23 | Password input |
| Keypad Row 3 | D24 | Password input |
| Keypad Row 4 | D25 | Password input |
| Keypad Column 1 | D26 | Password input |
| Keypad Column 2 | D27 | Password input |
| Keypad Column 3 | D28 | Password input |
| Keypad Column 4 | D29 | Password input |

## Output Connections

| Component | Arduino Mega Pin | Purpose |
|---|---:|---|
| Light LED | D5 | Automatic light control |
| Fan Module | D6 | Temperature-based fan control |
| Correct Password LED | D7 | Access granted indicator |
| Wrong Password LED | D8 | Access denied indicator |
| Door Servo | D9 | Password-protected door system |
| Garage Servo | D10 | Automatic garage door |
| Solar Tracking Servo | D11 | Solar panel direction adjustment |

## LCD Connections

| LCD Pin | Arduino Mega Pin | Purpose |
|---|---:|---|
| RS | D30 | LCD register select |
| E | D31 | LCD enable |
| D4 | D32 | LCD data |
| D5 | D33 | LCD data |
| D6 | D34 | LCD data |
| D7 | D35 | LCD data |

## System Behavior

The Arduino reads input signals from the keypad, temperature sensor, room LDR sensor, solar-tracking LDR sensors, and motion sensor.

Based on these input values, the Arduino controls output components such as servo motors, LEDs, LCD messages, a fan module, and the solar-tracking mechanism.

### Door System

When the correct password is entered, the door servo rotates to simulate opening the door. The LCD shows an access-granted message, and the correct-password LED turns on.

When the wrong password is entered, the door remains closed. The LCD shows an access-denied message, and the wrong-password LED turns on.

### Garage System

When motion is detected, the garage servo rotates to simulate opening the garage door. The garage closes again automatically after a defined time.

### Temperature Control

The LM35 temperature sensor provides an analog value. The Arduino converts this value into a temperature reading.

If the temperature is above the defined limit, the fan turns on automatically. When the temperature returns to a normal range, the fan turns off.

### Light Control

The room LDR sensor measures the surrounding brightness.

If the light level is below the defined limit, the LED light turns on automatically. If there is enough light, the LED light turns off.

### Solar Tracking Concept

Two LDR sensors compare light intensity from two directions.

If one side receives stronger light, the solar-tracking servo changes the panel angle step by step toward the stronger light source.

This simulates a simple solar-tracking concept for improving light exposure.

## Hardware Notes

- Use resistors with LEDs to protect them.
- Servo motors may need an external power supply if they require more current.
- The fan should be controlled through a transistor, relay, or motor driver module.
- The fan should not be powered directly from an Arduino digital pin.
- Connect all grounds together when using external power.
- The exact wiring can be adjusted depending on the available components.
