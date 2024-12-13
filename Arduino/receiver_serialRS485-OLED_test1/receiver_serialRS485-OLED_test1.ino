#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin (set to -1 if sharing Arduino reset pin)
#define RS485_DE_RE 33   // Pin for DE & RE
#define RS485_RO_RX0 3   // RS-485 RO is RX0 (GPIO3)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String displayBuffer = "";  // Buffer for OLED display (up to 5 lines max)
int maxLines = 5;           // Maximum lines to display on OLED
String lineBuffer = "";     // Temporary buffer for assembling a single line

unsigned long lastUpdate = 0; // Timestamp of the last display update
unsigned long updateInterval = 1000; // Interval between updates (1 second)

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
  display.println("RS485 Receiver Ready");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void updateDisplay(String newLine) {
  // Add the new line to the display buffer
  displayBuffer += newLine + "\n";

  // Count lines in the buffer
  int lineCount = 0;
  for (int i = 0; i < displayBuffer.length(); i++) {
    if (displayBuffer[i] == '\n') lineCount++;
  }

  // If buffer exceeds max lines, remove the oldest line
  while (lineCount > maxLines) {
    int firstLineEnd = displayBuffer.indexOf('\n');
    displayBuffer = displayBuffer.substring(firstLineEnd + 1);
    lineCount--;
  }

  // Update OLED only if the interval has passed
  if (millis() - lastUpdate >= updateInterval) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(displayBuffer);
    display.display();
    lastUpdate = millis(); // Update the timestamp
  }
}

void loop() {
  // Check if data is available on the serial port
  while (Serial.available()) {
    char incomingChar = Serial.read(); // Read one character at a time
    if (incomingChar == '\n') {        // End of message detected
      lineBuffer.trim();               // Remove extra whitespace
      if (lineBuffer.length() > 0) {
        updateDisplay(lineBuffer);     // Add line to OLED display
        Serial.println("Data: " + lineBuffer); // Debug: Print received data
        lineBuffer = "";               // Clear the line buffer
      }
    } else {
      lineBuffer += incomingChar;      // Append character to the line buffer
    }
  }

  // Optional: Display a waiting message when no data is received
  if (displayBuffer == "" && millis() - lastUpdate >= updateInterval) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Waiting for Data...");
    display.display();
    lastUpdate = millis();
  }
}
