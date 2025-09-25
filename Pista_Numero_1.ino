#include <Servo.h>

// --- Pines Motores  ---
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

// --- Pines Ultrasonicos ---
#define TRIG_FRONT 2
#define ECHO_FRONT 3
#define TRIG_LEFT 4
#define ECHO_LEFT 7
#define TRIG_RIGHT 12
#define ECHO_RIGHT 13

#define TRIG_BALL A0
#define ECHO_BALL A1

// --- Servo ---
Servo servoPinza;
#define SERVO_PIN  A2

// --- Sensor RGB TCS3200 ---
#define S0 A3
#define S1 A4
#define S2 A5
#define S3 A6
#define OUT A7

// --- Variables ---
bool hasBall = false;
String lastFlag = "";

// ---------------- FUNCIONES ----------------

// Medir distancia ultrasónica
long readUltrasonic(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long dur = pulseIn(echo, HIGH, 20000); // máx 
  long dist = dur * 0.034 / 2;
  return dist;
}

// Control Motores
void adelante(int vel = 150) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void atras(int vel = 150) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void derecha(int vel = 150) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void izquierda(int vel = 150) {
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void parar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// Servo
void agarrarPelota() {
  servoPinza.write(0);   // cerrar pinza
  delay(1000);
  hasBall = true;
}
void soltarPelota() {
  servoPinza.write(90);  // abrir pinza
  delay(1000);
  hasBall = false;
}

// --- Sensor RGB TCS3200 ---
int getColorFrequency(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  return pulseIn(OUT, LOW);
}

String detectarColor() {
  int red, green, blue;

  // Leer Rojo
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(OUT, LOW);

  // Leer Azul
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(OUT, LOW);

  // Leer Verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(OUT, LOW);

  Serial.print("R: "); Serial.print(red);
  Serial.print(" G: "); Serial.print(green);
  Serial.print(" B: "); Serial.println(blue);

  // ----- AJUSTAR ESTOS VALORES -----
  if (blue < red && blue < green) return "CELESTE";
  if (red < blue && green < blue) return "AMARILLO";
  if (red < 300 && green < 300 && blue > 400) return "ROJO";
  // --------------------------------------------
  
  return "DESCONOCIDO";
}

// ----------------- SETUP -----------------
void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  pinMode(TRIG_FRONT, OUTPUT); pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_BALL, OUTPUT);  pinMode(ECHO_BALL, INPUT);

  // TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  digitalWrite(S0, HIGH); // Escalado máximo frecuencia
  digitalWrite(S1, HIGH);

  servoPinza.attach(SERVO_PIN);
  servoPinza.write(90); // pinza abierta
  delay(1000);
}

// ----------------- LOOP -----------------
void loop() {
  // 1. Buscar pelota al inicio
  if (!hasBall) {
    long dBall = readUltrasonic(TRIG_BALL, ECHO_BALL);
    if (dBall < 10) {
      agarrarPelota();
    } else {
      adelante(100);
    }
  }

  // 2. Avanzar y evitar paredes
  long dFront = readUltrasonic(TRIG_FRONT, ECHO_FRONT);
  if (dFront < 15) {
    parar();
    long dL = readUltrasonic(TRIG_LEFT, ECHO_LEFT);
    long dR = readUltrasonic(TRIG_RIGHT, ECHO_RIGHT);
    if (dR > dL) {
      derecha(); delay(500);
    } else {
      izquierda(); delay(500);
    }
  }

  // 3. Detectar colores de banderas
  String color = detectarColor();
  if (color == "CELESTE" && hasBall) {
    parar();
    soltarPelota();
    lastFlag = "CELESTE";
    delay(1000);
  }
  else if (color == "AMARILLO" && hasBall) {
    parar();
    adelante(200); delay(1500); // empujar fuerte
    parar();
    lastFlag = "AMARILLO";
    delay(1000);
  }
  else if (color == "ROJO") {
    parar();
    // Acción bonus:
    if (lastFlag == "CELESTE") {
      adelante(200); delay(1500); parar(); // kick
    } else if (lastFlag == "AMARILLO") {
      soltarPelota();
    }
    while (1); // detener programa
  }

  adelante(120); // default avanzar
}
