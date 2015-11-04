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
  // �Ƿ��������Ч����ֵ
  bool flag = false;
  int USValue;

  // ���ͳ������������
  for (int i = 0; i < 4; i++) Serial.write(DMcmd[i]);
  while (!flag) {
    // ��ѯ������������
    // Serial.println(Serial.available());
    if (Serial.available() > 0) {
      int header = Serial.read();

      // 0x22 ��ʼ���վ�������
      int highbyte = Serial.read();   // �������ݸ�8λ
      int lowbyte = Serial.read();    // �������ݵ�8λ
      int sum = Serial.read();        // sumУ���

      // ������Ч
      if (highbyte == 0xff) {
        USValue = 0xffff;
      } else {
        USValue = highbyte * 0xff + lowbyte;

        Serial.print("Distance=");
        Serial.println(USValue);      // �������
      }
    }
    flag = true;
    // delay(100);
  }
    return USValue;
}
