//LM35 Connection V 1
// Display the Temp in LCD
#include <LiquidCrystal.h>
#define TempPin A0

float temp = 0.00;
LiquidCrystal lcd(7,8,9,10,11,12);
int tempPin = 0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.write("TEMPRATURE: ");
}

void loop()
{
  temp = analogRead(TempPin);
  temp = temp * 0.48828125;
  Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(1000);
}
