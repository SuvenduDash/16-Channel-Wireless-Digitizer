//TXT
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define LDRpin A0

int LDRValue = 0;
RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {
Serial.begin(9600);
radio.begin ();
radio.setRetries (15, 15);
radio.openWritingPipe (rxAddr);

radio.stopListening();

}

void loop() {
  LDRValue = analogRead(LDRpin);
  Serial.println(LDRValue);
  radio.write(&LDRValue, sizeof(LDRValue));

  delay (1000);
}
