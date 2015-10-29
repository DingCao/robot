#include "Arduino.h"
// Adjusted and Used by Junjie in 29.10.2015

// # Editor    :Jiang from DFRobot
// # Data      :18.09.2012
 
// # Product name:ultrasonic scanner 
// # Product SKU:SEN0001
// # Version :  0.2
 
// # Description:
// # The Sketch for scanning 180 degree area 4-500cm detecting range
 
// # Connection:
// #       Pin 1 VCC (URM V3.2) -> VCC (Arduino)
// #       Pin 2 GND (URM V3.2) -> GND (Arduino)
// #       Pin 4 PWM (URM V3.2) -> Pin 4 (Arduino)
// #       Pin 6 COMP/TRIG (URM V3.2) -> Pin 5 (Arduino)
// #
int URPWM = 4; // PWM Output 0£­25000US£¬Every 50US represent 1cm
int URTRIG=5; // PWM trigger pin

uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01};    // distance measure command

class URM2
{
	public:
		void sonicStart();
		int getDistance();
};

void PWM_Mode_Setup();

/* funcions to control the sonic sensor */
void URM2::sonicStart()
{
  Serial.begin(9600);
  PWM_Mode_Setup();
}

void PWM_Mode_Setup()
{ 
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH
   
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
   
  for(int i=0;i<4;i++)
  {
      Serial.write(EnPwmCmd[i]);
  } 
}

int URM2::getDistance()
{                              // a low pull on pin COMP/TRIG  triggering a sensor reading
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
      
    int DistanceMeasured=pulseIn(URPWM,LOW);
      
    if(DistanceMeasured>=10200)
    {              // the reading is invalid.
      Serial.println("Invalid");
    }
    else
    {
      int Distance=DistanceMeasured/50;           // every 50us low level stands for 1cm
      Serial.print("Distance=");
      Serial.print(Distance);
      Serial.println("cm");
      return Distance;
    }
}

