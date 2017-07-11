#include <LiquidCrystal.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
boolean curr_state;
boolean prev_state;
unsigned long current;
unsigned long prev;
int num_dataPoints;
unsigned long run_total;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);

void setup(){
  lcd.begin(16,1);
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(11,OUTPUT);
  curr_state = false;
  prev_state = false;
  num_dataPoints = 0;
  run_total = 0;
} 

void loop(){
  sensorValue=analogRead(sensorPin);
  //lcd.print(sensorValue);
  if(sensorValue <= 100)
    curr_state = true;
  else
    curr_state = false;
  if(curr_state != prev_state){
    current = micros();
    unsigned long time = current - prev;
    run_total += time;
    num_dataPoints += 1;
    if(num_dataPoints == 4){
      double real_time;
      real_time = ((double) run_total) / 1.0e6;
      lcd.print(real_time, 6);
      delay(1000);
      lcd.clear();
      num_dataPoints = 0;
      run_total = 0;
    }
    prev_state = curr_state;
    prev = current;
  if(sensorValue <= 100)
    digitalWrite(13,HIGH);
  else
    digitalWrite(13,LOW);
  }
}


