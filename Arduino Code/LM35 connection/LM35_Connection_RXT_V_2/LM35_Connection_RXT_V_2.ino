//RXT
//#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

float temp;
//LiquidCrystal lcd(7,8,9,10,11,12);
RF24 radio(7,8);

const byte rxAddr[6] = "00001";

void setup() {

  //lcd.begin (16,2);
  //lcd.setCursor (1,0);
  //lcd.write("TEMPERATURE: ");
  
  while (!Serial);
  Serial.begin (9600);
  radio.begin();
  radio.setPayloadSize(32);
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
}

void loop() {
  
      radio.read(&temp, sizeof(temp));
      //lcd.setCursor (0,1);
      //lcd.print (temp);
      Serial.print(" Received Temp. = ");
      Serial.print(temp);
      Serial.print("*C");
      Serial.println();
      delay (1000);
    
    }
   
