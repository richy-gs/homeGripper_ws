#include <Servo.h>

Servo myservo;  // create Servo object to control a servo

//int potpin = A0;  // analog pin used to connect the potentiometer
//int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
}

void loop() {
  //val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  //val = map(val, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  myservo.write(170);       // (10, 170)
  delay(15);                           // waits for the servo to get there
}
