#include <AFMotor.h> // Biblioteca para controlar os motores

AF_DCMotor fr(1);
AF_DCMotor br(2);
AF_DCMotor fl(3);
AF_DCMotor bl(4);


//Variaveis do sonar
int trig = A5;
int echo = A4;
int cm;
bool poweron = false;


void setup() {
  Serial.begin(9600);
  liberar();
  dist();
}

void loop() {

  dist();

  if (cm < 6) {
    poweron = !poweron;
    Serial.print("On: ");
    Serial.println(poweron);
    delay(1000);
  }

  if (poweron){
    if (cm <= 15) {
      liberar();
      Serial.println("Afastar");
      Serial.println(cm);

      afastar();
      liberar();
      direita();
      delay(700);
      
      while (cm <= 15) {
        dist();
      }
    }

    else {
      liberar();
      Serial.println("Frente");
      Serial.println(cm);

      frente();

      while (cm > 15) {
        dist();
      }
    }
  }
}


void liberar() {
  //Liberar motores
  fl.setSpeed(0);
  fl.run(RELEASE);

  fr.setSpeed(0);
  fr.run(RELEASE);

  bl.setSpeed(0);
  bl.run(RELEASE);

  br.setSpeed(0);
  br.run(RELEASE);

  delay(200);

}

void dist() { //Sonar
  long duration;

  delayMicroseconds(2);
  analogWrite(trig, 0);
  delayMicroseconds(2);

  analogWrite(trig, 255);
  delayMicroseconds(10);

  analogWrite(trig, 0);

  duration = pulseIn(echo, 255);
  cm = (duration/57);
  Serial.println(cm);

}


void frente() {
  fl.setSpeed(255);
  fl.run(FORWARD);

  fr.setSpeed(255);
  fr.run(FORWARD);

  bl.setSpeed(255);
  bl.run(FORWARD);

  br.setSpeed(255);
  br.run(FORWARD);
}

void direita() {

  fl.setSpeed(255);
  fl.run(FORWARD);

  fr.setSpeed(255);
  fr.run(BACKWARD);

  bl.setSpeed(255);
  bl.run(FORWARD);

  br.setSpeed(255);
  br.run(BACKWARD);

}

void afastar() {

  fl.setSpeed(255);
  fl.run(BACKWARD);
  
  bl.setSpeed(255);
  bl.run(BACKWARD);

  fr.setSpeed(255);
  fr.run(BACKWARD);

  br.setSpeed(255);
  br.run(BACKWARD);

  delay(300);

}
