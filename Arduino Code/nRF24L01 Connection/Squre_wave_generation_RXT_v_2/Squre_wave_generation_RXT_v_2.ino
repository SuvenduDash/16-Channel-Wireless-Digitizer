//Reciver
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int output_state = 0;

RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {

  while (!Serial);
  Serial.begin (9600);
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
}

void loop() {
      
      radio.read(&output_state, sizeof(output_state));
      Serial.println(output_state);
      delay(100);
    }
       
