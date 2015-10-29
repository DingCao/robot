#include "Arduino.h"

// pin to give energy to motors
const int enableLeft = 3;
const int enableRight = 2;

// pin of left motor
const int leftMotor = 24;
// pin of right motor
const int rightMotor = 22;

// default speed
const int dfvoltage = 90;

class Car {
	public:
		Car();
		Car(int voltage);
		void motorStart();
		void setSpeed(int voltage);
		void setAMotor(int pin, int mode, int voltage);
		void ahead();
		void turnLeft();
		void turnRight();
		void back();
		void stopGo();
		void turn(int mode);
	private:
		// speed
		int voltage;
};

// set up the speed
Car::Car() {
	setSpeed(dfvoltage);
}
Car::Car(int voltage) {
	setSpeed(voltage);
}

// set up the pins' mode.
void Car::motorStart() {
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(leftMotor + 1, OUTPUT);
  pinMode(rightMotor, OUTPUT);
  pinMode(rightMotor + 1, OUTPUT);
  digitalWrite(enableLeft, LOW);
  digitalWrite(enableRight, LOW);
}

void Car::setSpeed(int voltage) {
	this->voltage = voltage;
} 
// make a motor run on the right direction or reverse.
// @Param pin: the pinline of controling a motor
// @Param mode: 1 for ahead and 0 for reverse, 2 for stop
// @Param voltage: control the speed, 0 - 255
void Car::setAMotor(int pin, int mode, int voltage = dfvoltage) {
  if(mode == 2) {
  	if (pin == leftMotor) {
  		analogWrite(enableLeft, 255);
  	} else {
  		analogWrite(enableRight, 255);
  	}
    digitalWrite(pin, LOW);
    digitalWrite(pin+1, LOW);
    return;
  }
  if (pin == leftMotor) {
  	analogWrite(enableLeft, voltage);
  } else {
  	analogWrite(enableRight, voltage);
  }
  if (mode == 0) {
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, LOW);
  } else {
    digitalWrite(pin, LOW);
    digitalWrite(pin+1, HIGH);
  }
}
void Car::ahead() {
  setAMotor(leftMotor, 1, voltage);
  setAMotor(rightMotor, 1, voltage);
}

void Car::turnLeft() {
  setAMotor(leftMotor, 0, voltage);
  setAMotor(rightMotor, 1, voltage);
}

void Car::turnRight() {
  setAMotor(leftMotor, 1, voltage);
  setAMotor(rightMotor, 0, voltage);
}

void Car::back() {
  setAMotor(leftMotor, 0, voltage);
  setAMotor(rightMotor, 0, voltage);
}

void Car::stopGo() {
  setAMotor(leftMotor, 2, voltage);
  setAMotor(rightMotor, 2, voltage);
}

