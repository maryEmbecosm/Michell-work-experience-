#include <LiquidCrystal.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);

void setup(){
  lcd.begin(16,1);
  pinMode(sensorPin, INPUT);
  pinMode(11,OUTPUT);
}

/*void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}*/
void loop(){
  sensorValue=analogRead(sensorPin);
  lcd.clear();
  lcd.print(sensorValue);
  delay(1000);
}
