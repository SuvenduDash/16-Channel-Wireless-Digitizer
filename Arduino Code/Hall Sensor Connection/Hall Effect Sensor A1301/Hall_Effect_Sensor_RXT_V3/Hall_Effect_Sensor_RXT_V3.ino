//Receiver Part
#include <LiquidCrystal.h>
#include <SPI.h>                    //to handle the communication interface with the modem
#include <nRF24L01.h>               //to handle this particular modem driver
#include <RF24.h>                   //to control the radio modem


float hall = 0.0;
//LiquidCrystal lcd(7,8,9,10,11,12);
LiquidCrystal lcd(7,8,4,5,6,9);
RF24 radio(2,3);                     //This object represents a modem connected to the Arduino. Arguments 7 and 8 are a digital pin numbers to
                                     //which signals CE and CSN are connected.

const byte rxAddr[6] = "00001";      //In this array we wrote the address of the modem, that will receive data from Arduino. 

void setup() {

  lcd.begin (16,2);
  lcd.setCursor(1,0);
  lcd.write("Welcome to BRNS");
  
  while (!Serial);                  //This part is waiting for the Arduino USB port switches to serial COM port when You connect USB cable.
  Serial.begin (9600);              //sets the baud rate
  radio.begin();
  radio.setPayloadSize(32);         //to ensure your data can receive the largest packet possible. However, there is a maximum of 32 bytes.
 
  radio.openReadingPipe(0, rxAddr); //which determines the address of our modem which receives data. 
                                    //The 1st argument is the number of the stream. You can create up to 6 streams
                                    //that responds to different addresses. We created only address for the stream number 0.
                                    //The second argument is the address to which the stream will react to collect the data. 
  radio.startListening();           //enable receiving data via modem using the method
  
}

void loop() {
      if (radio.available()){
      radio.read(&hall, sizeof(hall));  //The 1st argument is an indicator of the variable to which you want to save the data received
                                        //by the modem. To present a variable as an indicator we applied the “&” character in front of its name. 
                                        //The second argument is the amount of data to be stored in a variable.
      lcd.setCursor (0,1);
      lcd.write("RxT hall Val");
      lcd.print (hall);                                  
      Serial.print(" Received Hall Effect. = ");
      Serial.print(hall);
      Serial.print("Gauss");
      Serial.println();
     }
      delay (1000);
    
    }
   
