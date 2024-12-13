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
  
  Serial.println("Robot Simulation Started...");
  Serial.println("Bluetooth Master Initialized...");
}

void loop() {
  // Initial simulated velocities
  float linear_velocity = 0.5;  // Linear velocity in m/s
  float angular_velocity = 1.0; // Angular velocity in rad/s
  float step = 0.1;             // Increment for simulation
  String message = "";

  // Simulate increasing velocities
  for (float i = 0.0; i <= 3.0; i += step) {
    // Build the message in the specified format
    message = "linear:" + String(linear_velocity, 2) + ",angular:" + String(angular_velocity, 2);
    
    // Publish the message to both Serial and Bluetooth
    Serial.println(message);
    Bluetooth.println(message);

    // Increment velocities
    linear_velocity += i * 0.2; // Change factor for linear velocity
    angular_velocity += i * 0.05; // Change factor for angular velocity

    // Wait before sending the next message
    delay(900);
  }

  // Simulate decreasing velocities
  for (float i = 3.0; i >= 0.0; i -= step) {
    // Build the message in the specified format
    message = "linear:" + String(linear_velocity, 2) + ",angular:" + String(angular_velocity, 2);
    
    // Publish the message to both Serial and Bluetooth
    Serial.println(message);
    Bluetooth.println(message);

    // Decrement velocities
    linear_velocity -= i * 0.2; // Change factor for linear velocity
    angular_velocity -= i * 0.05; // Change factor for angular velocity

    // Prevent negative values
    linear_velocity = max(0.0, linear_velocity);
    angular_velocity = max(0.0, angular_velocity);

    // Wait before sending the next message
    delay(900);
  }
}
