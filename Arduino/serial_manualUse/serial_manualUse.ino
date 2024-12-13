void setup() {
  // Inicializa la comunicación serial
  Serial.begin(115200);
  
  // Espera a que el puerto serial esté listo
  while (!Serial) {
    ; // Espera activa
  }
  
  Serial.println("Robot Simulation Started...");
}

void loop() {
  // Velocidades iniciales simuladas
  float linear_velocity = 0.5;  // Velocidad lineal en m/s
  float angular_velocity = 1.0; // Velocidad angular en rad/s
  float step = 0.1;             // Incremento para la simulación
  String message = "";

  // Simulación de incremento de velocidades
  for (float i = 0.0; i <= 3.0; i += step) {
    // Construye el mensaje en el formato especificado
    message = "linear:" + String(linear_velocity, 2) + ",angular:" + String(angular_velocity, 2);
    
    // Publica el mensaje en el puerto serial
    Serial.println(message);

    // Incrementa las velocidades
    linear_velocity += i * 0.2; // Factor de cambio para la velocidad lineal
    angular_velocity += i * 0.05; // Factor de cambio para la velocidad angular

    // Espera antes de enviar el siguiente mensaje
    delay(700);
  }

  // Simulación de decremento de velocidades
  for (float i = 3.0; i >= 0.0; i -= step) {
    // Construye el mensaje en el formato especificado
    message = "linear:" + String(linear_velocity, 2) + ",angular:" + String(angular_velocity, 2);
    
    // Publica el mensaje en el puerto serial
    Serial.println(message);

    // Decrementa las velocidades
    linear_velocity -= i * 0.2; // Factor de cambio para la velocidad lineal
    angular_velocity -= i * 0.05; // Factor de cambio para la velocidad angular

    // Evita valores negativos
    linear_velocity = max(0.0, linear_velocity);
    angular_velocity = max(0.0, angular_velocity);

    // Espera antes de enviar el siguiente mensaje
    delay(700);
  }
}
