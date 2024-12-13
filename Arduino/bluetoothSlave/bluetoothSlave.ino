#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);

  Serial.println("Slave Bluetooth Initialized");
  delay(1000);
}

void loop() {
  // Check for a message from the master
  if (Bluetooth.available()) {
    String received = Bluetooth.readString();
    Serial.println("Received from Master: " + received);
    
    // Respond back to the master
    Bluetooth.println("Hello from Slave!");
    Serial.println("Sent: Hello from Slave!");
  }
  
  delay(500); // Delay for readability
}