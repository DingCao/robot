#include "Arduino.h"

// pin to give energy to motors
const int enableLeft = 3;
const int enableRight = 2;

// pin of left motor
const int leftMotor = 24;
// pin of right motor   
const int rightMotor = 22;

// speed
const int voltage = 80;

class Car {
	public:
		void motorStart();
		void setAMotor(int pin, bool mode);void ahead();
		void turnLeft();
		void turnRight();
		void back();
		void stopGo();
		void turn(int mode);
};

// set up the pins' mode.
void Car::motorStart() {
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(leftMotor + 1, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(rightMotor + 1, OUTPUT);
}

// make a motor run on the right direction or reverse.
// @Param pin: the pinline of controling a motor
// @Param mode: 1 for ahead and 0 for reverse
void Car::setAMotor(int pin, bool mode) {
  if(mode == 2) {
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, HIGH);
  }
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
  	/* nothing */
  }
}

void Car::ahead() {
  analogWrite(enableLeft, voltage);
  analogWrite(enableRight, voltage);
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 1);
}

void Car::turnLeft() {
  analogWrite(enableLeft, voltage);
  analogWrite(enableRight, voltage);
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 1);
}

void Car::turnRight() {
  analogWrite(enableLeft, voltage);
  analogWrite(enableRight, voltage);
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 0);
}

void Car::back() {
  analogWrite(enableLeft, voltage);
  analogWrite(enableRight, voltage);
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 0);
}

void Car::stopGo() {
  analogWrite(enableLeft, 255);
  analogWrite(enableRight, 255);
  setAMotor(leftMotor, 2);
  setAMotor(rightMotor, 2);
}

void Car::turn(int mode) {
  if (mode) {
    turnRight();
  } else {
    turnLeft();
  }
}

