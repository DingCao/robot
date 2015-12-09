#include <Car.h>

// control pins
const int centerPin = 19;
const int leftPin = 20;
const int rightPin = 21;

// states
int center;
int left;
int right;

const int voltage = 255;

Car car(voltage);

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
    // delay(50);
  } else if (left == HIGH && right == LOW) {
    car.turnRight();
    // delay(50);
  } else {
    car.ahead();
  }
}

void getState() {
  center = digitalRead(centerPin);
  left = digitalRead(leftPin);
  right = digitalRead(rightPin);
}

