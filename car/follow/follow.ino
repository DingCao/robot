#include <Car.h>
#include <URM.h>
#include <Servo.h>

Car car;
URM myURM;

Servo myservo;

const int minDistance = 25;
const int maxDistance = 50;
const int blockedDistance = 8;

int lastDistance = 0;
int turnMode = 0;

unsigned long previousMillis = 0;

int pos = 90;

void setup() {
  // put your setup code here, to run once:
  car.motorStart();
  myURM.sonicStart();
  myservo.attach(9);
}
/*
void loop() {
  // put your main code here, to run repeatedly:
  //unsigned long currentMillis = millis();
  int distance = myURM.getDistance();
  //pos++;
  //if(currentMillis - previousMillis >= 100) {
    //previousMillis = currentMillis;
    myservo.write(pos); 
    if (minDistance <= distance && distance <= maxDistance) {
      car.ahead();
    } else if (distance < blockedDistance) {
      car.back();
    } else {
      // distance > maxDistance
      car.stopGo();
    }
  //}
}
*/
void loop () {
  car.ahead();
  delay(500);
  car.stopGo();
  delay(1000);
  car.setAMotor(leftMotor, 1);
  car.setAMotor(rightMotor, 1, 255);
  delay(500);
  car.stopGo();
  delay(1000);
  car.setAMotor(leftMotor, 1,255);
  car.setAMotor(rightMotor, 1);
  delay(500);
  car.stopGo();
  delay(1000);
}

