const int ledCol = 5;
// the column of led(there are only two rows)
const int ledPin = 22;
// the first pin to control led
const int lpPic3 = 2;
const int lpPic5 = 20;
const int butPin = ledPin + ledCol * 2;
void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  for (int i = 0; i < ledCol * 2; ++i) {
    pinMode(ledPin + i, OUTPUT);
  }
  pinMode(butPin, INPUT);
}

void lightLed(int pin) {
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
}

void flashTogether(int num) {
  for (int i = 0; i < num; ++i) {
    lightLed(ledPin + i * 2);
    lightLed(ledPin + 1 + i * 2);
  }
  delay(800);
}

void lightLine(int line, int len) {
  if (len > 5) {
    len = 5;
  }
  for (int i = 0; i < len; ++i) {
    digitalWrite(ledPin + line + i * 2, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // pic one
  for (int i = 0; i < ledCol; ++i) {
    lightLed(ledPin + i * 2);
    delay(51);
  }
  for (int i = 0; i < ledCol; ++i) {
    lightLed(ledPin + ledCol * 2 - 1 - i * 2);
    delay(51);
  }

  // pic two
  for (int i = 0; i < ledCol; ++i) {
    digitalWrite(ledPin + i * 2, HIGH);
    delay(51);
  }
  for (int i = 0; i < ledCol; ++i) {
    digitalWrite(ledPin + ledCol * 2 - 1 - i * 2, HIGH);
    delay(51);
  }
  for (int i = 0; i < ledCol; ++i) {
    digitalWrite(ledPin + 1 + i * 2, LOW);
    delay(51);
  }
  for (int i = 0; i < ledCol; ++i) {
    digitalWrite(ledPin + ledCol * 2 - 2 - i * 2, LOW);
    delay(51);
  }

  delay(500);

  // pic three
  for (int n = 0; n < lpPic3 * 2; ++n) {
    if (n % 2 == 0) {
      // M type
      for (int i = 0; i < ledCol; ++i) {
        digitalWrite(ledPin + i * 2 + i % 2, HIGH);
      }
    } else {
      // W type
      for (int i = 0; i < ledCol; ++i) {
        digitalWrite(ledPin + i * 2 + (i + 1) % 2, HIGH);
      }
    }
    delay(500);
    for (int i = 0; i < ledCol * 2; ++i) {
      digitalWrite(ledPin + i, LOW);
    }
  }

  delay(500);

  // pic four
  flashTogether(1);
  flashTogether(2);
  flashTogether(3);
  flashTogether(4);
  flashTogether(5);

  // pic five
  int left = 0, right = random(6);
  for (int i = 0; i < lpPic5; ++i) {
    for (int k = 0; k < ledCol * 2; ++k) {
      digitalWrite(ledPin + k, LOW);
    }
    lightLine(1, left);
    lightLine(0, right);
    left = right;
    right = random(6);
    delay(500);
  }
  for (int i = 0; i < ledCol * 2; ++i) {
    digitalWrite(ledPin + i, LOW);
  }

  // game
  int fail = 0;
  int p = 0;
  // 0 for down/right and 1 for up/left
  while (fail != 1) {
    int lr = random(2);
    // 1 for down/right and 0 for up/left
    for (int i = 0; i < ledCol; ++i) {
      int butState = digitalRead(butPin);
      if(butState == HIGH) {
        // blocked
        digitalWrite(ledPin + !p, HIGH);
        digitalWrite(ledPin + p, LOW);
        p = !p;
      } else {
        digitalWrite(ledPin + p, HIGH);
        digitalWrite(ledPin + !p, LOW);
      }
      lightLed(ledPin + ledCol * 2 - 1 - lr - i * 2);
      if (i == 4 && lr == !p) {
        fail = 1;
      }
      delay(1000);
    }
  }
  // game end
}
