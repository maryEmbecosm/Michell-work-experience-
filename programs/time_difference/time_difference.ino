#include <LiquidCrystal.h>

unsigned long current;
unsigned long previous;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);                  //select the pins for the lcd
int sensorPin = A0;                                                     //select the input pin for the photoresistor
int sensorValue = 0;                                                    //variable to store the value coming from the sensor
unsigned numberSwings;

void setup(){
  lcd.begin(16,1);                                                      //start the lcd
  pinMode(sensorPin, INPUT);
  pinMode(11, OUTPUT);
  numberSwings = 2;                                                     //the amount of swings of the pendulum wished to be recorded
}

void loop(){
  sensorValue=analogRead(sensorPin);                                    //reads sensor
  //lcd.print(sensorValue);                                             //prints sensor value if required for accurate setup                                         
    if(sensorValue >= 150){                                             //adjust depending on sensorValue
      current = micros();
      unsigned long time = (current - previous);
      unsigned long Time2 = time / numberSwings * 21600;
      unsigned long Time3 = (8.64e10 - Time2);
      unsigned long printTime = Time3 / 1.0e6;
      lcd.clear();
      lcd.print(printTime, 6);    
      delay(4000 * numberSwings - 1000);                                //4000 milliseconds (4 seconds) * numberSwings - 1000 milliseconds (1 second)
      previous = current;
    }
}
