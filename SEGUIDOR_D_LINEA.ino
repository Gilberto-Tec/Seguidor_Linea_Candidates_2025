// ------------------ SENSORES INFRARROJOS ------------------
const int sensorIzq = 13;  // Sensor infrarrojo izquierdo
const int sensorDer = 25;  // Sensor infrarrojo derecho

// ------------------ MOTORES ------------------
// Lado derecho (Puente H 1)
int IN1_D1 = 27;
int IN2_D1 = 29;
int IN3_D2 = 31;
int IN4_D2 = 33;
int ENA_D = 4;   // PWM derecho
int ENB_D = 3;

// Lado izquierdo (Puente H 2)
int IN1_I1 = 26;
int IN2_I1 = 28;
int IN3_I2 = 30;
int IN4_I2 = 32;
int ENA_I = 7;   // PWM izquierdo
int ENB_I = 8;

// ------------------ VELOCIDADES ------------------
const int velMax = 200;   // velocidad máxima
const int velGiro = 130;  // velocidad más lenta para giros

void setup() {
  // Sensores
  pinMode(sensorIzq, INPUT);
  pinMode(sensorDer, INPUT);

  // Motores derecho
  pinMode(IN1_D1, OUTPUT);
  pinMode(IN2_D1, OUTPUT);
  pinMode(IN3_D2, OUTPUT);
  pinMode(IN4_D2, OUTPUT);
  pinMode(ENA_D, OUTPUT);
  pinMode(ENB_D, OUTPUT);

  // Motores izquierdo
  pinMode(IN1_I1, OUTPUT);
  pinMode(IN2_I1, OUTPUT);
  pinMode(IN3_I2, OUTPUT);
  pinMode(IN4_I2, OUTPUT);
  pinMode(ENA_I, OUTPUT);
  pinMode(ENB_I, OUTPUT);

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
  // Sensor izquierdo ve negro → girar suave a la izquierda
  else if (valorIzq == LOW && valorDer == HIGH) {
    girarIzquierda();
  }
  // Sensor derecho ve negro → girar suave a la derecha
  else if (valorIzq == HIGH && valorDer == LOW) {
    girarDerecha();
  }
  // Ambos sensores ven negro → detenerse (opcional)
  else {
    detenerMotores();
  }
}

// ------------------ FUNCIONES DE MOVIMIENTO ------------------

void avanzar() {
  // Motores derechos adelante
  digitalWrite(IN1_D1, HIGH);
  digitalWrite(IN2_D1, LOW);
  digitalWrite(IN3_D2, HIGH);
  digitalWrite(IN4_D2, LOW);
  analogWrite(ENA_D, velMax);
  analogWrite(ENB_D, velMax);

  // Motores izquierdos adelante
  digitalWrite(IN1_I1, HIGH);
  digitalWrite(IN2_I1, LOW);
  digitalWrite(IN3_I2, HIGH);
  digitalWrite(IN4_I2, LOW);
  analogWrite(ENA_I, velMax);
  analogWrite(ENB_I, velMax);
}

void girarIzquierda() {
  // Motores derechos adelante rápido
  digitalWrite(IN1_D1, HIGH);
  digitalWrite(IN2_D1, LOW);
  digitalWrite(IN3_D2, HIGH);
  digitalWrite(IN4_D2, LOW);
  analogWrite(ENA_D, velMax);
  analogWrite(ENB_D, velMax);

  // Motores izquierdos más lento
  digitalWrite(IN1_I1, HIGH);
  digitalWrite(IN2_I1, LOW);
  digitalWrite(IN3_I2, HIGH);
  digitalWrite(IN4_I2, LOW);
  analogWrite(ENA_I, velGiro);
  analogWrite(ENB_I, velGiro);
}

void girarDerecha() {
  // Motores izquierdos rápido
  digitalWrite(IN1_I1, HIGH);
  digitalWrite(IN2_I1, LOW);
  digitalWrite(IN3_I2, HIGH);
  digitalWrite(IN4_I2, LOW);
  analogWrite(ENA_I, velMax);
  analogWrite(ENB_I, velMax);

  // Motores derechos más lento
  digitalWrite(IN1_D1, HIGH);
  digitalWrite(IN2_D1, LOW);
  digitalWrite(IN3_D2, HIGH);
  digitalWrite(IN4_D2, LOW);
  analogWrite(ENA_D, velGiro);
  analogWrite(ENB_D, velGiro);
}

void detenerMotores() {
  digitalWrite(IN1_D1, LOW);
  digitalWrite(IN2_D1, LOW);
  digitalWrite(IN3_D2, LOW);
  digitalWrite(IN4_D2, LOW);
  digitalWrite(IN1_I1, LOW);
  digitalWrite(IN2_I1, LOW);
  digitalWrite(IN3_I2, LOW);
  digitalWrite(IN4_I2, LOW);
  analogWrite(ENA_D, 0);
  analogWrite(ENB_D, 0);
  analogWrite(ENA_I, 0);
  analogWrite(ENB_I, 0);
}
