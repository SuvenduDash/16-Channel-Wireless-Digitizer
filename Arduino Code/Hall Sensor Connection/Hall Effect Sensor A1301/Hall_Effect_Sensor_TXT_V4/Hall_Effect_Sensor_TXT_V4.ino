//Transmitter Part
#include <LiquidCrystal.h>
#include <SPI.h>              //to handle the communication interface with the modem
#include <nRF24L01.h>         //to handle this particular modem driver
#include <RF24.h>             //to control the radio modem



#define HallVolt1 A0           //declear the analog pin A0
#define HallVolt2 A1           //declear the analog pin A1
#define HallVolt3 A2           //declear the analog pin A2
//#define HallVolt4 A3
//#define HallVolt5 A4
//#define HallVolt6 A5


float hall1 = 0.0;
float hall2 = 0.0;
float hall3 = 0.0;
//float hall4 = 0.0;
//float hall5 = 0.0;

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

hall1 = analogRead (HallVolt1);  //read the analog pin 
hall2 = analogRead (HallVolt2);
hall3 = analogRead (HallVolt3);
//hall4 = analogRead (HallVolt4);
//hall5 = analogRead (HallVolt5);

hall1=hall1*5/1023;
hall2=hall2*5/1023;
hall3=hall3*5/1023;
//hall4=hall4*5/1023;
//hall5=hall5*5/1023;

//hall = (hall-2.5)*5/(0.00025*1023);

lcd.setCursor (0,1);
lcd.write("h1");
lcd.print(hall1);
lcd.write("h2");
lcd.print(hall2);
lcd.write("h3");
lcd.print(hall3);
//lcd.write("h4");
//lcd.print(hall4);
//lcd.write("h5");
//lcd.print(hall5);
//lcd.write("h5");

Serial.print("Transmite Hall-1 Effect = "); 
Serial.print(hall1);
Serial.print("Volt");
Serial.print("\t");

Serial.print("Transmite Hall-2 Effect = "); 
Serial.print(hall2);
Serial.print("Volt");
Serial.print("\t");

Serial.print("Transmite Hall-3 Effect = ");
Serial.print(hall3);
Serial.print("Volt");
Serial.print("\t");
Serial.println();
//Serial.print("Transmite Hall-4 Effect = "); 
//Serial.print(hall4);
//Serial.print("Volt");
//Serial.print("\t");

//Serial.print("Transmite Hall-5 Effect = "); 
//Serial.print(hall5);
//Serial.print("Volt");
//Serial.print("\t");
//Serial.println();

radio.write(&hall1, sizeof(hall1)); // we send hall through the radio to the modem (the address of the modem was set up earlier using “openWritingPipe”). 
                                  //First argument is an indication of the variable that stores the data to send. That’s why we used “&” before the variable name, 
                                  //so we can make an indicator from this variable. 
                                  //The second argument is the number of bytes that the radio will take from a variable to be sent.
                                  //Here we used the function “sizeof ()“, which automatically calculates the number of bytes in a “hall” string.
radio.write(&hall2, sizeof(hall2));
radio.write(&hall3, sizeof(hall3));
//radio.write(&hall4, sizeof(hall4));
//radio.write(&hall5, sizeof(hall5));

delay(1000);

}
