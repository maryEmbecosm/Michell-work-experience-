#include <LiquidCrystal.h>

unsigned long current;
unsigned long previous;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);
int sensorPin = A0;
int sensorValue = 0;

void setup(){
  lcd.begin(16,1);
  pinMode(sensorPin, INPUT);
  pinMode(11, OUTPUT);
}

void loop(){
  sensorValue=analogRead(sensorPin);
    if(sensorValue <= 100){
      current = micros();
      unsigned long time = current - previous;
      lcd.clear();
      lcd.print(time);
      delay(1000);
  }
  previous = current;
}
