//Transmitter Part
#include <LiquidCrystal.h>
#include <SPI.h>              //to handle the communication interface with the modem
#include <nRF24L01.h>         //to handle this particular modem driver
#include <RF24.h>             //to control the radio modem

#define HallVolt A4           //declear the analog pin A0

float hall = 0.0;
LiquidCrystal lcd(7,8,4,5,6,9);
RF24 radio(2,3);              //This object represents a modem connected to the Arduino. Arguments 7 and 8 are a digital pin numbers to
                              //which signals CE and CSN are connected.

const byte rxAddr[6] = "00001"; //In this array we wrote the address of the modem, that will receive data from Arduino. 
                                //You can create up to 6 streams that responds to different addresses.

void setup() {

lcd.begin (16,2);
lcd.setCursor(1,0);
lcd.write("Welcome to BRNS");
Serial.begin(9600);            //sets the baud rate
radio.begin(); 
radio.setRetries (15, 15);     // The 1st argument sets how often modem will retry. It is a multiple of 250 microseconds. 15 * 250 = 3750.
                               //So, if the recipient does not receive data, modem will try to send them every 3.75 milliseconds. 
                               //Second argument is the number of attempts. 
                                                              
radio.openWritingPipe (rxAddr); //sets the address of the receiver to which the program will send data. Its argument is an array previously made with the receiver address.
radio.setPayloadSize (32);     //to ensure your data can receive the largest packet possible. However, there is a maximum of 32 bytes.
 
radio.stopListening ();         //It switch the modem to data transmission mode.

}

void loop() {

hall = analogRead (HallVolt);  //read the analog pin 
hall=hall*5/1023;
//hall = (hall-2.5)*5/(0.00025*1023);
lcd.setCursor (0,1);
lcd.write("TxT hall Val");
lcd.print(hall);
Serial.print("Transmite Hall Effect = "); 
Serial.print(hall);
Serial.print("Gauss");
Serial.println();
radio.write(&hall, sizeof(hall)); // we send hall through the radio to the modem (the address of the modem was set up earlier using “openWritingPipe”). 
                                  //First argument is an indication of the variable that stores the data to send. That’s why we used “&” before the variable name, 
                                  //so we can make an indicator from this variable. 
                                  //The second argument is the number of bytes that the radio will take from a variable to be sent.
                                  //Here we used the function “sizeof ()“, which automatically calculates the number of bytes in a “hall” string.

delay(1000);

}
