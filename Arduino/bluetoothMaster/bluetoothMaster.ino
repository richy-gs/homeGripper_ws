#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);

  Serial.println("Master Bluetooth Initialized");
  delay(1000);
}

void loop() {
  Bluetooth.println("Hello from Master!"); // Send message to slave
  Serial.println("Sent: Hello from Master!");
  
  // Check for a response from the slave
  if (Bluetooth.available()) {
    String received = Bluetooth.readString();
    Serial.println("Received from Slave: " + received);
  }
  
  delay(2000); // Delay for readability
}
