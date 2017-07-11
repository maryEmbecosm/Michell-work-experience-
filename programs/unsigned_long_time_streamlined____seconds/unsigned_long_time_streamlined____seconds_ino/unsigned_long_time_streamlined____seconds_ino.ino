// Pendulum swing timer

// Copyright (C) 2017 Embecosm Limited <www.embecosm.com>

// Contributor: Mitchell Granger

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


// All times are in whole numbers of microseconds, unless the variable has the suffix _secs,
// in which case the time is in seconds and is floating point.

#include <LiquidCrystal.h>

const unsigned CUTOFF = 115;                   // >= this value, sensor is off
const unsigned MAX_SWINGS = 200;                // Number of swings to average
const unsigned PRINT_FREQ = 10;                 // How often to print data
const double SWINGS_PER_DAY = 21600.0;          //number of swings of pendulum in 24 hours
const double SECS_PER_DAY = 86400.0;               //number of seconds in a day
const double CORRECTION_FACTOR = 4.0 / 3.956;      //to increase accuracy


LiquidCrystal lcd(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2);     //select the pins for the lcd
int sensorPin = A0;                                        //select the input for the photoresistor
int ledPin = 1;

unsigned long prev_time;      // Start of previous swing

enum state {
  ON,
  OFF
};

enum state prev_state;       // Previous state of pendulum

int  change_count;           // Expect 4 changes per swing

int  next_res;               // Index in swing_times of next result
int  num_valid;              // Number of valid data points

unsigned long swing_times [MAX_SWINGS];

void setup() {
  lcd.begin(16,1);                                                                   //start the lcd                                                
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);                   // Start the LED
  
  prev_time = micros ();
  
  if (analogRead(sensorPin) >= CUTOFF) {
    prev_state = OFF;
    digitalWrite (ledPin, LOW);
  }
  else {
    prev_state = ON;  
    digitalWrite (ledPin, HIGH);
  }
    
  change_count = 0;
  next_res = 0;
  num_valid = 0;
  
  lcd.clear ();
  lcd.print ("Wait...");
}

void loop() {
  
  // Record our current state
  
  enum state curr_state;

  if (analogRead(sensorPin) >= CUTOFF) {
    curr_state = OFF;
    digitalWrite (ledPin, HIGH);
  }
  else
  {
    curr_state = ON;  
    digitalWrite (ledPin, LOW);
  }
  
  // We are only interested when the state has changed, which should happen
  // 4 times per swing.

  if (curr_state != prev_state) {

    prev_state = curr_state;      // Ready for next change
    change_count = change_count + 1;
    
    if (change_count == 4) {
      change_count = 0;         // Ready for next time
      
      // We have completed one full swing
 
      unsigned long curr_time = micros ();
      swing_times[next_res] = curr_time - prev_time;
      prev_time = curr_time;
      next_res = (next_res + 1) % MAX_SWINGS;

      if (num_valid < MAX_SWINGS)
        num_valid = num_valid + 1;

      // Only print out sometimes
      
      if (0 == (next_res % PRINT_FREQ)) {
      
        // Work out average of the MAX_SWINGS times
      
        unsigned long tot = 0;
      
        for (int i = 0; i < num_valid; i++)
          tot = tot + swing_times[i];
          
        // Work out the error in one day of swings
  
        double swing_time_secs = ((double) (tot / num_valid)) / 1.0e6;
        double dayEst = swing_time_secs * SWINGS_PER_DAY * CORRECTION_FACTOR;
        double dayErr = SECS_PER_DAY - dayEst;

        lcd.clear ();
        lcd.print (dayErr, 6);
      }
    }
  }
}


