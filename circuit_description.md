# Circuit Description

This file describes the basic circuit connections for the Arduino Smart Home System.

## Arduino Board

The project is designed for an Arduino Uno or a compatible Arduino board.

## Input Connections

| Component | Arduino Pin | Purpose |
|---|---:|---|
| LDR Sensor | A0 | Measures surrounding light level |
| LM35 Temperature Sensor | A1 | Measures temperature |
| Motion Sensor | D2 | Detects movement near the garage |
| Keypad Row 1 | D3 | Password input |
| Keypad Row 2 | D4 | Password input |
| Keypad Row 3 | D5 | Password input |
| Keypad Row 4 | D6 | Password input |
| Keypad Column 1 | D7 | Password input |
| Keypad Column 2 | D12 | Password input |
| Keypad Column 3 | D13 | Password input |
| Keypad Column 4 | A2 | Password input |

## Output Connections

| Component | Arduino Pin | Purpose |
|---|---:|---|
| Light LED | D8 | Automatic light control |
| Fan Module | D9 | Temperature-based fan control |
| Door Servo | D10 | Password-protected door system |
| Garage Servo | D11 | Automatic garage door |
| Correct Password LED | A3 | Access granted indicator |
| Wrong Password LED | A4 | Access denied indicator |

## System Behavior

The Arduino reads the input signals from the sensors and keypad. Based on these values, it controls the output components.

### Door System

When the correct password is entered, the door servo rotates to simulate opening the door. A green LED can be used to show that access is granted.

When the wrong password is entered, the door remains closed and a red LED can be used to show that access is denied.

### Garage System

When motion is detected, the garage servo rotates to simulate opening the garage door.

### Temperature Control

The LM35 temperature sensor provides an analog value. The Arduino converts this value into a temperature reading.

If the temperature is above the defined limit, the fan turns on automatically.

### Light Control

The LDR sensor measures the surrounding brightness.

If the light level is below the defined limit, the LED light turns on automatically.

## Notes

- Use resistors with LEDs to protect them.
- Servo motors may need an external power supply if they require more current.
- Connect all grounds together when using external power.
- The exact wiring can be adjusted depending on the available components.
