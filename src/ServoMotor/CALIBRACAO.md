/*
  Calibração ServoMotor - Brasilino
  
  Este sketch ajuda a encontrar os valores ideais de PWM_MIN e PWM_MAX
  para seu servo específico.
  
  COMO USAR:
  1. Conecte seu servo no pino 9
  2. Carregue este código
  3. Abra o Serial Monitor (9600 baud)
  4. Observe o movimento e siga as instruções
  5. Ajuste os valores até obter movimento completo (0° a 180°)
  
  COMANDOS VIA SERIAL:
  - test: Executa teste automático
  - reset: Volta aos valores padrão
  - cal MIN MAX: Define novos valores (ex: cal 20 140)
  - show: Mostra valores atuais
  - 0-180: Move para ângulo específico
  
  Criado por: Erick Simões (2025)
*/

#include <Brasilino.h>

ServoMotor servo(9);
String comando = "";

funcao configurar() {
  iniciarSerial(9600);
  esperar(1);
  
  escreverSerialn("=== CALIBRAÇÃO SERVOMOTOR ===");
  escreverSerialn("Conecte o servo no pino 9");
  escreverSerialn("");
  escreverSerialn("Comandos disponíveis:");
  escreverSerialn("- test: Teste automático");
  escreverSerialn("- reset: Resetar calibração");
  escreverSerialn("- cal MIN MAX: Calibrar (ex: cal 20 140)");
  escreverSerialn("- show: Mostrar valores atuais");
  escreverSerialn("- 0-180: Mover para ângulo");
  escreverSerialn("============================");
  
  servo.mostrarValoresPWM();
  escreverSerialn("Digite 'test' para começar a calibração");
}

funcao repetir() {
  se (Serial.available()) {
    comando = Serial.readString();
    comando.trim();
    processarComando();
  }
}

funcao processarComando() {
  se (comando == "test") {
    servo.testarCalibracao();
    
  } senao se (comando == "reset") {
    servo.resetarCalibracao();
    
  } senao se (comando == "show") {
    servo.mostrarValoresPWM();
    
  } senao se (comando.startsWith("cal ")) {
    // Extrai valores MIN e MAX do comando
    inteiro espaco1 = comando.indexOf(' ', 4);
    
    se (espaco1 > 0) {
      inteiro pwmMin = comando.substring(3, espaco1).toInt();
      inteiro pwmMax = comando.substring(espaco1 + 1).toInt();
      
      se (pwmMin > 0 && pwmMax > pwmMin && pwmMax <= 255) {
        servo.calibrarPWM(pwmMin, pwmMax);
        escreverSerialn("Calibração aplicada! Digite 'test' para testar.");
      } senao {
        escreverSerialn("Erro: Valores inválidos (MIN: 1-254, MAX: MIN+1 a 255)");
      }
    } senao {
      escreverSerialn("Uso: cal MIN MAX (exemplo: cal 20 140)");
    }
    
  } senao {
    // Tenta interpretar como ângulo
    inteiro angulo = comando.toInt();
    se (angulo >= 0 && angulo <= 180) {
      escreverSerial("Movendo para ");
      escreverSerial(angulo);
      escreverSerialn("°");
      servo.escreverAngulo(angulo);
    } senao {
      escreverSerialn("Comando não reconhecido");
      escreverSerialn("Use: test, reset, show, cal MIN MAX, ou 0-180");
    }
  }
}

// ============ GUIA DE CALIBRAÇÃO MANUAL ============
/*
VALORES TÍPICOS PARA DIFERENTES SERVOS:

1. SERVO PADRÃO (SG90, MG90S):
   - PWM_MIN: 20-30 (corresponde a ~1ms)
   - PWM_MAX: 130-140 (corresponde a ~2ms)

2. SERVO DE ROTAÇÃO CONTÍNUA:
   - PWM_MIN: 25-35
   - PWM_MAX: 120-135
   
3. MICRO SERVO:
   - PWM_MIN: 15-25
   - PWM_MAX: 125-140

4. SERVO METAL GEAR:
   - PWM_MIN: 25-35
   - PWM_MAX: 135-150

CÁLCULO TEÓRICO:
Para Arduino Uno (PWM ~490Hz):
- 1ms = (1000/20408) × 255 ≈ 12.5 → use ~20-30
- 2ms = (2000/20408) × 255 ≈ 25.0 → use ~125-140

DICAS:
- Comece com valores conservadores (26, 128)
- Ajuste gradualmente em incrementos de 5-10
- Alguns servos precisam de valores fora da faixa padrão
- Anote os valores que funcionam melhor para seu servo

SOLUÇÃO DE PROBLEMAS:
- Servo treme: Valores muito próximos dos limites
- Não atinge 0°: Diminua PWM_MIN
- Não atinge 180°: Aumente PWM_MAX
- Movimento irregular: Verifique alimentação
*/
