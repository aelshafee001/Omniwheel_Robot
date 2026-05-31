#include <SoftwareSerial.h>

/*
  4-Omni / Mecanum Wheel Bluetooth Control
  Board: Arduino UNO
  Bluetooth module: HC-05/HC-06

  Bluetooth wiring:
  BT TX  -> Arduino D2  (SoftwareSerial RX)
  BT RX  -> Arduino D4  (SoftwareSerial TX) through voltage divider is recommended
  BT VCC -> 5V
  BT GND -> GND

  Commands from Bluetooth terminal:
  F = Forward
  B = Backward
  L = Move Left / Strafe Left
  R = Move Right / Strafe Right
  Q = Rotate Left / Counter-clockwise
  E = Rotate Right / Clockwise
  G = Forward-Left diagonal
  I = Forward-Right diagonal
  H = Backward-Left diagonal
  J = Backward-Right diagonal
  S = Stop
  0..9 = Speed level, 0 stop, 9 max
  + = Increase speed
  - = Decrease speed
*/

#include <SoftwareSerial.h>
SoftwareSerial BT(2, 4); // RX, TX

// --------- Motor pin mapping ---------
// Each motor uses: EN(PWM), IN1, IN2
// Front Left (FL)
const int EN_FL  = 5;   // PWM
const int IN1_FL = 6;
const int IN2_FL = 7;

// Front Right (FR)
const int EN_FR  = 10;  // PWM
const int IN1_FR = 8;
const int IN2_FR = 9;

// Rear Left (RL)
const int EN_RL  = 11;  // PWM
const int IN1_RL = 12;
const int IN2_RL = 13;

// Rear Right (RR)
const int EN_RR  = 3;   // PWM
const int IN1_RR = A0;
const int IN2_RR = A1;

// --------- Motor calibration ---------
// If one motor rotates opposite to the required direction, change its value from 1 to -1.
const int INV_FL = 1;
const int INV_FR = 1;
const int INV_RL = 1;
const int INV_RR = 1;

// Base speed: 0 to 255
int baseSpeed = 160;
const int MIN_SPEED = 70;
const int MAX_SPEED = 255;
const int SPEED_STEP = 20;

char lastCommand = 'S';

void setup() {
  pinMode(EN_FL, OUTPUT); pinMode(IN1_FL, OUTPUT); pinMode(IN2_FL, OUTPUT);
  pinMode(EN_FR, OUTPUT); pinMode(IN1_FR, OUTPUT); pinMode(IN2_FR, OUTPUT);
  pinMode(EN_RL, OUTPUT); pinMode(IN1_RL, OUTPUT); pinMode(IN2_RL, OUTPUT);
  pinMode(EN_RR, OUTPUT); pinMode(IN1_RR, OUTPUT); pinMode(IN2_RR, OUTPUT);

  stopRobot();

  Serial.begin(9600);
  BT.begin(9600);

  Serial.println("Omni Bluetooth Robot Ready");
  Serial.println("Commands: F B L R Q E G I H J S, 0..9, +, -");
  BT.println("Omni Bluetooth Robot Ready");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    handleCommand(cmd);
  }

  // Optional: send commands from Serial Monitor too
  if (Serial.available()) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  if (cmd == '\n' || cmd == '\r' || cmd == ' ') return;

  cmd = toupper(cmd);

  if (cmd >= '0' && cmd <= '9') {
    int level = cmd - '0';
    if (level == 0) {
      baseSpeed = 0;
      stopRobot();
    } else {
      baseSpeed = map(level, 1, 9, MIN_SPEED, MAX_SPEED);
      executeMove(lastCommand);
    }
    printStatus("Speed level changed", cmd);
    return;
  }

  if (cmd == '+') {
    baseSpeed += SPEED_STEP;
    if (baseSpeed > MAX_SPEED) baseSpeed = MAX_SPEED;
    executeMove(lastCommand);
    printStatus("Speed increased", cmd);
    return;
  }

  if (cmd == '-') {
    baseSpeed -= SPEED_STEP;
    if (baseSpeed < 0) baseSpeed = 0;
    executeMove(lastCommand);
    printStatus("Speed decreased", cmd);
    return;
  }

  executeMove(cmd);
  printStatus("Command received", cmd);
}

void executeMove(char cmd) {
  lastCommand = cmd;

  switch (cmd) {
    case 'F': // Forward
      driveOmni( 1,  1,  1,  1);
      break;

    case 'B': // Backward
      driveOmni(-1, -1, -1, -1);
      break;

    case 'L': // Strafe Left
      driveOmni(-1,  1,  1, -1);
      break;

    case 'R': // Strafe Right
      driveOmni( 1, -1, -1,  1);
      break;

    case 'Q': // Rotate Left / Counter-clockwise
      driveOmni(-1,  1, -1,  1);
      break;

    case 'E': // Rotate Right / Clockwise
      driveOmni( 1, -1,  1, -1);
      break;

    case 'G': // Forward-Left diagonal
      driveOmni( 0,  1,  1,  0);
      break;

    case 'I': // Forward-Right diagonal
      driveOmni( 1,  0,  0,  1);
      break;

    case 'H': // Backward-Left diagonal
      driveOmni(-1,  0,  0, -1);
      break;

    case 'J': // Backward-Right diagonal
      driveOmni( 0, -1, -1,  0);
      break;

    case 'S': // Stop
    default:
      stopRobot();
      lastCommand = 'S';
      break;
  }
}

void driveOmni(int fl, int fr, int rl, int rr) {
  setMotor(EN_FL, IN1_FL, IN2_FL, fl * INV_FL, baseSpeed);
  setMotor(EN_FR, IN1_FR, IN2_FR, fr * INV_FR, baseSpeed);
  setMotor(EN_RL, IN1_RL, IN2_RL, rl * INV_RL, baseSpeed);
  setMotor(EN_RR, IN1_RR, IN2_RR, rr * INV_RR, baseSpeed);
}

void setMotor(int enPin, int in1Pin, int in2Pin, int direction, int speedValue) {
  speedValue = constrain(speedValue, 0, 255);

  if (direction > 0 && speedValue > 0) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enPin, speedValue);
  }
  else if (direction < 0 && speedValue > 0) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enPin, speedValue);
  }
  else {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(enPin, 0);
  }
}

void stopRobot() {
  setMotor(EN_FL, IN1_FL, IN2_FL, 0, 0);
  setMotor(EN_FR, IN1_FR, IN2_FR, 0, 0);
  setMotor(EN_RL, IN1_RL, IN2_RL, 0, 0);
  setMotor(EN_RR, IN1_RR, IN2_RR, 0, 0);
}

void printStatus(const char *msg, char cmd) {
  Serial.print(msg);
  Serial.print(": ");
  Serial.print(cmd);
  Serial.print(" | Speed = ");
  Serial.println(baseSpeed);

  BT.print(msg);
  BT.print(": ");
  BT.print(cmd);
  BT.print(" | Speed = ");
  BT.println(baseSpeed);
}
