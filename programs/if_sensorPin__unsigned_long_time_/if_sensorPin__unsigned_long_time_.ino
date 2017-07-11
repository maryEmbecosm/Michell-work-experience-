int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup(){
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(11,OUTPUT);
}

void loop(){
  sensorValue=analogRead(sensorPin);
  if(sensorValue <= 14){
  unsigned long time;
    Serial.print("Time: ");
    time = micros();
    Serial.println(time);
    delayMicroseconds(2000000);
  }
}
  
