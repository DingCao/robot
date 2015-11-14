#include <Car.h>
#include <URM2.h>
#include <Servo.h>

Car car;
URM2 myURM;
Servo myservo;

const int resetPin = 52;

const int minDistance = 10;
const int maxDistance = 30;
// const int blockedDistance = 9;

const int interval = 200;

const int head = 90;
const int scan_angle = 15;

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(head - 45);
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, LOW);
}

// set the servo to a fix angle,
// and change the direction according to the distance checked.
// no delay to reach a fast reaction.
void loop() {
  unsigned long distance = myURM.getDistance();
  if (distance < minDistance) {
    car.turnLeft();
  } else if (distance < maxDistance) {
    car.turnRight();
  } else {
    car.ahead();
  }
}


