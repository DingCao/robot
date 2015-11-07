#include <Car.h>

// control pins
const int leftPin
const int centerPin
const int rightPin

// states
int center;
int left;
int right;

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(centerPin, INPUT);
}

void loop() {
  getState();
  if (center == LOW) {
    if (left == LOW && right == HIGH) turnRight();
    else if (left == HIGH && right == LOW) turnLeft(); 
    else if (left == HIGH && right == HIGH) ahead();
    else
  } else {
    stopGo();
  }
}

void getState() {
  center = digitalRead(centerPin);
  left = digitalRead(leftPin);
  right = digitalRead(rightPin);
}

