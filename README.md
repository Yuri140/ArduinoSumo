# Projeto Robô Sumô com Arduino

## Descrição
Este projeto implementa um robô de sumô controlado por Arduino. O robô utiliza motores e sensores ultrassônicos para identificar oponentes e bordas da arena, movendo-se estrategicamente para empurrar o adversário para fora da área delimitada.

## Funcionalidades
- **Movimentação automática**: O robô busca e ataca o oponente.
- **Detecção de bordas**: Sensores reflexivos detectam bordas da arena e ajustam o movimento para evitar quedas.
- **Sensores ultrassônicos**: Identificação da distância até o oponente.

## Bibliotecas Utilizadas
1. `AFMotor.h` - Controla o Motor Shield.
2. `Ultrasonic.h` - Gerencia o sensor ultrassônico.

## Componentes Necessarios
- **Os componentes necessarios para realização do projeto estão no arquivo [ComponentesArduino](ComponentesArduino.md)** 


## Código do Projeto
O código principal está localizado no arquivo `codigo_robo_sumo_arduino` e inclui as seguintes funções principais:
- **`setup()`**: Configuração inicial dos motores e sensores.
- **`loop()`**: Lógica de movimentação e detecção do oponente/bordas.
- **Funções de Movimento**:
  - `frente()`
  - `tras()`
  - `esquerda()`
  - `direita()`
  - `parada()`
  - `procura()` (movimento otimizado para busca).

## Funcionamento
1. O robô utiliza o sensor ultrassônico para identificar a distância até o oponente.
2. Os sensores reflexivos monitoram bordas da arena e impedem que o robô saia.
3. Ao localizar o oponente, o robô avança e tenta empurrá-lo.
4. A lógica de movimentação otimizada busca oponente caso ele não esteja visível.

## Como Executar o Projeto
1. Carregue o código `codigo_robo_sumo_arduino` no Arduino usando a IDE Arduino.
2. Insira as bibliotecas dentro da pasta [Bibliotecas](Bibiotecas)
3. Conecte os componentes descritos em `ComponentesArduino.md`.
4. Ligue o robô e coloque-o na arena.
---

