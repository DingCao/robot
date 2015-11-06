#include <Car.h>
#include <URM2.h>
#include <Servo.h>

#define RTOL false
#define LTOR true

Car car;
URM2 myURM;
Servo myservo;

const int resetPin = 52;

const int minDistance = 15;
const int maxDistance = 30;
const int blockedDistance = 8;

const int head = 90;
const int scan_angle = 5;

int range = 60;
int straightRange = 20;
// go straight in the range between 
// head - straightRange  and head + straightRange

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(head - range);
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, LOW);
}

boolean scanDirection = RTOL;
boolean finded = false;

void loop() {
  // put your main code here, to run repeatedly:
  // reset the direction of URM37
  int resetPinState = digitalRead(resetPin);
  if (resetPinState == HIGH) {
    myservo.write(head);
    delay(2000);
    myservo.write(head - 90);
    delay(2000);
    myservo.write(head + 90);
    delay(2000);
    return;
  }
  if (scanDirection == RTOL) {
    finded = false;
  }
  for(int i = head - range; i <= head + range; i += scan_angle) {
    int p;
    if (scanDirection == RTOL) {
      p = i;
    } else {
      p = 180 - i;
    }
    myservo.write(p);

    int distance;
    distance = myURM.getDistance();

    if (minDistance <= distance && distance <= maxDistance) {
      if (p >= head - straightRange && p <= head + straightRange) {
        while (true) {
          car.ahead();
          delay(50);
          distance = myURM.getDistance();
          if (minDistance > distance || distance > maxDistance) {
            car.stopGo();
            break;
          }
        }
      } else if (p >= head - range && p < head - straightRange) {
        car.setAMotor(leftMotor, 1);
        car.setAMotor(rightMotor, 2);
      } else {
        // p <= head  + range && p > head + straightRange
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
    delay(50);
  }

  if (scanDirection == LTOR && !finded) {
    car.turnLeft();
    delay(500);
    car.stopGo();
  }
  scanDirection = !scanDirection;
}

