# ServoMotor - Biblioteca Brasilino

Esta é uma biblioteca wrapper em português para controle de servomotores, compatível com a biblioteca padrão Servo.h do Arduino.

## Características

- **Compatibilidade**: Funciona como wrapper da biblioteca Servo.h quando disponível
- **Fallback**: Implementação própria quando a biblioteca Servo.h não está disponível
- **Interface em Português**: Todas as funções têm nomes em português
- **Fácil de usar**: Interface simples e intuitiva

## Instalação

A biblioteca ServoMotor já está incluída na biblioteca Brasilino. Para usar, simplesmente inclua:

```cpp
#include <Brasilino.h>
```

## Funções Disponíveis

### Construtores
- `ServoMotor()` - Cria um objeto ServoMotor
- `ServoMotor(int pino)` - Cria um objeto ServoMotor e conecta ao pino especificado

### Métodos
- `conectar(int pino)` - Conecta o servo ao pino especificado
- `escreverAngulo(int angulo)` - Define o ângulo do servo (0-180 graus)
- `lerAngulo()` - Retorna o ângulo atual do servo
- `desconectar()` - Desconecta o servo do pino

## Exemplos de Uso

### Exemplo Básico
```cpp
#include <Brasilino.h>

ServoMotor meuServo;

funcao configurar() {
  meuServo.conectar(9);        // Conecta ao pino 9
  meuServo.escreverAngulo(90); // Posição central
}

funcao repetir() {
  // Movimento de varredura
  para (inteiro i = 0; i <= 180; i++) {
    meuServo.escreverAngulo(i);
    esperarMili(15);
  }
}
```

### Exemplo com Construtor
```cpp
#include <Brasilino.h>

ServoMotor meuServo(9); // Conecta automaticamente ao pino 9

funcao configurar() {
  meuServo.escreverAngulo(0); // Posição inicial
}

funcao repetir() {
  meuServo.escreverAngulo(90);  // Centro
  esperar(1);
  meuServo.escreverAngulo(180); // Máximo
  esperar(1);
}
```

## Implementação Técnica

### Com Biblioteca Servo.h (Recomendado)
Quando a biblioteca Servo.h está disponível, a ServoMotor funciona como um wrapper simples, oferecendo:
- Controle preciso via timers
- Suporte a múltiplos servos
- Baixo consumo de recursos

### Sem Biblioteca Servo.h (Fallback)
Quando a biblioteca Servo.h não está disponível, a implementação utiliza:
- PWM via `analogWrite()` em pinos compatíveis
- Controle manual via `digitalWrite()` em outros pinos
- Geração de pulsos com largura apropriada (544-2400 μs)

## Pinos Compatíveis

### Arduino Uno/Nano/Pro Mini
- Pinos PWM: 3, 5, 6, 9, 10, 11
- Outros pinos: Todos os pinos digitais (com controle manual)

### Arduino Mega
- Pinos PWM: 2-13, 44-46
- Outros pinos: Todos os pinos digitais

## Limitações

1. **Precisão**: O modo fallback (sem Servo.h) pode ser menos preciso
2. **Performance**: O controle manual pode bloquear outras operações
3. **Múltiplos Servos**: O modo fallback não é otimizado para múltiplos servos

## Solução de Problemas

### Servo não se move
1. Verifique a alimentação do servo (4.8-6V)
2. Confirme se o pino está correto
3. Teste com valores entre 0 e 180 graus

### Movimento irregular
1. Verifique se há interferência elétrica
2. Use capacitors para filtrar a alimentação
3. Considere usar pinos PWM quando possível

### Biblioteca não compila
1. Verifique se a biblioteca Brasilino está instalada
2. Confirme se está usando a versão mais recente
3. Reporte issues no GitHub

## Autor

**Erick Simões** (2025)
- GitHub: [@ErickSimoes](https://github.com/ErickSimoes)
- Twitter: [@AloErickSimoes](https://twitter.com/AloErickSimoes)

Baseado na biblioteca original Servo de Michael Margolis.

## Licença

MIT License - Veja LICENSE para detalhes.