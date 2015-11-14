#include <Car.h>
#include <URM2.h>
#include <Servo.h>

#define RTOL false
#define LTOR true

Car car;
URM2 myURM;
Servo myservo;

const int resetPin = 52;

// const int minDistance = 20;
const int maxDistance = 40;
const int blockedDistance = 9;

const int interval = 200;

const int head = 90;
const int scan_angle = 15;

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(0);
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, LOW);
}

boolean scanDirection = RTOL;

boolean wallAtRight = false;
boolean wallAtLeft = false;

// use to judge whether the car has lost the place of wall
boolean startFlag = false;
unsigned long startMillis;

void loop() {
  // put your main code here, to run repeatedly:
  // reset the direction of URM37
  int resetPinState = digitalRead(resetPin);
  if (resetPinState == HIGH) {
    myservo.write(head);
    delay(3000);
    myservo.write(head - 90);
    delay(3000);
    myservo.write(head + 90);
    delay(3000);
    return;
  }

  // find the direction of wall, right of left
  while (wallAtRight == false && wallAtLeft == false) {
    Serial.println("finding");
    car.ahead();
    int sacn_nums = 180 / scan_angle + 1;
    for(int i = 0; i < sacn_nums; ++i) {
      int p;
      if (scanDirection == RTOL) {
        p = i;
      } else {
        p = sacn_nums - 1 - i;
      }
      myservo.write(p * scan_angle);
      delay(50);
      int distance;
      distance = myURM.getDistance();
      if (distance <= maxDistance) {
        if (p <= sacn_nums / 2) {
          wallAtRight = true;
          wallAtLeft = false;
        } else {
          wallAtLeft = true;
          wallAtRight = false;
        }
        car.stopGo();
        break;
      }
    }
    scanDirection = !scanDirection;
  }

  if (wallAtRight == true) {
    // the wall is at the right of the car
    // action
    int sacn_nums = 90 / scan_angle + 1;
    int d[sacn_nums];
    int minDistanceOfDirs = 500;
    int minDistanceP = 0;
    //if (scanDirection == RTOL)
    for(int i = 0; i < sacn_nums; ++i) {
      int p;
      if (scanDirection == RTOL) {
        p = i;
      } else {
        p = sacn_nums - 1 - i;
      }
      myservo.write(p * scan_angle);  // from 0 to 90
      delay(40);
      d[p] = myURM.getDistance();
      if (d[p] < minDistanceOfDirs) {
        minDistanceP = p;
        minDistanceOfDirs = d[p];
      }
    }
    if (minDistanceOfDirs > maxDistance) {
      if (startFlag == false) {
        startFlag = true;
        startMillis = millis();
      } else {
        unsigned long curMillis = millis();
        if (curMillis - startMillis >= 3000) {
          // lose the place of wall
          wallAtRight = false;
          wallAtLeft = false;
          startFlag = false;
        }
      }
    } else {
      startFlag = false;
    }
    if (minDistanceOfDirs < blockedDistance) {
      // too closed to the wall
      car.setSpeed(100);
      car.turnLeft();
      delay(interval);
      car.stopGo();
      car.setSpeed(70);
    } else if (minDistanceOfDirs > maxDistance) {
      // running away from the wall
      car.turnRight();
      delay(interval);
      car.stopGo();
    } else if (minDistanceP > sacn_nums / 2) {
      // running towards the wall
      car.turnLeft();
      delay(interval);
      car.stopGo();
    } else {
      car.ahead();
    }
    scanDirection = !scanDirection;
  } else if (wallAtLeft == true) {
    // the wall is at the left of the car
    // action
    int sacn_nums = 90 / scan_angle + 1;
    int d[sacn_nums];
    int minDistanceOfDirs = 500;
    int minDistanceP = 0;
    for(int i = 0; i < sacn_nums; ++i) {
      int p;
      if (scanDirection == RTOL) {
        p = i;
      } else {
        p = sacn_nums - 1 - i;
      }
      myservo.write(90 + p * scan_angle);  // from 90 to 180
      delay(40);
      d[p] = myURM.getDistance();
      if (d[p] < minDistanceOfDirs) {
        minDistanceP = p;
        minDistanceOfDirs = d[p];
      }
    }
    if (minDistanceOfDirs > maxDistance) {
      if (startFlag == false) {
        startFlag = true;
        startMillis = millis();
      } else {
        unsigned long curMillis = millis();
        if (curMillis - startMillis >= 3000) {
          // lose the place of wall
          wallAtRight = false;
          wallAtLeft = false;
          startFlag = false;
        }
      }
    } else {
      startFlag = false;
    }
    if (minDistanceOfDirs < blockedDistance) {
      // too closed to the wall
      car.setSpeed(100);
      car.turnRight();
      delay(interval);
      car.stopGo();
      car.setSpeed(70);
    } else if (minDistanceOfDirs > maxDistance) {
      // running away from the wall
      car.turnLeft();
      delay(interval);
      car.stopGo();
    } else if (minDistanceP < sacn_nums / 2) {
      // running towards the wall
      car.turnRight();
      delay(interval);
      car.stopGo();
    } else {
      car.ahead();
    }
    scanDirection = !scanDirection;
  } else {
    // to be continued
  }
}

