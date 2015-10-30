#include <Car.h>
#include <URM2.h>
#include <Servo.h>

Car car;
URM2 myURM;
Servo myservo;

const int resetPin = 52;

const int minDistance = 20;
const int maxDistance = 40;
const int blockedDistance = 9;

const int interval = 500;

const int head = 90;
void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(head);
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  // reset the direction
  int resetPinState = digitalRead(resetPin);
  if (resetPinState == HIGH) {
    myservo.write(head);
    delay(interval * 10);
    myservo.write(head - 90);
    delay(interval * 10);
    myservo.write(head + 90);
    delay(interval * 10);
    return;
  }

  boolean finded = false;
  int d[3];
  for(int i = 0; i <= 2; ++i) {
    myservo.write(i * 90);
    delay(interval);
    d[i] = myURM.getDistance();
    Serial.println("1");
    Serial.println(i);
    Serial.println(d[i]);
  }
  Serial.println("j");
  if (d[1] >= blockedDistance) {
    if (minDistance <= d[0] && d[0] <= maxDistance) {
      car.turnRight();
      Serial.println("right");
      delay(interval);
      car.stopGo();
    } else if (minDistance <= d[2] && d[2] <= maxDistance) {
      car.turnLeft();
      Serial.println("left");
      delay(interval);
      car.stopGo();
    } else if (d[0] < blockedDistance) {
      car.turnLeft();
      delay(interval);
      car.stopGo();
    } else if (d[2] < blockedDistance) {
      car.turnRight();
      delay(interval);
      car.stopGo();
    } else {
      car.ahead();
    }
  } else {
    // d[1] < blockedDistance, which means that wall is in front of the car
    if (blockedDistance <= d[0]) {
      car.turnLeft();
      Serial.println("bleft");
      delay(interval * 2);
      car.stopGo();
    } else if (blockedDistance <= d[2]) {
      car.turnRight();
      Serial.println("bright");
      delay(interval * 2);
      car.stopGo();
    } else {
      car.stopGo();
    }
  }
  // for two
  for(int i = 2; i >= 0 ; --i) {
    myservo.write(i * 90);
    delay(interval);
    d[i] = myURM.getDistance();
    Serial.println("2");
    Serial.println(i);
    Serial.println(d[i]);
  }
  Serial.println("j");
  if (d[1] >= blockedDistance) {
    if (minDistance <= d[0] && d[0] <= maxDistance) {
      car.turnRight();
      Serial.println("2right");
      delay(interval);
      car.stopGo();
    } else if (minDistance <= d[2] && d[2] <= maxDistance) {
      car.turnLeft();
      Serial.println("2left");
      delay(interval);
      car.stopGo();
    } else if (d[0] < blockedDistance) {
      car.turnLeft();
      delay(interval);
      car.stopGo();
    } else if (d[2] < blockedDistance) {
      car.turnRight();
      delay(interval);
      car.stopGo();
    } else {
      car.ahead();
    }
  } else {
    // d[1] < blockedDistance, which means that wall is in front of the car
    if (blockedDistance <= d[0]) {
      car.turnLeft();
      Serial.println("2bleft");
      delay(interval * 2);
      car.stopGo();
    } else if (blockedDistance <= d[2]) {
      car.turnRight();
      Serial.println("2bright");
      delay(interval * 2);
      car.stopGo();
    } else {
      car.stopGo();
    }
  }
}

