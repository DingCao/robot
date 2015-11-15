#include <Car.h>

// control pins
const int leftPin = 31;
const int centerPin = 32;
const int rightPin = 33;

// states
int center;
int left;
int right;

Car car;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(centerPin, INPUT);
}

void loop() {
  getState();
  if (center == LOW) {
    car.ahead();
  } else if (left == LOW && right == HIGH) {
    car.turnLeft();
  } else if(left == HIGH && right == LOW) {
    car.turnRight();
  } else {
    car.stopGo();
  }
}

void getState() {
  center = digitalRead(centerPin);
  left = digitalRead(leftPin);
  right = digitalRead(rightPin);
}

