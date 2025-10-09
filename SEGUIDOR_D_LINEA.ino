const int sensorIzq  = 2; 
const int sensorDer  = 3;

// Pines PWM para motores
const int motorIzqAd = 9;
const int motorIzqBack = 10;
const int motorDereAd = 11;
const int motorDereBack = 12;

// Velocidades PWM (0-255)
const int velMax = 255;      // velocidad máxima
const int velGiro = 150;     // velocidad más lenta para giros suaves

void setup() {
  pinMode(sensorIzq, INPUT);
  pinMode(sensorDer, INPUT);

  pinMode(motorIzqAd, OUTPUT);
  pinMode(motorIzqBack, OUTPUT);
  pinMode(motorDereAd, OUTPUT);
  pinMode(motorDereBack, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int valorIzq = digitalRead(sensorIzq);
  int valorDer = digitalRead(sensorDer);

  Serial.print("Izq: "); Serial.print(valorIzq);
  Serial.print("  Der: "); Serial.println(valorDer);

  // Ambos sensores ven blanco → avanzar recto
  if (valorIzq == HIGH && valorDer == HIGH) {
    avanzar();
  }
  // Sensor izquierdo ve negro → giro suave izquierda
  else if (valorIzq == LOW && valorDer == HIGH) {
    girarIzquierda();
  }
  // Sensor derecho ve negro → giro suave derecha
  else if (valorIzq == HIGH && valorDer == LOW) {
    girarDerecha();
  }
  // Ambos sensores ven negro → avanzar recto (suave)
  else if (valorIzq == LOW && valorDer == LOW) {
    avanzar();
  }
}

// === Funciones de movimiento con PWM ===

void avanzar() {
  analogWrite(motorIzqAd, velMax);
  digitalWrite(motorIzqBack, LOW);
  analogWrite(motorDereAd, velMax);
  digitalWrite(motorDereBack, LOW);
}

void girarIzquierda() {
  analogWrite(motorIzqAd, velGiro);  // izquierdo más lento
  digitalWrite(motorIzqBack, LOW);
  analogWrite(motorDereAd, velMax);  // derecho rápido
  digitalWrite(motorDereBack, LOW);
}

void girarDerecha() {
  analogWrite(motorIzqAd, velMax);   // izquierdo rápido
  digitalWrite(motorIzqBack, LOW);
  analogWrite(motorDereAd, velGiro); // derecho más lento
  digitalWrite(motorDereBack, LOW);
}
