//Transmiter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int output_state = 0;
unsigned long start;

RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {
  Serial.begin (9600);
  start = millis();
  radio.begin ();
  radio.setRetries (15, 15);
  radio.openWritingPipe (rxAddr);

  radio.stopListening();

}

void loop() {

  if((millis() - start) >=1000) {
   output_state = ! output_state;
   start = millis();
  }
    radio.write(&output_state, sizeof(output_state));
    Serial.println(output_state);
    //delay (1000);
}
