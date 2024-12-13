#include <SoftwareSerial.h>
 
// Define the pins for the MAX485
#define DE 5    // Arduino: 5 || ESP: 0
#define RE 6    // Arduino: 6 || ESP: 4

// Create a SoftwareSerial object to communicate with the MAX485
SoftwareSerial RS485Serial(7, 4); // RX, TX   //Arduino: (7, 4) || ESP: (5, 2)
 
void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  RS485Serial.begin(9600);
 
  // Set the DE and RE pins as outputs
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
 
  // Set DE and RE low to enable receiving mode by default
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
 
  Serial.println("Enter data to send or wait to receive:");
}
 
void loop() {
  // Check if data is available in the serial terminal to send
  if (Serial.available()) {
    // Read the data from the serial terminal
    String dataToSend = Serial.readStringUntil('\n');
 
    // Switch to transmission mode
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
 
    // Send the data over RS485
    RS485Serial.println(dataToSend);
 
    // Print the sent data to the serial monitor
    Serial.print("Data sent: ");
    Serial.println(dataToSend);
 
    // Switch back to receiving mode
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
  }
 
  // Check if data is available to receive over RS485
  if (RS485Serial.available()) {
    // Read the received data
    String receivedData = RS485Serial.readStringUntil('\n');
 
    // Print the received data to the serial monitor
    Serial.print("Data received: ");
    Serial.println(receivedData);
 
    // Print a successful message
    Serial.println("Data successfully received.");
  }
}