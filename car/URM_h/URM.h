// caution
// something was wrong with this class and stop using it
// caution

#include "Arduino.h"

// command to control the sonic sensor
byte DMcmd[4] = { 0x22, 0x00, 0x00, 0x22 };

class URM {
	public:
		void sonicStart();
		int getDistance();
};
/* funcions to control the sonic sensor */
void URM::sonicStart() {
  Serial.begin(9600);
}

int URM::getDistance() {
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

        Serial.print("Distance=");
        Serial.println(USValue);      // 输出距离
      }
    }
    flag = true;
    // delay(100);
  }
    return USValue;
}
