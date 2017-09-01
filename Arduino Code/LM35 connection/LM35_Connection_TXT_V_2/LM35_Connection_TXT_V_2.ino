//TXT
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define TempPin A0

float temp = 0.0;
RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {
Serial.begin(9600);           // sets serial port for communication
radio.begin();
radio.setRetries (15, 15);
radio.openWritingPipe (rxAddr);
radio.setPayloadSize(32);

radio.stopListening();

}

void loop() 
{
temp = analogRead(TempPin);
temp = (temp/1024.0)*500;
Serial.print("Transmitter Temp. = ");
Serial.print(temp);
Serial.print("*C");
Serial.println();
radio.write(&temp, sizeof(temp));

delay(1000);
}
