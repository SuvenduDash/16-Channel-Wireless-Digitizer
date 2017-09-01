int hallPin = 6;
int statePin = LOW;

void setup() {
pinMode(hallPin, INPUT);
Serial.begin(9600);

}

void loop() {
statePin = digitalRead(hallPin);
if (Serial.available())
{
  if(statePin == HIGH)
{
  Serial.println("North");
}
else if (statePin == LOW)
{
  Serial.println("South");
}
}
delay(500);
}


