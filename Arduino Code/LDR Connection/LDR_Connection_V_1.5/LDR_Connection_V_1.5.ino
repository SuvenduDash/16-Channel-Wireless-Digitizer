#define LDRpin A0             // pin where we connected the LDR and the resistor
int LDRValue = 0;             // result of reading the analog pin

void setup() {
Serial.begin(9600);           // sets serial port for communication
}

void loop() {
LDRValue = analogRead(LDRpin); // read the value from the LDR

if(LDRValue >= 200){
  Serial.print ("High Density Light -> ");
}
else if (LDRValue >= 70) {
  Serial.print ("Normal Density Light -> ");
}
else if ( LDRValue < 70){
  Serial.print ("Low Density Light -> ");
}

Serial.println(LDRValue);      // print the value to the serial port
delay(1000);                   // wait a little
}
