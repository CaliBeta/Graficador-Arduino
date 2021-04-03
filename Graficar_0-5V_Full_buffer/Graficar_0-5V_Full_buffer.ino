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
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCK, DATA, CS, U8X8_PIN_NONE);
//----------------------------------------------------------------------

//Declaramos las variables globales necesarias
//Enumeracion para las entradas de la maquina
enum entrada {
  DESCONOCIDO,
  TIME_DIV_MENOS,
  TIME_DIV_MAS
};

//Enumeracion para los estados de la maquina
enum estado {
  INTERFACE_GRAFICA,
  CONFIGURACION,
};

//Variables maquina de estados
entrada entradaActual;
estado estadoActual;

float voltaje = 0.0;
int signalY[] = {0, 0};
int x = MIN_X;   //Valor eje x grafica señal detector
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

  mensajeInicio(XPOS, YPOS, 10);

  //Configuramos el estado inicial del sistema
  estadoActual = estado::INTERFACE_GRAFICA;
  delay(100);
  u8g2.clearBuffer();
}
//----------------------------------------------------------------------

//Funcion Principal
void loop() {
  signalY[0] = analogRead(ADC);
  voltaje = signalY[0] * VCC / 1024;
  signalY[0] = map(signalY[0], 0, 1023, MIN_Y, MAX_Y - 2);
  interfaceGrafica(XPOS - 61, YPOS - 29, x, signalY[0], signalY[1]);

  if (x < MAX_X) {
    x++;
  }
  else {
    x = MIN_X;
    u8g2.clearBuffer();
  }
  signalY[1] = signalY[0];
  delay(100);
}
//----------------------------------------------------------------------
