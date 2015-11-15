#include <Car.h>
#include <URM2.h>
#include <Servo.h>

#define RTOL false
#define LTOR true

Car car;
URM2 myURM;
Servo myservo;

const int maxDistance = 40;
// avoiding that hitDistance > minDistance
// otherwise, the car will stop at (minDistance, hitDistance)
const int hitDistance = 15;
const int minDistance = 18;

// time(ms) before the servo return to the starting poing
const int newScanInterval = 400;
// time(ms) for car to turn slightly when drift off the straight line
const int turnInterval = 300;
// time(ms) for car to turn 90 degrees when meet the out corner
const int turn90Interval = 500;
// time(ms) for car to walk ahead before new scan
const int aheadInterval = 500;
// time(times of loop) of losing the sight of the wall and used to judge meeting the out corner
const int cornerFindMinNum = 4;
// if cornerFindCounter >= cornerFindMinNum, meet the corner
int cornerFindCounter = 0;

const int head = 90;
const int scan_angle = 15;

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
  myservo.write(0);
}

boolean scanDirection = RTOL;

boolean wallAtRight = false;
boolean wallAtLeft = false;

void ahead() {
  myservo.write(head);
  delay(50);
  unsigned long aheadStartTime = millis();
  unsigned long aheadCurrentTime = millis();
  while (aheadCurrentTime - aheadStartTime < aheadInterval) {
    if (myURM.getDistance() >= hitDistance) {
      car.ahead();
    } else {
      car.stopGo();
      break;
    }
    aheadCurrentTime = millis();
  }
}
void loop() {
  // put your main code here, to run repeatedly:

  // find the direction of wall, right of left
  while (wallAtRight == false && wallAtLeft == false) {
    Serial.println("finding");
    // car.ahead();
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
        if (p < sacn_nums / 4) {
          wallAtRight = true;
          wallAtLeft = false;
        } else if (p > sacn_nums  * 3 / 4){
          wallAtLeft = true;
          wallAtRight = false;
        } else {
          // no
        }
        //car.stopGo();
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
    for(int p = 0; p < sacn_nums; ++p) {
      myservo.write(p * scan_angle);  // from 0 to 90
      delay(50);
      d[p] = myURM.getDistance();
      if (d[p] < minDistanceOfDirs) {
        minDistanceP = p;
        minDistanceOfDirs = d[p];
      }
    }

    if (minDistanceOfDirs > maxDistance) {
      cornerFindCounter++;
      if (cornerFindCounter == 1) {
        car.turnRight();
        delay(turnInterval);
        car.stopGo();
      } else {
        if (cornerFindCounter >= cornerFindMinNum) {
          // meet the out right corner
          car.turnRight();
          delay(turn90Interval);
          ahead();
          cornerFindCounter = 0;
        }
      }
    } else {
      cornerFindCounter = 0;
    }
    if (minDistanceOfDirs <= minDistance) {
      // too closed to the wall
      car.turnLeft();
      delay(turnInterval);
      car.stopGo();
    } else {
      ahead();
      car.stopGo();
    }
    myservo.write(0);
    delay(newScanInterval);
  } else if (wallAtLeft == true) {
    // the wall is at the left of the car
    // action
    int sacn_nums = 90 / scan_angle + 1;
    int d[sacn_nums];
    int minDistanceOfDirs = 500;
    int minDistanceP = 0;
    for(int p = 0; p < sacn_nums; ++p) {
      myservo.write(180 - p * scan_angle);  // from 180 to 90
      delay(50);
      d[p] = myURM.getDistance();
      if (d[p] < minDistanceOfDirs) {
        minDistanceP = p;
        minDistanceOfDirs = d[p];
      }
    }

    if (minDistanceOfDirs > maxDistance) {
      cornerFindCounter++;
      if (cornerFindCounter == 1) {
        car.turnLeft();
        delay(turnInterval);
        car.stopGo();
      } else {
        if (cornerFindCounter >= cornerFindMinNum) {
          // meet the out left corner
          car.turnLeft();
          delay(turn90Interval);
          ahead();
          cornerFindCounter = 0;
        }
      }
    } else {
      cornerFindCounter = 0;
    }
    if (minDistanceOfDirs <= minDistance) {
      // too closed to the wall
      car.turnRight();
      delay(turnInterval);
      car.stopGo();
    } else {
      ahead();
      car.stopGo();
    }
    myservo.write(180);
    delay(newScanInterval);
  } else {
    // to be continued
  }
}

