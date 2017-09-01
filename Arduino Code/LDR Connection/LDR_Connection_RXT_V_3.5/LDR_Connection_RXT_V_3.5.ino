//RXT
#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int LDRValue = 0;
LiquidCrystal lcd(7,8,9,10,11,12);
RF24 radio(5,6);

const byte rxAddr[6] = "00001";

void setup() {

  lcd.begin (16,2);
  lcd.setCursor (1,0);
  lcd.write("LIGHT DENSITY: ");
  
  while (!Serial);
  Serial.begin (9600);
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
  
}

void loop() {
  
      radio.read(&LDRValue, sizeof(LDRValue));
      lcd.setCursor (0,1);
      lcd.print (LDRValue);
      Serial.println(LDRValue);
      delay (1000);
    
    }
   
