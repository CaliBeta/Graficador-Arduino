//Funcion de interupcion del Timer2 por comparacion de coincidencia
ISR(TIMER2_COMPA_vect) {
  if (contador >= 60) {
    x++;
    contador = 0;
  }
  contador++;
}
//-----------------------------------------------------------------
