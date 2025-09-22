//Place where are the pines
const int sensorIzq  = 2; 
const int sensorDer = 3;
const int motorIzqAd = 9;
const int motorIzqback = 10;
const int motorDereAd = 11;
const int motorDereBack = 12;

void setup() {
  // put your setup code here, to run once:
pinMode(sensorIzq, INPUT);
pinMode(sensorDer,INPUT);
pinMode(motorIzqAd,OUTPUT);
pinMode(motorIzqback,OUTPUT);
pinMode(motorDereAd,OUTPUT);
pinMode(motorDereBack,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int valor1 = 0;
  int valor2 = 0;
  valor1 = digitalRead(sensorIzq);
  valor2 = digitalRead(sensorDer);
  //Los 2 sensores estan sobre la linea y no detectan nada blanco
  if(valor1 == LOW && valor2 == LOW)
  {
    avanzar();
  }
  //Solo el izquierdo esta sobre la linea
  if(valor1 ==LOW && valor2 ==HIGH)
  {
    girarIzquierda();
  }
  //Caso donde solo el derecho esta sobre la linea 
  if(valor1==HIGH && valor2 ==LOW)
  {
    girarDerecha();
  }
  //Ningun sensor esta sobre la linea negra
 if(valor1 == HIGH && valor2 == HIGH)
 {
  detener();
 }
 
}
//Creacion de funciones 
//Funcion para avanzar y nomas 
void avanzar()
{
  digitalWrite(motorIzqAd,HIGH);
  digitalWrite(motorIzqBack,LOW);
  digitalWrite(motorDereAd,HIGH);
  digitalWrite(motorDereBack,LOW);
}
//Funcion para girar derecha
void girarDerecha()
{
  digitalWrite(motorIzqAd,HIGH);
  digitalWrite(motorIzqBack,LOW);
  digitalWrite(motorDereAd,LOW);
  digitalWrite(motorDereBack,LOW);
}
//Funcion para girar izquierda
void girarIzquierda()
{
  digitalWrite(motorIzqAd,LOW);
  digitalWrite(motorIzqBack,LOW);
  digitalWrite(motorDereAd,HIGH);
  digitalWrite(motorDereBack,LOW); 
}
void detener()
{
  digitalWrite(motorIzqAd,LOW);
  digitalWrite(motorIzqBack,LOW);
  digitalWrite(motorDereAd,LOW);
  digitalWrite(motorDereBack,LOW);
}
