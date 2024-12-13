#include <SoftwareSerial.h>

// Define RX and TX pins for HC-05
SoftwareSerial Bluetooth(10, 11); // RX, TX

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize Bluetooth communication
  Bluetooth.begin(9600);

  // Wait for the serial port to be ready
  while (!Serial) {
    ; // Wait
  }

  Serial.println("Bluetooth Slave Initialized...");
}

void loop() {
  // Procesar datos si están disponibles
  if (Bluetooth.available()) {
    String message = Bluetooth.readStringUntil('\n'); // Leer hasta el terminador '\n'
    Serial.println(message);
  }
  delay(300);
}
