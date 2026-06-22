#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/wdt.h> // biblioteca do watchdog

LiquidCrystal_I2C lcd(0x20, 16, 2);

int botao = 8;
int carrovermelho = 13;
int carroamarelo = 12;
int carroverde = 11;
int pedestrevermelho = 7;
int pedestreverde = 6;
int som = 10;
int pot = A0;

unsigned long tempoAnterior = 0;
int estado = 0;
int tempoPedestre = 0;
int contador = 0;

void setup() {
  pinMode(botao, INPUT);
  pinMode(carrovermelho, OUTPUT);
  pinMode(carroamarelo, OUTPUT);
  pinMode(carroverde, OUTPUT);
  pinMode(pedestrevermelho, OUTPUT);
  pinMode(pedestreverde, OUTPUT);
  pinMode(som, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Semaforo pronto!");

  // Ativa watchdog com timeout de 2 segundos
  wdt_enable(WDTO_2S);
}

void loop() {
  // Atualiza watchdog
  wdt_reset();

  int start = digitalRead(botao);

  switch (estado) {
    case 0: // Estado inicial: carro verde, pedestre vermelho
      digitalWrite(carroverde, HIGH);
      digitalWrite(pedestrevermelho, HIGH);
      if (start == HIGH) {
        tempoPedestre = map(analogRead(pot), 0, 1023, 5, 15);
        estado = 1;
        tempoAnterior = millis();
      }
      break;

    case 1: // Carro amarelo por 1s
      digitalWrite(carroverde, LOW);
      digitalWrite(carroamarelo, HIGH);
      if (millis() - tempoAnterior >= 1000) {
        digitalWrite(carroamarelo, LOW);
        digitalWrite(carrovermelho, HIGH);
        estado = 2;
        tempoAnterior = millis();
      }
      break;

    case 2: // Carro vermelho por 2s antes de liberar pedestre
      if (millis() - tempoAnterior >= 2000) {
        contador = tempoPedestre;
        estado = 3;
        tempoAnterior = millis();
      }
      break;

    case 3: // Pedestre atravessando
      if (contador > 0 && millis() - tempoAnterior >= 1000) {
        contador--;
        tempoAnterior = millis();

        digitalWrite(pedestrevermelho, LOW);
        digitalWrite(pedestreverde, HIGH);
        tone(som, 440, 200);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pedestre:");
        lcd.setCursor(0, 1);
        lcd.print(contador);
        lcd.print(" segs");
      }
      if (contador == 0) {
        digitalWrite(pedestreverde, LOW);
        digitalWrite(pedestrevermelho, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Espere...");
        estado = 4;
        tempoAnterior = millis();
      }
      break;

    case 4: // Espera 3s antes de liberar carros
      if (millis() - tempoAnterior >= 3000) {
        digitalWrite(carrovermelho, LOW);
        digitalWrite(carroverde, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Semaforo pronto!");
        estado = 0;
      }
      break;
  }
}
