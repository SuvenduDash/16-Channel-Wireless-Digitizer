int PIN= 13;

void setup() {
  Serial.begin (9600);
  pinMode(PIN, OUTPUT);
}

void loop() {
  int state = 0;

  while(1) {
    if (state == 0) {
      digitalWrite(PIN, LOW);
      state = 1;
    }
    else {
      digitalWrite(PIN, HIGH);
      state = 0;
    }
        delay(100);
        Serial.println(PIN);
  }
}

