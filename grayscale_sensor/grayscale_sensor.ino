//const int linePin[0] = 22;
//const int linePin[1] = 28;
//const int linePin[2] = 34;
//const int linePin[3] = 40;
const int positionPin = 46;  // four position and 46 is the leftest
const int butPin = 52;
const int grayPin = 0;
const int seedPin = 1;  // analog pin 1 should not be used
const int pinNum = 32;
const int rowOfLed = 5;  // the lengths of row of len
const int colOfLed = 4;
const int linePin[colOfLed] = {22, 28, 34, 40};
// 5 led per line and the 6th pin is not connected with a led

const long interval = 1000; 
unsigned long previousMillis = 0;

int gray = 0;
int numPosition = 0;  // up to 3 from left to right
int nums[4] = {0};  // the nums of four positions
int part = 0;  // which part to play, 0 - 2, and part 1 is a game

int lens[5] = {0};  // use to show part 2 and lens[0] is meaningless

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 24 + 4; ++i) {
    pinMode(linePin[0] + i, OUTPUT);
  }
  randomSeed(analogRead(seedPin));
  Serial.begin(9600);
}

void lightLed(int startPin, int * array, int len) {
  for (int i = 0; i < len; ++i) {
    digitalWrite(startPin + array[i], HIGH);
  }
}
void flashLed(int pin) {
  digitalWrite(pin, HIGH);
  delay(interval);
  digitalWrite(pin, LOW);
}

void printNum(int num) {
  switch(num) {
    case 0:
    {
      int array1[] = {0, 1, 2, 3, 4};
      int array2[] = {0, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array1, sizeof(array1) / sizeof(int));
      break;
    }
    case 1:
    {
      int array1[] = {0, 1, 2, 3, 4};
      lightLed(linePin[2], array1, sizeof(array1) / sizeof(int));
      break;
    }
    case 2:
    {
      int array1[] = {0, 1, 2, 4};
      int array2[] = {0, 2, 4};
      int array3[] = {0, 2, 3, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array3, sizeof(array3) / sizeof(int));
      break;
    }
    case 3:
    {
      int array1[] = {0, 2, 4};
      int array2[] = {0, 1, 2, 3, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[2], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[3], array2, sizeof(array2) / sizeof(int));
      break;
    }
    case 4:
    {
      int array1[] = {2, 3, 4};
      int array2[] = {2};
      int array3[] = {0, 1, 2, 3, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array3, sizeof(array3) / sizeof(int));
      lightLed(linePin[3], array2, sizeof(array2) / sizeof(int));
      break;
    }
    case 5:
    {
      int array1[] = {0, 2, 3, 4};
      int array2[] = {0, 2, 4};
      int array3[] = {0, 1, 2, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array3, sizeof(array3) / sizeof(int));
      break;
    }
    case 6:
    {
      int array1[] = {0, 1, 2, 3, 4};
      int array2[] = {0, 2, 4};
      int array3[] = {0, 1, 2, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array3, sizeof(array3) / sizeof(int));
      break;
    }
    case 7:
    {
      int array1[] = {4};
      int array2[] = {0, 1, 2, 3, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[2], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[3], array2, sizeof(array2) / sizeof(int));
      break;
    }
    case 8:
    {
      int array1[] = {0, 1, 2, 3, 4};
      int array2[] = {0, 2, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array1, sizeof(array1) / sizeof(int));
      break;
    }
    case 9:
    {
      int array1[] = {0, 2, 3, 4};
      int array2[] = {0, 2, 4};
      int array3[] = {0, 1, 2, 3, 4};
      lightLed(linePin[0], array1, sizeof(array1) / sizeof(int));
      lightLed(linePin[1], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[2], array2, sizeof(array2) / sizeof(int));
      lightLed(linePin[3], array3, sizeof(array3) / sizeof(int));
      break;
    }
    default:
    break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int butState = digitalRead(butPin);
  if(butState == HIGH) {
    // blocked
    gray = analogRead(grayPin);
    Serial.println(gray, DEC);
    part = 2;
    previousMillis = millis();
    unsigned long currentMillis = millis();
    while (currentMillis - previousMillis <= interval) {
      butState = digitalRead(butPin);
      if (butState == LOW) {
        part = 0;
        break;
      }
      currentMillis = millis();
    }
    if (part == 2) {
      previousMillis = millis();
      currentMillis = millis();
      while (currentMillis - previousMillis <= interval * 2) {
        butState = digitalRead(butPin);
        if (butState == LOW) {
          part = 1;
          break;
        }
        currentMillis = millis();
      }
    }
    if (part == 0) {
      for (int i = 0; i < pinNum; ++i) {
        digitalWrite(linePin[0] + i, LOW);
      }
      int tmp = gray;
      for (int i = 0; i < 4; ++i) {
        nums[3 - i] = tmp % 10;
        tmp /= 10;
      }
      previousMillis = millis();
    } else if (part == 1){
      for (int i = 0; i < pinNum; ++i) {
        digitalWrite(linePin[0] + i, LOW);
      }
      // game
      Serial.println("game start");
      int fail = 0;  // 1 if game is over
      int p = 0;
      // up to 3 from left to right and 
      // determine the place of player
      while (fail != 1) {
        int lr = random(4);
        // determine the place of bullet
        for (int i = rowOfLed - 1; i >= 0; --i) {
          gray = analogRead(grayPin);
          if(gray > 400) {
            // right
            p++;
            Serial.println("right");
            if (p >= colOfLed) {
              p = colOfLed - 1;
            }
          } else if (gray > 300){
            // left
            p--;
            Serial.println("left");
            if (p < 0) {
              p = 0;
            }
          } else {
            // do nothing
          }
          for (int itr = 0; itr < colOfLed; ++itr) {
            digitalWrite(linePin[itr], LOW);
          }
          digitalWrite(linePin[p], HIGH);
          flashLed(linePin[lr] + i);
          if (i == 0 && lr == p) {
            fail = 1;
          }
          delay(interval);
        }
      }
      // game end
      Serial.println("game end");
    } else {
      for (int i = 0; i < pinNum; ++i) {
        digitalWrite(linePin[0] + i, LOW);
      }
      for (int i = 1; i <= 3; ++i) {
        lens[i] = lens[i + 1];
      }
      lens[4] = gray / 100;
      int array0[] = {0, 1, 2, 3, 4};
      lightLed(linePin[3], array0, lens[4]);
      lightLed(linePin[2], array0, lens[3]);
      lightLed(linePin[1], array0, lens[2]);
      lightLed(linePin[0], array0, lens[1]);
    }
  } else {
    // show nuber
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval * 2) {
      for (int i = 0; i < pinNum; ++i) {
        digitalWrite(linePin[0] + i, LOW);
      }
      numPosition++;
      if (numPosition == 4) {
        numPosition = 0;
      }
      previousMillis = currentMillis;
      
    } else {
      printNum(nums[numPosition]);
      digitalWrite(positionPin + numPosition, HIGH);
    }
  }
}

