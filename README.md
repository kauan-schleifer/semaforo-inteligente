# 🚦 Projeto Semáforo Inteligente com Pedestres

## 📌 Descrição
Este projeto implementa um sistema de semáforo para carros e pedestres utilizando **Arduino**, com:
- Controle de tempo de travessia ajustável via potenciômetro
- Exibição das mensagens em um **LCD I2C**
- Sinal sonoro para pedestres
- Uso de **máquina de estados** sem `delay()`
- Implementação de **watchdog timer**
- Teste de **interrupções** para acionamento via botão

O objetivo é simular um semáforo funcional, modular e seguro, seguindo boas práticas de programação embarcada.

---

## 🛠️ Componentes Utilizados
- Placa **Arduino Uno**
- Display **LCD 16x2 com módulo I2C**
- LEDs (vermelho, amarelo, verde) para carros
- LEDs (vermelho, verde) para pedestres
- **Buzzer** para sinal sonoro
- **Botão** para acionamento da travessia
- **Potenciômetro** para ajuste do tempo de travessia

---

## 📂 Organização do Código
- `setup()`: inicialização dos pinos, LCD e watchdog
- `loop()`: máquina de estados controlando o semáforo
- Estados:
  - **0** → Carro verde, pedestre vermelho
  - **1** → Carro amarelo (1s)
  - **2** → Carro vermelho (2s)
  - **3** → Travessia do pedestre (tempo ajustável)
  - **4** → Espera antes de liberar carros novamente

---

## ⚙️ Funcionalidades Obrigatórias
- **Organização**: código estruturado em estados
- **Modularização**: cada fase do semáforo é um estado independente
- **Comentários**: explicações em cada parte do código
- **Boas práticas**: uso de `millis()` em vez de `delay()`
- **Interrupções**: botão de pedestre acionado via leitura digital
- **Watchdog**: reinicia o sistema em caso de travamento

---

## 🎬 Simulação Funcional
### Funcionamento normal
- Carros seguem ciclo verde → amarelo → vermelho
- Pedestres aguardam até acionamento do botão

### Acionamento das entradas
- Botão inicia ciclo de travessia
- Potenciômetro ajusta tempo de travessia (5–15s)

### Teste da interrupção
- Pressionar o botão durante o ciclo aciona a travessia

### Teste do watchdog
- Caso o loop trave, o watchdog reinicia o Arduino em até 2 segundos

---

## ▶️ Como Executar
1. Monte o circuito conforme os componentes listados
2. Carregue o código no Arduino
3. Abra o **Serial Monitor** ou observe o LCD para acompanhar o funcionamento
4. Teste o botão e o potenciômetro para verificar as funcionalidades

---

## 👨‍💻 Autores
Projeto desenvolvido por **Kauan e João** para a disciplina de Microcontroladores e Microprocessadores.  
Entrega 3 — Desenvolvimento do Sistema (3 pontos).
