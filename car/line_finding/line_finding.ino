#include <Car.h>

Car car(55);

// control pins
const int centerItr = 2;
const int centerPin = 21;
const int leftItr = 3;
const int leftPin = 20;
const int rightItr = 4;
const int rightPin = 19;

// use to adjust slightly
volatile boolean lineAtLeft = true;
volatile boolean lineAtRight = false;
volatile boolean lineChanged = false;

// use to adjust much
// >
volatile boolean leftCorner = false;
// <
volatile boolean rightCorner = false;

// const int turnSpeed = 60;

void setup() {
  //attachInterrupt(centerItr, linePlaceChanging, FALLING);
  //attachInterrupt(leftItr, findLineL, FALLING);
  //attachInterrupt(rightItr, findLineR, FALLING);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // use to adjust slightly
  if (lineChanged == true) {
    delay(50);
    car.ahead();
    lineChanged = false;
  }

  int leftState = digitalRead(leftPin);
  int rightState = digitalRead(rightPin);
  if (leftState == LOW) {
    car.turnLeft();  // car.setAMotor(leftMotor, 1, turnSpeed);
    delay(50);
    car.ahead();
  } else if (rightState == LOW){
    car.turnRight();  // car.setAMotor(leftMotor, 1, turnSpeed);
    delay(50);
    car.ahead();
  } else {
    car.ahead();
  }
}

void linePlaceChanging() {
  //static unsigned long lastMillis = 0;
  //unsigned long newMillis = millis();
  //if (newMillis - lastMillis < 50) {
    // 消除抖动
  //} else {
    int leftState = digitalRead(leftPin);
    int rightState = digitalRead(rightPin);
    // if (leftState == LOW && rightState == LOW) {}
    if (leftState == LOW) {
      // need to adjust much
      lineAtLeft = true;
      lineAtRight = false;
      lineChanged = false;
      return;
    } else if (rightState == LOW) {
      // need to adjust much
      lineAtLeft = false;
      lineAtRight = true;
      lineChanged = false;
      return;
    } else {
      // nothing
      // continue the following actions
    }
    if (lineAtRight == true) {
      car.turnLeft();  // car.setAMotor(leftMotor, 1, turnSpeed);
    } else {
      car.turnRight();  // car.setAMotor(leftMotor, 1, turnSpeed);
    }
    lineChanged = true;
    lineAtLeft = !lineAtLeft;
    lineAtRight = !lineAtRight;
  //}
}

// void findLineL()
// void findLineR()

