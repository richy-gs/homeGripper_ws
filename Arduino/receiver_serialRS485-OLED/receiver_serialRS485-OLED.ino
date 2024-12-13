#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin (set to -1 if sharing Arduino reset pin)
#define RS485_DE_RE 33   // Pin for DE & RE
#define RS485_RO_RX0 3   // RS-485 RO is RX0 (GPIO3)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(RS485_DE_RE, OUTPUT);
  digitalWrite(RS485_DE_RE, LOW); // Enable receive mode
  delay(1);

  // Initialize Serial Communication
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_PAGEADDR, 0x3D)) { // Check if OLED is at address 0x3C
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("RS485 Receiver xD");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  digitalWrite(RS485_DE_RE, LOW); // Enable receive mode

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello World xD");
  display.display();
  delay(500);
  
  if (Serial.available()) {
    // Display the received data on the OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("PreData LOL");
    display.display();
    delay(100);

    String receivedData = Serial.readString();
    receivedData.trim();  // Remove any extra whitespace from the input

    // Display the received data on the OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Received Data:");
    display.println(receivedData);
    display.display();
    // Print received data to serial monitor for debugging
    Serial.println("Data received: " + receivedData);
    delay(500);
  } else {
    // Display the received data on the OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Received Data Failed");
    display.display();
    delay(500);
  }

}
