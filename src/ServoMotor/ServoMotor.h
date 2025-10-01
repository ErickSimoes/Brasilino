/*
  ServoMotor.h - Biblioteca para controle de motores servo

  Autor original: Michael Margolis (2009)
  Tradução e adaptação para Brasilino: Erick Simões (2025)
  
  Licenciado sob a licença MIT.
*/

#ifndef ServoMotor_h
#define ServoMotor_h

#include <Servo.h>

class ServoMotor {
  public:
    ServoMotor(int pino) : servo() { conectar(pino); }
    void conectar(int pino) { servo.attach(pino); }
    void escreverAngulo(int angulo) { servo.write(angulo); }
    int lerAngulo() { return servo.read(); }
    void desconectar() { servo.detach(); }
    
  private:
    Servo servo;
};

#endif