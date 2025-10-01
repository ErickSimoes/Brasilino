/*
  Exemplo Avançado - ServoMotor Brasilino
  
  Este exemplo demonstra recursos avançados da biblioteca ServoMotor:
  - Controle de múltiplos servos
  - Movimentos sincronizados
  - Controle via Serial
  
  Conexões:
  - Servo 1: Pino 9
  - Servo 2: Pino 10
  
  Comandos via Serial:
  - "0-180" - Move servo 1 para ângulo especificado
  - "s0-180" - Move servo 2 para ângulo especificado  
  - "sync" - Movimento sincronizado
  - "home" - Volta ambos para posição inicial (90°)
  
  Criado por: Erick Simões (2025)
*/

#include <Brasilino.h>

ServoMotor servo1(9);   // Servo 1 no pino 9
ServoMotor servo2(10);  // Servo 2 no pino 10

String comando = "";
logico comandoCompleto = falso;

funcao configurar() {
  iniciarSerial(9600);
  escreverSerialnl("=== Exemplo Avançado ServoMotor ===");
  escreverSerialnl("Comandos disponíveis:");
  escreverSerialnl("- 0-180: Move servo 1");
  escreverSerialnl("- s0-180: Move servo 2"); 
  escreverSerialnl("- sync: Movimento sincronizado");
  escreverSerialnl("- home: Posição inicial");
  escreverSerialnl("- test: Teste completo");
  escreverSerialnl("============================");
  
  // Posição inicial
  servo1.escreverAngulo(90);
  servo2.escreverAngulo(90);
  esperar(1);
  
  escreverSerialnl("Servos prontos!");
}

funcao repetir() {
  // Processa comandos da serial
  se (Serial.available()) {
    caractere c = Serial.read();
    se (c == '\n') {
      comandoCompleto = verdadeiro;
    } senao {
      comando += c;
    }
  }
  
  se (comandoCompleto) {
    processarComando();
    comando = "";
    comandoCompleto = falso;
  }
}

funcao processarComando() {
  comando.trim();
  
  se (comando == "home") {
    escreverSerialnl("Voltando para posição inicial...");
    servo1.escreverAngulo(90);
    servo2.escreverAngulo(90);
    mostrarStatus();
    
  } senao se (comando == "sync") {
    escreverSerialnl("Executando movimento sincronizado...");
    movimentoSincronizado();
    
  } senao se (comando == "test") {
    escreverSerialnl("Executando teste completo...");
    testeCompleto();
    
  } senao se (comando.startsWith("s")) {
    // Comando para servo 2
    String anguloStr = comando.substring(1);
    inteiro angulo = anguloStr.toInt();
    se (angulo >= 0 && angulo <= 180) {
      escreverSerial("Movendo servo 2 para ");
      escreverSerial(angulo);
      escreverSerialnl("°");
      servo2.escreverAngulo(angulo);
      mostrarStatus();
    } senao {
      escreverSerialnl("Erro: Ângulo deve estar entre 0 e 180");
    }
    
  } senao {
    // Comando para servo 1
    inteiro angulo = comando.toInt();
    se (angulo >= 0 && angulo <= 180) {
      escreverSerial("Movendo servo 1 para ");
      escreverSerial(angulo);
      escreverSerialnl("°");
      servo1.escreverAngulo(angulo);
      mostrarStatus();
    } senao {
      escreverSerialnl("Comando não reconhecido");
      escreverSerialnl("Use: 0-180, s0-180, sync, home, ou test");
    }
  }
}

funcao mostrarStatus() {
  escreverSerial("Status - Servo1: ");
  escreverSerial(servo1.lerAngulo());
  escreverSerial("° | Servo2: ");
  escreverSerial(servo2.lerAngulo());
  escreverSerialnl("°");
}

funcao movimentoSincronizado() {
  // Movimento espelhado
  para (inteiro angulo = 0; angulo <= 180; angulo += 10) {
    servo1.escreverAngulo(angulo);
    servo2.escreverAngulo(180 - angulo);
    esperarMili(200);
  }
  
  esperarMili(500);
  
  // Volta ao centro
  para (inteiro angulo = 180; angulo >= 90; angulo -= 5) {
    servo1.escreverAngulo(angulo);
    servo2.escreverAngulo(180 - angulo);
    esperarMili(100);
  }
  
  mostrarStatus();
}

funcao testeCompleto() {
  escreverSerialnl("1. Teste individual servo 1");
  para (inteiro angulo = 0; angulo <= 180; angulo += 30) {
    servo1.escreverAngulo(angulo);
    esperarMili(300);
  }
  
  escreverSerialnl("2. Teste individual servo 2");
  para (inteiro angulo = 0; angulo <= 180; angulo += 30) {
    servo2.escreverAngulo(angulo);
    esperarMili(300);
  }
  
  escreverSerialnl("3. Movimento sincronizado");
  movimentoSincronizado();
  
  escreverSerialnl("4. Voltando ao centro");
  servo1.escreverAngulo(90);
  servo2.escreverAngulo(90);
  
  escreverSerialnl("Teste completo finalizado!");
  mostrarStatus();
}