#include <Servo.h>
#include "Car.h"
#include "URM2.h"

Car car;
URM2 sonic;
Servo myservo;

const int minDistance = 25;
const int maxDistance = 50;
const int blockedDistance = 8;

int distance;

void setup() {
  // opens the motors and the sonic sensor
  car.motorStart();
  sonic.sonicStart();

  // link to servo
  myservo.attach(9);
  // set to the ahead direction
  myservo.write(90);
}

void loop() {
  distance = sonic.getDistance();
  if (minDistance <= distance) {
    car.ahead();
  } else if (distance < blockedDistance) {
    car.back();
  } else {
    // distance > maxDistance
    car.stopGo();
    car.turnRight();
  }
}

