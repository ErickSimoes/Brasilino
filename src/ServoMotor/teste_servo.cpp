/*
  Teste da biblioteca ServoMotor - wrapper brasileira para Servo.h
  
  Este arquivo testa as funcionalidades básicas da classe ServoMotor
  para garantir que está funcionando como wrapper da biblioteca Servo.h
*/

#include "ServoMotor.h"

// Teste simples da biblioteca ServoMotor
void teste_servomotor() {
    ServoMotor servo(9);  // Cria servo conectado ao pino 9
    
    // Testa movimentos básicos
    servo.escreverAngulo(0);    // Move para 0 graus
    delay(1000);
    servo.escreverAngulo(90);   // Move para 90 graus
    delay(1000);
    servo.escreverAngulo(180);  // Move para 180 graus
    delay(1000);
    
    // Testa leitura do ângulo
    int angulo = servo.lerAngulo();
    
    // Testa desconexão
    servo.desconectar();
}

void configurar() {
    // Inicialização do sistema
    Serial.begin(9600);
    Serial.println("Testando biblioteca ServoMotor...");
}

void repetir() {
    teste_servomotor();
    delay(5000);  // Espera 5 segundos antes de repetir
}