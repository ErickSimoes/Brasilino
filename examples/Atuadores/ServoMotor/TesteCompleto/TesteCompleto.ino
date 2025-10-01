/*
  Teste da ServoMotor - Biblioteca Brasilino
  
  Este sketch testa a funcionalidade da classe ServoMotor
  que foi criada como wrapper para a biblioteca Servo.h
  
  Criado por: Erick Simões (2025)
  
  Para usar:
  1. Conecte um servo no pino 9
  2. Carregue este código no Arduino
  3. Observe o servo fazendo movimentos de varredura
*/

#include <Brasilino.h>

ServoMotor meuServo;  // Cria objeto ServoMotor

funcao configurar() {
  iniciarSerial(9600);
  escreverSerialnl("Iniciando teste da biblioteca ServoMotor...");
  
  meuServo.conectar(9);  // Conecta o servo ao pino 9
  escreverSerialnl("ServoMotor conectado ao pino 9");
  
  meuServo.escreverAngulo(90);  // Posição inicial (centro)
  escreverSerialnl("Servo posicionado em 90 graus");
  esperar(1);
}

funcao repetir() {
  escreverSerialnl("Iniciando movimento de varredura...");
  
  // Move de 0 a 180 graus
  para (inteiro angulo = 0; angulo <= 180; angulo += 10) {
    meuServo.escreverAngulo(angulo);
    escreverSerial("Angulo: ");
    escreverSerial(angulo);
    escreverSerial(" - Leitura: ");
    escreverSerialnl(meuServo.lerAngulo());
    esperarMili(500);
  }
  
  esperar(1);
  
  // Move de 180 a 0 graus
  para (inteiro angulo = 180; angulo >= 0; angulo -= 10) {
    meuServo.escreverAngulo(angulo);
    escreverSerial("Angulo: ");
    escreverSerial(angulo);
    escreverSerial(" - Leitura: ");
    escreverSerialnl(meuServo.lerAngulo());
    esperarMili(500);
  }
  
  esperar(2);
}