/*
  ServoMotor.h - Biblioteca para controle de motores servo

  Autor original: Michael Margolis (2009)
  Tradução e adaptação para Brasilino: Erick Simões (2025)
  
  Licenciado sob a licença MIT.
*/

#ifndef ServoMotor_h
#define ServoMotor_h

#include "Arduino.h"

// Tenta usar a biblioteca Servo padrão se disponível
#if __has_include(<Servo.h>)
  #include <Servo.h>
  #define USE_SERVO_LIB
#endif

class ServoMotor {
  public:
    ServoMotor(int pino);
    void escreverAngulo(int angulo);
    int lerAngulo();
    void desconectar();
    
    // Funções de calibração PWM
    void calibrarPWM(int pwmMin, int pwmMax);
    void testarCalibracao();
    void resetarCalibracao();
    void mostrarValoresPWM();
    
    private:
    int _pino;
    int _anguloAtual;
    bool _conectado;
    int _pwmMin;
    int _pwmMax;
    
#ifdef USE_SERVO_LIB
    Servo _servo;
#endif
};

#endif