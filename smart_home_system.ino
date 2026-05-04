/*
  Arduino Smart Home System

  Features:
  - Password-protected door using keypad, LCD and servo motor
  - Correct/wrong password feedback using LEDs and LCD messages
  - Motion-based garage opening using motion sensor and servo motor
  - Temperature-based fan control using LM35 temperature sensor
  - LDR-based automatic light control
  - Light-dependent solar tracking concept using two LDR sensors and servo motor

  Recommended Board: Arduino Mega 2560
  Language: Embedded C/C++
*/

#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <string.h>

// ----- Pin Configuration -----

// Sensors
const int roomLdrPin = A0;
const int tempPin = A1;
const int leftSolarLdrPin = A2;
const int rightSolarLdrPin = A3;
const int motionPin = 2;

// Outputs
const int lightLedPin = 5;
const int fanPin = 6;
const int correctLedPin = 7;
const int wrongLedPin = 8;

// Servo pins
const int doorServoPin = 9;
const int garageServoPin = 10;
const int solarServoPin = 11;

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(30, 31, 32, 33, 34, 35);

// ----- Servo Positions -----
const int doorClosedAngle = 0;
const int doorOpenAngle = 90;

const int garageClosedAngle = 0;
const int garageOpenAngle = 90;

const int solarMinAngle = 20;
const int solarMaxAngle = 160;
const int solarCenterAngle = 90;

// ----- Timing Settings -----
const unsigned long doorOpenTime = 3000;
const unsigned long garageOpenTime = 3000;
const unsigned long garageCooldownTime = 5000;
const unsigned long sensorReadInterval = 500;
const unsigned long feedbackLedTime = 1500;
const unsigned long lcdMessageTime = 2000;

// ----- Threshold Values -----
const int lightThreshold = 500;
const float temperatureThreshold = 28.0;
const int solarDifferenceThreshold = 80;

// ----- Servo Objects -----
Servo doorMotor;
Servo garageMotor;
Servo solarMotor;

// ----- Keypad Configuration -----
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Arduino Mega keypad pins
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ----- Password Settings -----
const char correctPassword[] = "1234";
char enteredPassword[5];
byte passwordIndex = 0;
const byte passwordLength = 4;

// ----- System States -----
bool doorIsOpen = false;
bool garageIsOpen = false;
bool fanIsOn = false;
bool lightsAreOn = false;
bool correctLedIsOn = false;
bool wrongLedIsOn = false;

int solarAngle = solarCenterAngle;

// ----- Time Tracking -----
unsigned long doorOpenedAt = 0;
unsigned long garageOpenedAt = 0;
unsigned long lastGarageTrigger = 0;
unsigned long lastSensorRead = 0;
unsigned long correctLedStartedAt = 0;
unsigned long wrongLedStartedAt = 0;
unsigned long lcdMessageStartedAt = 0;

bool temporaryLcdMessageActive = false;

void setup() {
  pinMode(motionPin, INPUT);

  pinMode(lightLedPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(correctLedPin, OUTPUT);
  pinMode(wrongLedPin, OUTPUT);

  doorMotor.attach(doorServoPin);
  garageMotor.attach(garageServoPin);
  solarMotor.attach(solarServoPin);

  closeDoor();
  closeGarage();

  solarMotor.write(solarCenterAngle);

  turnOffFeedbackLeds();

  digitalWrite(lightLedPin, LOW);
  digitalWrite(fanPin, LOW);

  lastGarageTrigger = millis() - garageCooldownTime;

  lcd.begin(16, 2);
  showLcdMessage("Smart Home", "System Ready", true);

  Serial.begin(9600);
  Serial.println("Smart Home System Ready");
}

void loop() {
  handleDoorAccess();
  handleGarageDoor();
  handleAutoClose();
  handleSensors();
  handleFeedbackLeds();
  handleLcdDefaultScreen();
}

// ----- Door Access -----
void handleDoorAccess() {
  char key = keypad.getKey();

  if (!key) {
    return;
  }

  if (key == '*') {
    clearPassword();
    showLcdMessage("Password", "Cleared", true);
    Serial.println("Password cleared");
  }
  else if (key == '#') {
    checkPassword();
  }
  else if (isValidPasswordKey(key)) {
    addPasswordDigit(key);
  }
}

bool isValidPasswordKey(char key) {
  return key >= '0' && key <= '9';
}

void addPasswordDigit(char key) {
  if (passwordIndex < passwordLength) {
    enteredPassword[passwordIndex] = key;
    passwordIndex++;
    enteredPassword[passwordIndex] = '\0';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password");
    lcd.setCursor(0, 1);

    for (byte i = 0; i < passwordIndex; i++) {
      lcd.print("*");
    }

    temporaryLcdMessageActive = true;
    lcdMessageStartedAt = millis();

    Serial.print("Digit entered: ");
    Serial.println(passwordIndex);
  }
  else {
    showLcdMessage("Password Full", "Press # or *", true);
    Serial.println("Password full. Press # to submit or * to clear.");
  }
}

void checkPassword() {
  if (strcmp(enteredPassword, correctPassword) == 0) {
    Serial.println("Correct password - Door opened");
    showCorrectPasswordFeedback();
    showLcdMessage("Access Granted", "Door Opened", true);
    openDoor();
  }
  else {
    Serial.println("Wrong password");
    showWrongPasswordFeedback();
    showLcdMessage("Access Denied", "Wrong Password", true);
  }

  clearPassword();
}

void clearPassword() {
  passwordIndex = 0;
  enteredPassword[0] = '\0';
}

void openDoor() {
  doorMotor.write(doorOpenAngle);
  doorIsOpen = true;
  doorOpenedAt = millis();
}

void closeDoor() {
  doorMotor.write(doorClosedAngle);
  doorIsOpen = false;
}

// ----- Password Feedback LEDs -----
void showCorrectPasswordFeedback() {
  digitalWrite(correctLedPin, HIGH);
  digitalWrite(wrongLedPin, LOW);

  correctLedIsOn = true;
  wrongLedIsOn = false;

  correctLedStartedAt = millis();
}

void showWrongPasswordFeedback() {
  digitalWrite(wrongLedPin, HIGH);
  digitalWrite(correctLedPin, LOW);

  wrongLedIsOn = true;
  correctLedIsOn = false;

  wrongLedStartedAt = millis();
}

void handleFeedbackLeds() {
  unsigned long currentTime = millis();

  if (correctLedIsOn && currentTime - correctLedStartedAt >= feedbackLedTime) {
    digitalWrite(correctLedPin, LOW);
    correctLedIsOn = false;
  }

  if (wrongLedIsOn && currentTime - wrongLedStartedAt >= feedbackLedTime) {
    digitalWrite(wrongLedPin, LOW);
    wrongLedIsOn = false;
  }
}

void turnOffFeedbackLeds() {
  digitalWrite(correctLedPin, LOW);
  digitalWrite(wrongLedPin, LOW);

  correctLedIsOn = false;
  wrongLedIsOn = false;
}

// ----- Garage Door -----
void handleGarageDoor() {
  int motionState = digitalRead(motionPin);
  unsigned long currentTime = millis();

  bool cooldownFinished = currentTime - lastGarageTrigger >= garageCooldownTime;

  if (motionState == HIGH && !garageIsOpen && cooldownFinished) {
    Serial.println("Motion detected - Garage opened");
    showLcdMessage("Motion Detected", "Garage Opened", true);
    openGarage();
    lastGarageTrigger = currentTime;
  }
}

void openGarage() {
  garageMotor.write(garageOpenAngle);
  garageIsOpen = true;
  garageOpenedAt = millis();
}

void closeGarage() {
  garageMotor.write(garageClosedAngle);
  garageIsOpen = false;
}

// ----- Auto Close -----
void handleAutoClose() {
  unsigned long currentTime = millis();

  if (doorIsOpen && currentTime - doorOpenedAt >= doorOpenTime) {
    closeDoor();
    Serial.println("Door closed");
    showLcdMessage("Door", "Closed", true);
  }

  if (garageIsOpen && currentTime - garageOpenedAt >= garageOpenTime) {
    closeGarage();
    Serial.println("Garage closed");
    showLcdMessage("Garage", "Closed", true);
  }
}

// ----- Sensors -----
void handleSensors() {
  unsigned long currentTime = millis();

  if (currentTime - lastSensorRead >= sensorReadInterval) {
    lastSensorRead = currentTime;

    handleTemperatureControl();
    handleLightControl();
    handleSolarTracking();
  }
}

void handleTemperatureControl() {
  int sensorValue = analogRead(tempPin);

  // LM35 temperature sensor: 10 mV per degree Celsius
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = voltage * 100.0;

  if (temperatureC > temperatureThreshold && !fanIsOn) {
    digitalWrite(fanPin, HIGH);
    fanIsOn = true;

    Serial.print("Fan ON - Temperature: ");
    Serial.println(temperatureC);
  }
  else if (temperatureC <= temperatureThreshold && fanIsOn) {
    digitalWrite(fanPin, LOW);
    fanIsOn = false;

    Serial.print("Fan OFF - Temperature: ");
    Serial.println(temperatureC);
  }
}

void handleLightControl() {
  int lightValue = analogRead(roomLdrPin);

  if (lightValue < lightThreshold && !lightsAreOn) {
    digitalWrite(lightLedPin, HIGH);
    lightsAreOn = true;

    Serial.print("Lights ON - Light value: ");
    Serial.println(lightValue);
  }
  else if (lightValue >= lightThreshold && lightsAreOn) {
    digitalWrite(lightLedPin, LOW);
    lightsAreOn = false;

    Serial.print("Lights OFF - Light value: ");
    Serial.println(lightValue);
  }
}

// ----- Solar Tracking Concept -----
void handleSolarTracking() {
  int leftLightValue = analogRead(leftSolarLdrPin);
  int rightLightValue = analogRead(rightSolarLdrPin);

  int difference = leftLightValue - rightLightValue;

  if (abs(difference) < solarDifferenceThreshold) {
    return;
  }

  if (difference > 0 && solarAngle < solarMaxAngle) {
    solarAngle++;
  }
  else if (difference < 0 && solarAngle > solarMinAngle) {
    solarAngle--;
  }

  solarMotor.write(solarAngle);

  Serial.print("Solar angle: ");
  Serial.print(solarAngle);
  Serial.print(" | Left LDR: ");
  Serial.print(leftLightValue);
  Serial.print(" | Right LDR: ");
  Serial.println(rightLightValue);
}

// ----- LCD -----
void showLcdMessage(const char firstLine[], const char secondLine[], bool temporaryMessage) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(firstLine);

  lcd.setCursor(0, 1);
  lcd.print(secondLine);

  temporaryLcdMessageActive = temporaryMessage;
  lcdMessageStartedAt = millis();
}

void handleLcdDefaultScreen() {
  if (!temporaryLcdMessageActive) {
    return;
  }

  unsigned long currentTime = millis();

  if (currentTime - lcdMessageStartedAt >= lcdMessageTime) {
    temporaryLcdMessageActive = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp/Fan: ");
    lcd.print(fanIsOn ? "ON" : "OFF");

    lcd.setCursor(0, 1);
    lcd.print("Light: ");
    lcd.print(lightsAreOn ? "ON" : "OFF");
  }
}
