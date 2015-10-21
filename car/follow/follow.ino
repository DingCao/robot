// pin to give energy to motors
const int enableLeft = 23;
const int enableRight = 22;

// pin of left motor
const int leftMotor = 36;
// pin of right motor   
const int rightMotor = 34;

int ledpin = 13;
// command to control the sonic sensor
byte DMcmd[4] = { 0x22, 0x00, 0x00, 0x22 };

const int minDistance = 30;
const int maxDistance = 100;

int lastDsitance = 0;
int turnMode = 0;
void setup() {
  // put your setup code here, to run once:
  motorStart();
  sonicStart();
}

void loop() {
  // put your main code here, to run repeatedly:
  int distance = getDistance();
  if (minDistance <= distance && distance <= maxDistance) {
    go();
    ahead();
    delay(200);
    stop();
  } else if (distance < minDistance) {
    back();
    delay(400);
    stop();
  } else if (disntance > maxDistance) {
    if (distance <= LastDistance) {
      turn(turnMode);
    } else {
      turn(1-turnMode);
    }
  }
}

/* functions to control the motors */
// set up the pins' mode.
void motorStart() {
  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);

  // give the energy of the motors
  go();
}

// make a motor run on the right direction or reverse.
// @Param pin: the pinline of controling a motor
// @Param mode: 1 for ahead and 0 for reverse
void setAMotor(int pin, bool mode) {
  if (pin == leftMotor) {
      if (mode == 0) {
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      } else {
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      }
  } else if (pin == rightMotor) {
      if (mode == 0) {
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      } else {
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      }
  } else {
  }
}

void stop() {
  digitalWrite(enableLeft, LOW);
  digitalWrite(enableRight, LOW);
}

void go() {
  digitalWrite(enableLeft, HIGH);
  digitalWrite(enableRight, HIGH);
}

void ahead() {
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 1);
}

void turnLeft() {
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 1);
}

void turnRight() {
  setAMotor(leftMotor, 1);
  setAMotor(rightMotor, 0);
}

void back() {
  setAMotor(leftMotor, 0);
  setAMotor(rightMotor, 0);
}

void turn(int mode) {
  if (mode) {
    turnRight();
  } else {
    turnLeft();
  }
}

/* funcions to control the sonic sensor */
void sonicStart() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
}

int getDistance() {
  // 是否测量到有效距离值
  bool flag = false;
  int USValue;
  
  // 发送超声波测距命令
  for (int i = 0; i < 4; i++) Serial.write(DMcmd[i]);
  while (!flag) {
    // 查询串口有无数据
    // Serial.println(Serial.available());
    if (Serial.available() > 0) {
      int header = Serial.read();

      // 0x22 开始接收距离数据
      int highbyte = Serial.read();   // 距离数据高8位
      int lowbyte = Serial.read();    // 距离数据低8位
      int sum = Serial.read();        // sum校验和

      // 数据无效
      if (highbyte == 0xff) {
        USValue = 0xffff;
      } else {
        USValue = highbyte * 0xff + lowbyte;

        // 如果距离大于 30-70 厘米小灯亮起
        if (minDistance <= USValue && USValue <= minDistance) {
          digitalWrite(ledpin, HIGH);
        } else {
          digitalWrite(ledpin, LOW);
        }
        Serial.print("Distance=");
        Serial.println(USValue);      // 输出距离
      }
    }
    flag = true;
    delay(100);
  }
    return USValue;
}

