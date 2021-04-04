/*
  Project : Graficador 0-5V
  Version : 1.0
  Date    : 01/04/2021
  Author  : Carlos Andres Betancourt
  Company : CaliBeta
  Comments:
  Chip type               : ATmega328P-AU
  Program type            : Application
  AVR Core Clock frequency: 16.000000 MHz
  Memory model            : Small
  External RAM size       : 0
  Data Stack size         : 512
  commit:
  ------------------------------------------------------------
  Conexiones electricas

  //----------------------------------------------------------*/

//Incluimos las librerias necesarias
#include <Arduino.h>
#include <U8g2lib.h>
#include "Config.h"
//----------------------------------------------------------

//Declaramos los objetos de las liberias
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, SCK, DATA, CS, U8X8_PIN_NONE);
//----------------------------------------------------------------------

//Declaramos las variables globales necesarias
float voltaje = 0.0;    //mide el voltaje de la señal analoga
int contador = 0;       //cuenta las interrupciones del Timer2
int signalY[] = {0, 0}; //Array para realizar la grafica
int x = MIN_X;          //Valor eje x de la grafica

//----------------------------------------------------------------------

//Configuracion
void setup() {
  //Serial.begin(115200);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x13_tr);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(1);

  pinMode(BL, OUTPUT);

  //Configuramos el estado inicial de los pines
  analogWrite(BL, BRILLO);

  cli();  //Deshabilitamos las interrupciones globales mientras configuramos

  //Configuramos las interrupciones por Timer2 cada 1ms(1000Hz)
  TCCR2A = 0; //registro de control TCCR2A a 0
  TCCR2B = 0; //registro de control TCCR2B a 0
  //configuramos el Timer2 en el modo CTC (comparacion por coincidencia)
  TCCR2A |= (1 << WGM21);
  //Configuramos el bit CS22 en 1 para un prescaler de 64
  TCCR2B |= (1 << CS22);
  //Habilitamos las interrupciones por comparacion
  TIMSK2 |= (1 << OCIE2A);
  //Configuramos el valor del registro de comparacion para interupciones a la
  //frecuencia deseada, [clock Hz)/(frec*prescaler]-1 -->>(menor a 256)
  OCR2A = round((CLOCK / FREC / PRESCALER) - 1);
  TCNT2  = 0; //inicializamos el valor del registro contador a 0

  sei();    //Habilitamos nuevamente las interrupciones globales

  //Configuramos el estado inicial del sistema
  mensajeInicio(XPOS, YPOS, 10);
  delay(100);
  u8g2.clearBuffer();
  x = MIN_X;
}
//----------------------------------------------------------------------

//Funcion Principal
void loop() {
  signalY[0] = analogRead(ADC);
  voltaje = signalY[0] * VCC / 1024;
  signalY[0] = map(signalY[0], 0, 1023, MIN_Y, MAX_Y - 2);
  interfaceGrafica(XPOS - 61, YPOS - 29, x, signalY[0], signalY[1]);

  if (x > MAX_X) {
    x = MIN_X;
  }

  signalY[1] = signalY[0];
}
//----------------------------------------------------------------------
