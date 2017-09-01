//Receiver Part
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

float hall = 0.0;

RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {

  while (!Serial);
  Serial.begin (9600);
  radio.begin();
  radio.setPayloadSize(32);
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
}

void loop() {
  
      radio.read(&hall, sizeof(hall));
      Serial.print(" Received Hall Effect. = ");
      Serial.print(hall);
      Serial.print("Gauss");
      Serial.println();
      delay (1000);
    
    }
   
