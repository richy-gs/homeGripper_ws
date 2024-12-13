#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// Definiciones de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset no utilizado
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pines de entrada de los potenciómetros
const int pot1Pin = A0; // Potenciómetro 1 (FSR1)
const int pot2Pin = A1; // Potenciómetro 2 (FSR2)

// Pin del servo
const int servoPin = 9;

// Variables globales
Servo myServo;
int pot1Value = 0;       // Valor del potenciómetro 1
int pot2Value = 0;       // Valor del potenciómetro 2
int servoPosition = 90;  // Posición inicial del servo (90 grados)

// PID variables
float Kp = 1.6;          // Ganancia proporcional
float Ki = 0.5;          // Ganancia integral
float Kd = 0.1;         // Ganancia derivativa
float integral = 0;      // Valor acumulado de la integral
float previousError = 0; // Error previo para cálculo derivativo
unsigned long previousTime = 0; // Tiempo anterior

void setup() {
  // Inicializar pantalla OLED
  if (!display.begin(0x7A, 0x3C)) {
    Serial.println(F("Error al inicializar la pantalla OLED"));
    for (;;); // Detener el programa
  }
  display.clearDisplay();
  display.display();

  // Inicializar servo
  myServo.attach(servoPin);
  myServo.write(servoPosition); // Inicializar a posición media

  // Configurar comunicación serie para depuración
  Serial.begin(9600);
}

void loop() {
  // Leer valores de los potenciómetros
  pot1Value = analogRead(pot1Pin); // FSR1
  pot2Value = analogRead(pot2Pin); // FSR2

  // Calcular el error
  int error = pot1Value - pot2Value;

  // Calcular PID
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - previousTime) / 1000.0; // Tiempo en segundos
  previousTime = currentTime;

  // Proporcional
  float proportional = Kp * error;

  // Integral
  integral += error * deltaTime;
  float integralTerm = Ki * integral;

  // Derivativo
  float derivative = (error - previousError) / deltaTime;
  float derivativeTerm = Kd * derivative;

  // Salida PID
  float pidOutput = proportional + integralTerm + derivativeTerm;

  // Actualizar posición del servo
  servoPosition = constrain(servoPosition + pidOutput, 0, 180);
  myServo.write(servoPosition);

  // Guardar error previo
  previousError = error;

  // Mostrar datos en la pantalla OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Pot1: ");
  display.println(pot1Value);

  display.setCursor(0, 10);
  display.print("Pot2: ");
  display.println(pot2Value);

  display.setCursor(0, 20);
  display.print("Error: ");
  display.println(error);

  display.setCursor(0, 30);
  display.print("Servo Pos: ");
  display.println(servoPosition);

  display.setCursor(0, 40);
  display.print("PID Out: ");
  display.println(pidOutput);

  display.display();

  // Enviar datos a la consola serie
  Serial.print("Pot1: ");
  Serial.print(pot1Value);
  Serial.print(" Pot2: ");
  Serial.print(pot2Value);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print(" Servo Pos: ");
  Serial.print(servoPosition);
  Serial.print(" PID Out: ");
  Serial.println(pidOutput);

  // Esperar un poco antes de la siguiente iteración
  delay(50); // 50ms delay (~20Hz frecuencia de control)
}
