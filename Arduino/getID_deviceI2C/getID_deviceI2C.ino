#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  Serial.println("\nI2C Scanner");
  byte count = 0;
  
  // Escanear las direcciones I2C
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Dispositivo I2C encontrado en la direccion 0x");
      Serial.println(i, HEX);
      count++;
      delay(100); // Retardo para no sobrecargar el bus
    }
  }
  if (count == 0) {
    Serial.println("No se encontraron dispositivos I2C.");
  } else {
    Serial.println("Escaneo completado.");
  }
}

void loop() {
  // El loop no hace nada, el trabajo está en el setup
}
