int ledPin = 8;  // Pin where the LED is connected

void setup() {
  Serial.begin(115200);  // Start the serial communication
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  digitalWrite(ledPin, LOW);  // Make sure the LED is off initially
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();  // Read the input from the serial monitor
    input.trim();  // Remove any extra whitespace from the input

    if (input == "on") {
      digitalWrite(ledPin, HIGH);  // Turn on the LED
      Serial.println("LED is ON");
    } 
    else if (input == "off") {
      digitalWrite(ledPin, LOW);  // Turn off the LED
      Serial.println("LED is OFF");
    }
    else {
      Serial.println("Invalid command. Use 'on' or 'off'.");
    }
  }
}
