/*
  ServoMotor.cpp - Biblioteca para controle de motores servo

  Autor original: Michael Margolis (2009)
  Tradução e adaptação para Brasilino: Erick Simões (2025)
  
  Licenciado sob a licença MIT.
*/

#include "ServoMotor.h"

#ifndef USE_SERVO_LIB
// Constantes para PWM do servo (usado apenas quando não há biblioteca Servo)
#define PERIODO_PWM 20000    // 20ms em microsegundos
#define PULSO_MIN 544        // Pulso mínimo em microsegundos (0 graus)
#define PULSO_MAX 2400       // Pulso máximo em microsegundos (180 graus)
#endif

ServoMotor::ServoMotor(int pino) {
    _pino = pino;
    _anguloAtual = 90;
    _conectado = true;
    
    // Valores padrão conservadores - funcionam na maioria dos servos
    _pwmMin = 15;
    _pwmMax = 300;

    #ifdef USE_SERVO_LIB
        _servo.attach(pino);
    #else
        pinMode(_pino, OUTPUT);
    #endif
    escreverAngulo(_anguloAtual);
}

void ServoMotor::escreverAngulo(int angulo) {
    if (!_conectado || _pino < 0) return;
    
    // Limita o ângulo entre 0 e 180 graus
    if (angulo < 0) angulo = 0;
    if (angulo > 180) angulo = 180;
    
    _anguloAtual = angulo;
    
#ifdef USE_SERVO_LIB
    _servo.write(angulo);
#else
    // Implementação manual quando a biblioteca Servo não está disponível
    // Converte o ângulo para largura de pulso em microsegundos
    int larguraPulso = map(angulo, 0, 180, PULSO_MIN, PULSO_MAX);
    
    // Gera o sinal PWM usando analogWrite se o pino suportar
    // Os valores PWM abaixo foram determinados empiricamente para Arduino Uno.
    // Use calibrarPWM() para ajustar para seu servo específico.

    if (digitalPinHasPWM(_pino)) {
        // Converte microsegundos para valor PWM (0-255)
        // Nota: Esta é uma aproximação, pode precisar de ajustes para outros modelos
        int valorPWM = map(larguraPulso, PULSO_MIN, PULSO_MAX, _pwmMin, _pwmMax);
        analogWrite(_pino, valorPWM);
    } else {
        // Para pinos sem PWM, gera o sinal manualmente
        for (int i = 0; i < 10; i++) {
            digitalWrite(_pino, HIGH);
            delayMicroseconds(larguraPulso);
            digitalWrite(_pino, LOW);
            delayMicroseconds(PERIODO_PWM - larguraPulso);
        }
    }
#endif
}

int ServoMotor::lerAngulo() {
#ifdef USE_SERVO_LIB
    return _servo.read();
#else
    return _anguloAtual;
#endif
}

void ServoMotor::desconectar() {
    _conectado = false;
    
#ifdef USE_SERVO_LIB
    _servo.detach();
#else
    if (_pino >= 0) {
        digitalWrite(_pino, LOW);
    }
#endif
}

// ==================== FUNÇÕES DE CALIBRAÇÃO ====================

void ServoMotor::calibrarPWM(int pwmMin, int pwmMax) {
    _pwmMin = pwmMin;
    _pwmMax = pwmMax;
    
    Serial.print("Calibração atualizada - PWM_MIN: ");
    Serial.print(_pwmMin);
    Serial.print(", PWM_MAX: ");
    Serial.println(_pwmMax);
}

void ServoMotor::testarCalibracao() {
    Serial.println("=== TESTE DE CALIBRAÇÃO ===");
    Serial.println("Observe o servo e ajuste os valores conforme necessário:");
    Serial.println();
    
    mostrarValoresPWM();
    
    Serial.println("Testando posição 0° (mínima)...");
    escreverAngulo(0);
    delay(2000);
    
    Serial.println("Testando posição 90° (centro)...");
    escreverAngulo(90);
    delay(2000);
    
    Serial.println("Testando posição 180° (máxima)...");
    escreverAngulo(180);
    delay(2000);
    
    Serial.println("Voltando ao centro...");
    escreverAngulo(90);
    
    Serial.println();
    Serial.println("COMO AJUSTAR:");
    Serial.println("- Se não atingir 0°: diminua PWM_MIN");
    Serial.println("- Se não atingir 180°: aumente PWM_MAX");
    Serial.println("- Se ultrapassar os limites: ajuste na direção oposta");
    Serial.println();
    Serial.println("Use calibrarPWM(pwmMin, pwmMax) para ajustar");
}

void ServoMotor::resetarCalibracao() {
    _pwmMin = 26;   // Valor conservador para 1ms
    _pwmMax = 128;  // Valor conservador para 2ms
    
    Serial.println("Calibração resetada para valores padrão:");
    mostrarValoresPWM();
}

void ServoMotor::mostrarValoresPWM() {
    Serial.print("Valores PWM atuais - MIN: ");
    Serial.print(_pwmMin);
    Serial.print(" (");
    Serial.print(map(_pwmMin, 0, 255, 0, 20000));
    Serial.print("μs), MAX: ");
    Serial.print(_pwmMax);
    Serial.print(" (");
    Serial.print(map(_pwmMax, 0, 255, 0, 20000));
    Serial.println("μs)");
}
