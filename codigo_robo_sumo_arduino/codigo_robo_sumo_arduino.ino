//Programa: Robô sumô
//Autor: Alex
//Versão: 1.2

//********************Inclusão das bibliotecas**************

#include <AFMotor.h>      // Biblioteca do motor shield
#include <Ultrasonic.h>   // Biblioteca do sensor ultrassônico

//********************Definição dos pinos********************

#define sensor1 A5  // Sensor frontal esquerdo
#define sensor2 A4  // Sensor traseiro esquerdo
#define sensor3 A3  // Sensor traseiro direito
#define echo   A2   // Pino de eco do ultrassônico
#define trigger A1  // Pino de trigger do ultrassônico

//********************Criação dos objetos********************

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Ultrasonic ultrasonic(trigger, echo);

//********************Função de configuração******************

void setup() {
  // Configuração de velocidade dos motores
  motor1.setSpeed(255); // Velocidade máxima
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  Serial.begin(9600);  // Habilita a comunicação serial
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
}

//********************Função principal********************

void loop() {
  // Leitura do sensor ultrassônico
  long microsec = ultrasonic.timing();
  float distancia = ultrasonic.convert(microsec, Ultrasonic::CM);

  // Leitura dos sensores reflexivos
  int leituraSensor1 = digitalRead(sensor1);
  int leituraSensor2 = digitalRead(sensor2);
  int leituraSensor3 = digitalRead(sensor3);

  // Exibe leituras no monitor serial
  Serial.print("Distância: ");
  Serial.println(distancia);
  Serial.print("Sensor1 (frontal): ");
  Serial.println(leituraSensor1);
  Serial.print("Sensor2 (traseiro esquerdo): ");
  Serial.println(leituraSensor2);
  Serial.print("Sensor3 (traseiro direito): ");
  Serial.println(leituraSensor3);

  // Caso não detecte oponente e esteja seguro na arena
  if (distancia > 20 && leituraSensor1 == 0 && leituraSensor2 == 0 && leituraSensor3 == 0) {
    Serial.println("Procurando oponente...");
    procura(); // Função otimizada para busca
  } 
  // Caso detecte oponente à frente
  else if (distancia <= 20 && distancia > 0 && leituraSensor1 == 0) {
    Serial.println("Oponente encontrado!");
    frente(); // Avança para empurrar o oponente
  } 
  // Lógica para bordas
  else if (leituraSensor1 == 1 && leituraSensor3 == 0) { // Apenas Sensor 1 detecta borda
    Serial.println("Borda detectada à frente esquerda!");
    tras();
    delay(500);
    direita();
    delay(300);
  } 
  else if (leituraSensor3 == 1 && leituraSensor1 == 0) { // Apenas Sensor 3 detecta borda
    Serial.println("Borda detectada à frente direita!");
    tras();
    delay(500);
    esquerda();
    delay(300);
  } 
  else if (leituraSensor1 == 1 && leituraSensor3 == 1) { // Ambos detectam borda
    Serial.println("Borda detectada em ambos os lados!");
    tras();
    delay(500);
  } 
  // Caso detecte borda atrás
  else if (leituraSensor2 == 1) {
    Serial.println("Borda detectada atrás!");
    frente();
    delay(500);
  }
}

//********************Movimenta o robô para frente********************

void tras() {
  motor1.run(FORWARD);  // Motor traseiro esquerdo
  motor2.run(FORWARD);  // Motor dianteiro esquerdo
  motor3.run(FORWARD);  // Motor dianteiro direito
  motor4.run(FORWARD);  // Motor traseiro direito
}

//********************Movimenta o robô para trás********************

void frente() {
  motor1.run(BACKWARD);  // Motor traseiro esquerdo
  motor2.run(BACKWARD);  // Motor dianteiro esquerdo
  motor3.run(BACKWARD);  // Motor dianteiro direito
  motor4.run(BACKWARD);  // Motor traseiro direito
}

//********************Parada dos motores********************

void parada() {
  motor1.run(RELEASE);  // Motor traseiro esquerdo
  motor2.run(RELEASE);  // Motor dianteiro esquerdo
  motor3.run(RELEASE);  // Motor dianteiro direito
  motor4.run(RELEASE);  // Motor traseiro direito
}

//********************Movimenta o robô para esquerda********************

void esquerda() {
  motor1.run(FORWARD);   // Motor traseiro esquerdo
  motor2.run(FORWARD);   // Motor dianteiro esquerdo
  motor3.run(BACKWARD);  // Motor dianteiro direito
  motor4.run(BACKWARD);  // Motor traseiro direito
}

//********************Movimenta o robô para direita********************

void direita() {
  motor1.run(BACKWARD);  // Motor traseiro esquerdo
  motor2.run(BACKWARD);  // Motor dianteiro esquerdo
  motor3.run(FORWARD);   // Motor dianteiro direito
  motor4.run(FORWARD);   // Motor traseiro direito
}

//********************Busca otimizada para oponente********************

void procura() {
  // Movimento em busca do oponente
  esquerda();  // Gira para a esquerda
  delay(300);
  frente();    // Avança levemente
  delay(400);
  parada();    // Pausa para análise
  delay(100);
}
