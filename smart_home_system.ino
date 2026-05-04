/*
  Arduino Smart Home System

  Features:
  - Password-protected door using keypad and servo motor
  - Correct/wrong password feedback using LEDs
  - Motion-based garage opening using motion sensor and servo motor
  - Temperature-based fan control using LM35 temperature sensor
  - LDR-based automatic light control

  Board: Arduino Uno
  Language: Embedded C/C++
*/

#include <Keypad.h>
#include <Servo.h>
#include <string.h>
// ----- Pin Configuration -----
const int ldrPin = A0;
const int tempPin = A1;
const int motionPin = 2;

const int lightLedPin = 8;
const int fanPin = 9;
const int correctLedPin = A3;
const int wrongLedPin = A4;

const int doorServoPin = 10;
const int garageServoPin = 11;

// ----- Servo Positions -----
const int doorClosedAngle = 0;
const int doorOpenAngle = 90;

const int garageClosedAngle = 0;
const int garageOpenAngle = 90;

// ----- Timing Settings -----
const unsigned long doorOpenTime = 3000;
const unsigned long garageOpenTime = 3000;
const unsigned long garageCooldownTime = 5000;
const unsigned long sensorReadInterval = 500;
const unsigned long feedbackLedTime = 1500;

// ----- Threshold Values -----
const int lightThreshold = 500;
const float temperatureThreshold = 28.0;

// ----- Servo Objects -----
Servo doorMotor;
Servo garageMotor;

// ----- Keypad Configuration -----
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 12, 13, A2};

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

// ----- Time Tracking -----
unsigned long doorOpenedAt = 0;
unsigned long garageOpenedAt = 0;
unsigned long lastGarageTrigger = 0;
unsigned long lastSensorRead = 0;
unsigned long correctLedStartedAt = 0;
unsigned long wrongLedStartedAt = 0;

void setup() {
  pinMode(motionPin, INPUT);

  pinMode(lightLedPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(correctLedPin, OUTPUT);
  pinMode(wrongLedPin, OUTPUT);

  doorMotor.attach(doorServoPin);
  garageMotor.attach(garageServoPin);

  closeDoor();
  closeGarage();
  turnOffFeedbackLeds();

  digitalWrite(lightLedPin, LOW);
  digitalWrite(fanPin, LOW);

  lastGarageTrigger = millis() - garageCooldownTime;

  Serial.begin(9600);
  Serial.println("Smart Home System Ready");
}

void loop() {
  handleDoorAccess();
  handleGarageDoor();
  handleAutoClose();
  handleSensors();
  handleFeedbackLeds();
}

// ----- Door Access -----
void handleDoorAccess() {
  char key = keypad.getKey();

  if (!key) {
    return;
  }

  if (key == '*') {
    clearPassword();
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

    Serial.print("Digit entered: ");
    Serial.println(passwordIndex);
  } 
  else {
    Serial.println("Password full. Press # to submit or * to clear.");
  }
}

void checkPassword() {
  if (strcmp(enteredPassword, correctPassword) == 0) {
    Serial.println("Correct password - Door opened");
    showCorrectPasswordFeedback();
    openDoor();
  } 
  else {
    Serial.println("Wrong password");
    showWrongPasswordFeedback();
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
  }

  if (garageIsOpen && currentTime - garageOpenedAt >= garageOpenTime) {
    closeGarage();
    Serial.println("Garage closed");
  }
}

// ----- Sensors -----
void handleSensors() {
  unsigned long currentTime = millis();

  if (currentTime - lastSensorRead >= sensorReadInterval) {
    lastSensorRead = currentTime;

    handleTemperatureControl();
    handleLightControl();
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
  int lightValue = analogRead(ldrPin);

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
