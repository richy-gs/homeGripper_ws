// Sender Code
#include <SoftwareSerial.h>
 
// Define the pins for the MAX485
#define DE 0    // Arduino: 5 || ESP: 0
#define RE 4    // Arduino: 6 || ESP: 4

// Create a SoftwareSerial object to communicate with the MAX485
SoftwareSerial RS485Serial(5, 2); // RX, TX   //Arduino: (7, 4) || ESP: (5, 2)
 
void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  RS485Serial.begin(9600);
 
  // Set the DE and RE pins as outputs
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
 
  // Set DE and RE high to enable transmission mode
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
}
 
void loop() {
  // Generate random data
  int data = random(0, 100);
 
  // Send data over RS485
  RS485Serial.write(data);
 
  // Print the sent data to the serial monitor
  Serial.print("Data sent: ");
  Serial.println(data);
 
  // Wait for a while before sending the next data
  delay(2000);
}
