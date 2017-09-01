//Transmitter Part
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define HallVolt A0

float hall = 0.0;
RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {
Serial.begin(9600);
radio.begin(); 
radio.setRetries (15, 15);
radio.openWritingPipe (rxAddr);
radio.setPayloadSize (32);
 
radio.stopListening ();

}

void loop() {
hall = analogRead (HallVolt);
hall=hall*5/1023;
//hall = (hall-2.5)*5/(0.00025*1023);
Serial.print("Hall Effect = ");
Serial.print(hall);
Serial.print("Gauss");
Serial.println();
radio.write(&hall, sizeof(hall));
delay(1000);

}
