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
unsigned long URPWM=4;  // PWM Output 0-25000US, Every 50US represent 1cm
unsigned long URTRIG=5;  // PWM trigger pin

uint8_t EnPwmCmd[4]={0x44,0x02,0xbb,0x01}; // distance measure command

class URM2
{
    public:
        void sonicStart();
        unsigned long getDistance();
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
   
  for(unsigned long i=0;i<4;i++)
  {
      Serial.write(EnPwmCmd[i]);
  } 
}

unsigned long URM2::getDistance()
{                              // a low pull on pin COMP/TRIG  triggering a sensor reading
    boolean  isValid = false; 

    unsigned long previousMillis = millis();
    unsigned long currentMillis = millis();
    while (currentMillis - previousMillis <= 100 && !isValid) {
    // the time keep getting distance before it is valid
        digitalWrite(URTRIG, LOW);
        digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
          
        unsigned long DistanceMeasured=pulseIn(URPWM,LOW);
          
        if(DistanceMeasured>15000)
        {              // the reading is invalid.
          Serial.println("Invalid");
          isValid = false;
        }
        else
        {
          unsigned long Distance=DistanceMeasured/50;           // every 50us low level stands for 1cm
          Serial.print("Distance=");
          Serial.print(Distance);
          Serial.println("cm");
          isValid = true;
          return Distance;
	    }
		currentMillis = millis();
	}
	if (!isValid) {
	    unsigned long Distance=300;
	    return Distance;
    }
}

