int output_state = 0;
unsigned long start;

void setup() {
  Serial.begin (9600);
  start = millis();

}

void loop() {

  if((millis() - start) >=1000) {
   output_state = ! output_state;
   start = millis();
  }
    Serial.println(output_state);
    delay (100);
}
