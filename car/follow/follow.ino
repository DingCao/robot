#include <Car.h>
#include <URM.h>
#include <Servo.h>

Car car;
URM myURM;

Servo myservo;

const int minDistance = 15;
const int maxDistance = 30;
const int blockedDistance = 8;

const int head = 90;
int range = 60;
int straightRange = 20;
// go straight in the range between 
// head - straightRange  and head + straightRange

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(range);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean finded = false;
  for(int i = head - range; i <= head + range; i += 5) {
    myservo.write(i);
    int distance = myURM.getDistance();
    if (minDistance <= distance && distance <= maxDistance) {
      if (i >= head - straightRange && i <= head + straightRange) {
        while (true) {
          car.ahead();
          delay(5);
          distance = myURM.getDistance();
          if (minDistance > distance || distance > maxDistance) {
            car.stopGo();
            break;
          }
        }
      } else if (i >= head - range && i < head - straightRange) {
        car.setAMotor(leftMotor, 1);
        car.setAMotor(rightMotor, 2);
      } else {
        // i <= head  + range && i > head + straightRange
        car.setAMotor(leftMotor, 2);
        car.setAMotor(rightMotor, 1);
      }
      finded = true;
    } else if (distance <= blockedDistance){
      car.back();
      delay(100);
      car.stopGo();
    } else {
      car.stopGo();
    }
    delay(15);
  }

  for(int i = head + range; i >= head - range ; i -= 5) {
    myservo.write(i);
    int distance = myURM.getDistance();
    if (minDistance <= distance && distance <= maxDistance) {
      if (i >= head - straightRange && i <= head + straightRange) {
        while (true) {
          car.ahead();
          delay(5);
          distance = myURM.getDistance();
          if (minDistance > distance || distance > maxDistance) {
            car.stopGo();
            break;
          }
        }
      } else if (i >= head - range && i < head - straightRange) {
        car.setAMotor(leftMotor, 1);
        car.setAMotor(rightMotor, 2);
      } else {
        // i <= head  + range && i > head + straightRange
        car.setAMotor(leftMotor, 2);
        car.setAMotor(rightMotor, 1);
      }
      finded = true;
    } else if (distance <= blockedDistance){
      car.back();
      delay(100);
      car.stopGo();
    } else {
      car.stopGo();
    }
    delay(15);
  }

  if (!finded) {
    car.turnLeft();
    delay(1000);
    car.stopGo();
  }
}

