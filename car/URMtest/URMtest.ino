int USValue = 0;
int timecount = 0;
int ledpin = 13;

// 定义L灯作显示
boolean flag = true;

byte DMcmd[4] = { 0x22, 0x00, 0x00, 0x22 };

// 距离命令 
void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  delay(200);
}

void loop() {
  flag = true;
  // 发送超声波测距命令
  for (int i = 0; i < 4; i++) Serial.write(DMcmd[i]);
  while (flag) {
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

        // 如果距离大于 50 厘米小灯亮起
        if (USValue >= 50) {
          digitalWrite(ledpin, HIGH);
        } else {
          digitalWrite(ledpin, LOW);
        }
        Serial.print("Distance=");
        Serial.println(USValue);      // 输出距离
      }
      flag = false;
    }
    delay(100);
  }
}
