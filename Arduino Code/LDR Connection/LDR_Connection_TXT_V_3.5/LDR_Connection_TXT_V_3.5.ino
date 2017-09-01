//TXT
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define LDRpin A0             // pin where we connected the LDR and the resistor

int LDRValue = 0;             // result of reading the analog pin
RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {
pinMode(4, OUTPUT);
Serial.begin(9600);           // sets serial port for communication
radio.setRetries (15, 15);
radio.openWritingPipe (rxAddr);

radio.stopListening();

}

void loop() {
LDRValue = analogRead(LDRpin); // read the value from the LDR

if(LDRValue >= 200){
  digitalWrite (4, HIGH);     // Turn OFF LED
  //Serial.print ("High Density Light -> ");
}
else if (LDRValue >= 70) {
  digitalWrite (4, HIGH);     // Turn OFF LED
  //Serial.print ("Normal Density Light -> ");
}
else if ( LDRValue < 70){
  digitalWrite (4, LOW);     // Turn ON LED
  //Serial.print ("Low Density Light -> ");
}

Serial.println(LDRValue);      // print the value to the serial port
radio.write(&LDRValue, sizeof(LDRValue));
delay(1000);                   // wait a little
}
