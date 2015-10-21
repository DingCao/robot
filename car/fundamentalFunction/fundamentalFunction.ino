// pin to give energy to motors
const int enableLeft = 23;
const int enableRight = 22;

// pin of left motor
const int leftMotor = 36;
// pin of right motor   
const int rightMotor = 34;

// set up the pins' mode.
void motorStart() {
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);

  // give the energy of the motors
  go();
}

// make a motor run on the right direction or reverse.
// @Param pin: the pinline of controling a motor
// @Param mode: 1 for ahead and 0 for reverse
void setAMotor(int pin, bool mode) {
  if (pin == leftMotor) {
      if (mode == 0) {
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      } else {
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      }
  } else if (pin == rightMotor) {
      if (mode == 0) {
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      } else {
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      }
  } else {
  }
}

void ahead() {
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 1);
}

void turnLeft() {
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 1);
}

void turnRight() {
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 0);
}

void back() {
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 0);
}

void stop() {
  digitalWrite(enableLeft, LOW);
  digitalWrite(enableRight, LOW);
}

void go() {
  digitalWrite(enableLeft, HIGH);
  digitalWrite(enableRight, HIGH);
}

// the setup function runs once when you press reset or power the board
void setup() {
  motorStart();
  // ahead();
  // delay(500);
  // turnLeft();
  // delay(500);
  // turnRight();
  // delay(500);
  // back();
  // delay(500);
}


void turn(int mode) {
  if (mode) {
    turnRight();
  } else {
    turnLeft();
  }
}

// the loop function runs over and over again forever
void loop() {
  go();
  ahead();
}
