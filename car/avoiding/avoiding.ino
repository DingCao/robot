#include "Car.h"
#include "URM.h"

Car car;
URM sonic;

const int minDistance = 25;
const int maxDistance = 50;
const int blockedDistance = 8;

int distance;

void setup() {
  car.motorStart();
  sonic.sonicStart();
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

