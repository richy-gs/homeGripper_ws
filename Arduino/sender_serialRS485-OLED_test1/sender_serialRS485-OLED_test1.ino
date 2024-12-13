// sender_serialRS485-OLED_test1

#define RS485_DE_RE 33 // Pin for DE & RE
#define RS485_DI_TX0 1 // Pin for DI (TX0)

void setup() {
  pinMode(RS485_DE_RE, OUTPUT);
  digitalWrite(RS485_DE_RE, HIGH); // Enable transmit mode
  
  // Initialize Serial Communication on UART0
  Serial.begin(9600);

  Serial.println("RS485 Master Initialized");
}

void loop() {
  digitalWrite(RS485_DE_RE, HIGH); // Set RS485 to transmit mode
  
  // Send data through UART0
  for (int i = 0; i < 10; i++) {
    Serial.print("Hello from Message ");
    Serial.println(i);
    delay(1000); // Wait for 1 second
  }
}
