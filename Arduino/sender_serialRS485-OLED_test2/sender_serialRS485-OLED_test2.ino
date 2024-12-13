#include <ESP32Servo.h>

#define RS485_DE_RE 33 // Pin for DE & RE
#define RS485_DI_TX0 1 // Pin for DI (TX0)

#define POT1_PIN 25    // Potentiometer 1 connected to GPIO25
#define POT2_PIN 26    // Potentiometer 2 connected to GPIO26
#define SERVO_PIN 12   // Servo PWM connected to GPIO12

Servo servo;           // Servo object to control the servo motor

void setup() {
  pinMode(RS485_DE_RE, OUTPUT);
  digitalWrite(RS485_DE_RE, HIGH); // Enable transmit mode

  // Initialize Serial Communication on UART0
  Serial.begin(9600);

  // Initialize Servo
  servo.attach(SERVO_PIN, 500, 2400); // Attach servo with pulse width range 500-2400 µs

  Serial.println("RS485 Master Initialized");
}

void loop() {
  // Read potentiometer values
  int pot1Value = analogRead(POT1_PIN); // Read potentiometer 1 value
  int pot2Value = analogRead(POT2_PIN); // Read potentiometer 2 value

  // Map potentiometer value to servo angle (0 to 180 degrees)
  int servoAngle = map(pot1Value, 0, 4095, 0, 180);
  servo.write(servoAngle); // Set servo to the mapped angle

  // Prepare data to send
  String dataToSend = String(servoAngle) +
                      "  " + String(pot1Value) +
                      "  " + String(pot2Value);

  // Send data through RS-485
  digitalWrite(RS485_DE_RE, HIGH); // Set RS485 to transmit mode
  Serial.println(dataToSend);      // Send data over UART
  
  delay(700); // Wait for 1 second before sending the next data
}
