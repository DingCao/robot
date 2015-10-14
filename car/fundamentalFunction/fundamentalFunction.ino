int enable;       // pin to give energy to motors
int leftMotor;    // pin of left motor
int rightMotor;   // pin of right motor

void motorStart() {
  pinMode(enable, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  digitalWrite(enable, HIGH);
}

void ahead() {
  digitalWrite(leftMotor, LOW);
  digitalWrite(rightMotor, HIGH);
}

void turnLeft() {
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightMotor, HIGH);
}

void turnRight() {
  digitalWrite(leftMotor, LOW);
  digitalWrite(rightMotor, LOW);
}

void back() {
  digitalWrite(leftMotor, HIGH);
  digitalWrite(rightMotor, LOW);
}
// the setup function runs once when you press reset or power the board
void setup() {
  motorStart();
  ahead();
  delay(1000);
  turnLeft();
  delay(1000);
  turnRight();
  delay(1000);
  back();
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {

}
