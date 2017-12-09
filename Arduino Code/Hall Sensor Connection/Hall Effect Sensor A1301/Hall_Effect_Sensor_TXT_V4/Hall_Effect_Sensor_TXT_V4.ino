//Transmitter Part
#include <LiquidCrystal.h>
#include <SPI.h>              //to handle the communication interface with the modem
#include <nRF24L01.h>         //to handle this particular modem driver
#include <RF24.h>             //to control the radio modem


#define HallVolt1 A0           //declear the analog pin A0
#define HallVolt2 A1           //declear the analog pin A1
#define HallVolt3 A2           //declear the analog pin A2
#define HallVolt4 A3           //declear the analog pin A3
#define HallVolt5 A4           //declear the analog pin A4
#define HallVolt6 A5           //declear the analog pin A5
#define HallVolt7 A6           //declear the analog pin A6
#define HallVolt8 A7           //declear the analog pin A7
#define HallVolt9 A8           //declear the analog pin A8
#define HallVolt10 A9          //declear the analog pin A9
#define HallVolt11 A10         //declear the analog pin A10
#define HallVolt12 A11         //declear the analog pin A11
#define HallVolt13 A12         //declear the analog pin A12
#define HallVolt14 A13         //declear the analog pin A13
#define HallVolt15 A14         //declear the analog pin A14
#define HallVolt16 A15         //declear the analog pin A15

float hall1[8];
float hall2[8];

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

hall1[0] = analogRead (HallVolt1);  //read the analog pin 
hall1[1] = analogRead (HallVolt2);
hall1[2] = analogRead (HallVolt3);
hall1[3] = analogRead (HallVolt4); 
hall1[4] = analogRead (HallVolt5);
hall1[5] = analogRead (HallVolt6);
hall1[6] = analogRead (HallVolt7);
hall1[7] = analogRead (HallVolt8);
hall2[0] = analogRead (HallVolt9);
hall2[1] = analogRead (HallVolt10);
hall2[2] = analogRead (HallVolt11);
hall2[3] = analogRead (HallVolt12);
hall2[4] = analogRead (HallVolt13);
hall2[5] = analogRead (HallVolt14);
hall2[6] = analogRead (HallVolt15);
hall2[7] = analogRead (HallVolt16);


hall1[0]=hall1[0]*5/1023;
hall1[1]=hall1[1]*5/1023;
hall1[2]=hall1[2]*5/1023;
hall1[3]=hall1[3]*5/1023;
hall1[4]=hall1[4]*5/1023;
hall1[5]=hall1[5]*5/1023;
hall1[6]=hall1[6]*5/1023;
hall1[7]=hall1[7]*5/1023;
hall2[0]=hall2[0]*5/1023;
hall2[1]=hall2[1]*5/1023;
hall2[2]=hall2[2]*5/1023;
hall2[3]=hall2[3]*5/1023;
hall2[4]=hall2[4]*5/1023;
hall2[5]=hall2[5]*5/1023;
hall2[6]=hall2[6]*5/1023;
hall2[7]=hall2[7]*5/1023;

//hall = (hall-2.5)*5/(0.00025*1023);

lcd.setCursor (0,1);
lcd.write("h1");
lcd.print(hall1[0]);
Serial.print("Transmite Hall-1 Effect = "); 
Serial.print(hall1[0]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h2");
lcd.print(hall1[1]);
Serial.print("Transmite Hall-2 Effect = "); 
Serial.print(hall1[1]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h3");
lcd.print(hall1[2]);
Serial.print("Transmite Hall-3 Effect = ");
Serial.print(hall1[2]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h4");
lcd.print(hall1[3]);
Serial.print("Transmite Hall-4 Effect = "); 
Serial.print(hall1[3]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h3");
lcd.print(hall1[4]);
Serial.print("Transmite Hall-5 Effect = "); 
Serial.print(hall1[4]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h4");
lcd.print(hall1[5]);
Serial.print("Transmite Hall-6 Effect = "); 
Serial.print(hall1[5]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h5");
lcd.print(hall1[6]);
Serial.print("Transmite Hall-7 Effect = "); 
Serial.print(hall1[6]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h6");
lcd.print(hall1[7]);
Serial.print("Transmite Hall-8 Effect = "); 
Serial.print(hall1[7]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h7");
lcd.print(hall2[0]);
Serial.print("Transmite Hall-9 Effect = "); 
Serial.print(hall2[0]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h8");
lcd.print(hall2[1]);
Serial.print("Transmite Hall-10 Effect = "); 
Serial.print(hall2[1]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h9");
lcd.print(hall2[2]);
Serial.print("Transmite Hall-11 Effect = "); 
Serial.print(hall2[2]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h10");
lcd.print(hall2[3]);
Serial.print("Transmite Hall-12 Effect = "); 
Serial.print(hall2[3]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h11");
lcd.print(hall2[4]);
Serial.print("Transmite Hall-13 Effect = "); 
Serial.print(hall2[4]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h13");
lcd.print(hall2[5]);
Serial.print("Transmite Hall-14 Effect = "); 
Serial.print(hall2[5]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h14");
lcd.print(hall2[6]);
Serial.print("Transmite Hall-15 Effect = "); 
Serial.print(hall2[6]);
Serial.print("Volt");
Serial.print("\t");

lcd.write("h15");
lcd.print(hall1[7]);
Serial.print("Transmite Hall-16 Effect = "); 
Serial.print(hall2[7]);
Serial.print("Volt");
Serial.print("\t");
Serial.println();

radio.write(&hall1[0], sizeof(hall1));   // we send hall through the radio to the modem (the address of the modem was set up earlier using “openWritingPipe”). 
                                      //First argument is an indication of the variable that stores the data to send. That’s why we used “&” before the variable name, 
                                      //so we can make an indicator from this variable. 
                                      //The second argument is the number of bytes that the radio will take from a variable to be sent.
                                      //Here we used the function “sizeof ()“, which automatically calculates the number of bytes in a “hall” string.
radio.write(&hall2[0], sizeof(hall2));   
delay(1000);

}
