// Pendulum swing timer

// Copyright (C) 2017 Embecosm Limited <www.embecosm.com>

// Contributor: Mitchell Granger

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

//All values are in microseconds unless they end in the suffix "_secs"

#include <LiquidCrystal.h>

unsigned long current;
unsigned long previous;
//Select the pins for the lcd
LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);     
//Select the input pin for the photoresistor
int sensorPin = A0; 
//Variable to store the value coming from the sensor
int sensorValue = 0;                                                    
unsigned long numberSwings;
const double CorrectionFactor = 4.0 / 3.956;
//Amount of swings in a day
int numberSwingsDay = 21600;
//Number of seconds in a day
int secs_per_day = 86400;

void setup(){
//Start the lcd
  lcd.begin(16,1);                                                      
  pinMode(sensorPin, INPUT);
  pinMode(11, OUTPUT);
//The amount of swings of the 
//Pendulum wished to be recorded
  numberSwings = 10;  
}

void loop(){
//Read sensor
  sensorValue=analogRead(sensorPin);                                                                                                                    
//lcd.print(sensorValue);  
//Adjust depending on sensorValue                                                                                                                                                                                                                                                                                                                                  
    if(sensorValue >= 150){      
      current = micros();
//Calculates time of swing in microseconds
      unsigned long time = current - previous;
//Calculates average in seconds
      double printTime_secs = (time / numberSwings / 1.0e6); 
//Calculates the time it will take to do 21600 swings  
      double day_err_secs = printTime_secs * numberSwingsDay;
      day_err_secs = day_err_secs * CorrectionFactor;
      lcd.clear();
//Prints however many seconds fast/slow
//The cock is after 24 hours
      lcd.print(secs_per_day - day_err_secs, 6);
//4000 milliseconds (4 seconds) * numberSwings - 1000 milliseconds (1 second)
      delay(4000 * numberSwings - 1000);                                
      previous = current;
    }
}

