#ifndef __Config_H__
#define __Config_H__

//LCD ST7920 128x64
#define XPOS        64      //posicion en X standard
#define YPOS        32      //posicion en Y standard
#define SCK         13
#define DATA        11
#define CS          12
#define BL          5
#define BRILLO      120

//Lectura analogica
#define ADC         A0
#define LECTURAS    10      //Numero de lecturas para el promedio
#define OFFSET      -1      //Nivel de offset para calibar el ADC
#define VCC         5.0     //Voltaje de alimentacion del MCU

//Interface grafica
#define MAX_X       124     //Valor maximo eje x
#define MIN_X       45      //Valor minimo eje x
#define MIN_Y       1        //Valor minimo eje y
#define MAX_Y       58      //Valor maximo eje y

#endif
