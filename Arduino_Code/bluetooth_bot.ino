#include <SoftwareSerial.h>

// ================= HC-05 =================
const uint8_t BT_RX = 2;   // Nano D2 <- HC-05 TXD
const uint8_t BT_TX = 3;   // Nano D3 -> HC-05 RXD

SoftwareSerial bt(BT_RX, BT_TX);


// ================= TB6612FNG =================
const uint8_t PWMA = 5;
const uint8_t AIN1 = 7;
const uint8_t AIN2 = 6;

const uint8_t PWMB = 10;
const uint8_t BIN1 = 8;
const uint8_t BIN2 = 9;


// ================= MOTOR DIRECTION =================
const bool INVERT_LEFT  = false;
const bool INVERT_RIGHT = false;


// ================= SPEED =================
int speedVal = 140;
char lastCmd = 'S';


// ====================================================
// Set one motor
// ====================================================
void setMotor(uint8_t in1, uint8_t in2,
              uint8_t pwm, int spd, bool invert) {

  if (invert)
    spd = -spd;

  if (spd > 0) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(pwm, spd);

  }
  else if (spd < 0) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(pwm, -spd);

  }
  else {

    // Stop motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(pwm, 0);
  }
}


// ====================================================
// Control both motors
// ====================================================
void setDrive(int leftSpeed, int rightSpeed) {

  setMotor(AIN1, AIN2, PWMA,
           leftSpeed, INVERT_LEFT);

  setMotor(BIN1, BIN2, PWMB,
           rightSpeed, INVERT_RIGHT);
}


// ====================================================
// Smooth acceleration
// ====================================================
void smoothDrive(char cmd) {

  int targetLeft = 0;
  int targetRight = 0;


  // Determine target speed
  switch (cmd) {

    case 'F':
      targetLeft = speedVal;
      targetRight = speedVal;
      break;

    case 'B':
      targetLeft = -speedVal;
      targetRight = -speedVal;
      break;

    case 'L':
      targetLeft = -speedVal;
      targetRight = speedVal;
      break;

    case 'R':
      targetLeft = speedVal;
      targetRight = -speedVal;
      break;

    case 'S':
      setDrive(0, 0);
      return;
  }


  // ===============================
  // Start from ZERO
  // ===============================

  int maxTarget = max(abs(targetLeft), abs(targetRight));


  for (int currentSpeed = 0;
       currentSpeed <= maxTarget;
       currentSpeed += 20) {

    int leftSpeed;
    int rightSpeed;


    // Left motor
    if (targetLeft > 0)
      leftSpeed = min(currentSpeed, abs(targetLeft));

    else
      leftSpeed = -min(currentSpeed, abs(targetLeft));


    // Right motor
    if (targetRight > 0)
      rightSpeed = min(currentSpeed, abs(targetRight));

    else
      rightSpeed = -min(currentSpeed, abs(targetRight));


    setDrive(leftSpeed, rightSpeed);

    delay(100);
  }


  // Make sure final target speed is reached
  setDrive(targetLeft, targetRight);
}


// ====================================================
// SETUP
// ====================================================
void setup() {

  Serial.begin(9600);

  // HC-05
  bt.begin(9600);

  // Motor pins
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // Start stopped
  setDrive(0, 0);

  Serial.println("Bluetooth Bot Ready");
}


// ====================================================
// LOOP
// ====================================================
void loop() {

  if (bt.available()) {

    char c = toupper(bt.read());

    Serial.print("Received: ");
    Serial.println(c);


    // ===============================
    // MOVEMENT
    // ===============================

    if (c == 'F' ||
        c == 'B' ||
        c == 'L' ||
        c == 'R' ||
        c == 'S') {

      lastCmd = c;

      smoothDrive(c);
    }


    // ===============================
    // SPEED 1-9
    // ===============================

    else if (c >= '1' && c <= '9') {

      speedVal = map(c - '0', 1, 9, 60, 255);

      Serial.print("Speed: ");
      Serial.println(speedVal);


      // Re-apply current direction
      if (lastCmd != 'S') {
        smoothDrive(lastCmd);
      }
    }


    // ===============================
    // FULL SPEED
    // ===============================

    else if (c == 'Q') {

      speedVal = 255;

      Serial.println("Full Speed");

      if (lastCmd != 'S') {
        smoothDrive(lastCmd);
      }
    }
  }
}