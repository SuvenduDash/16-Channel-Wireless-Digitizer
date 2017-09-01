#include <LiquidCrystal.h>                //Include the library of the LCD
#define LDRpin A0                         // pin where we connected the LDR and the resistor

int LDRValue = 0;                         // result of reading the analog pin
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12); // initialize the library with the numbers of the interface pins

void setup() {

pinMode (4, OUTPUT);                    //Pin connected to the LED 
Serial.begin(9600);                     // sets serial port for communication


lcd.begin(16, 2);                       // set up the LCD's number of columns and rows:
lcd.setCursor(1,0);
lcd.write("LIGHT DENSITY: ");                    // Print a message to the LCD.
}

void loop() {
LDRValue = analogRead(LDRpin);        // read the value from the LDR

if(LDRValue >= 200){
  digitalWrite (4, HIGH);             // Turn OFF LED
  Serial.print ("High Density Light -> ");
  lcd.setCursor(0,1);
  lcd.print (LDRValue);
}
else if (LDRValue >= 70) {
  digitalWrite (4, HIGH);            // Turn OFF LED
  Serial.print ("Normal Density Light -> ");
  lcd.setCursor(0,1);
  lcd.print (LDRValue);
}
else if ( LDRValue < 70){
  digitalWrite (4, LOW);            // Turn ON LED
  Serial.print ("Low Density Light -> ");
  lcd.setCursor(0,1);
  lcd.print (LDRValue);
}

Serial.println(LDRValue);           // print the value to the serial port
delay(1000);                        // wait a little
}
