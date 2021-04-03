void mensajeInicio(int x, int y, int h) {
  u8g2.clearBuffer();
  u8g2.setCursor(x - 56, y - 15);
  u8g2.print(F("CaliBeta Graficador"));
  u8g2.setCursor(x - 25, y + 10);
  u8g2.print(F("Cargando..."));
  u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
  u8g2.sendBuffer();

  for (int i = 0; i < 100; i++) {
    u8g2.drawBox(x - 50, y + 15, i, h);
    u8g2.sendBuffer();
    delay(5);
  }
}
//----------------------------------------------------------------------

//Interface para graficar la señal del detector de metales
void interfaceGrafica(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, uint8_t sy2) {
  u8g2.setDrawColor(1);
  u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
  u8g2.drawRFrame(x, y, x + 37, y + 54, 8);
  u8g2.drawLine(x + 42, y, 45, 60);
  u8g2.drawLine(x + 42, y + 57, 124, 60);
  for (int i = 55; i > 3; i -= 5) {
    u8g2.drawLine(44, i, 46, i);
  }
  u8g2.setDrawColor(0); /* color 1 for the box */
  u8g2.drawBox(x + 6, y + 1, 25, 14);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_6x13B_mn);
  u8g2.setCursor(x + 7, y + 12);
  u8g2.print(voltaje);
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.setCursor(x + 5, y + 20);
  u8g2.print(F("VOLTAJE"));
  u8g2.setCursor(x + 2, y + 36);
  u8g2.print(F("RECUENCIA"));
  u8g2.setCursor(x + 4, y + 53);
  u8g2.print(F("TIME/DIV"));
  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.setCursor(x + 12, y + 28);
  u8g2.print(F("200"));
  u8g2.setCursor(x + 12, y + 45);
  u8g2.print(F("120"));
  u8g2.setCursor(x + 25, y + 53);
  u8g2.drawLine(sx, MAX_Y - sy2, sx, MAX_Y - sy);
  u8g2.sendBuffer();
}
//----------------------------------------------------------------------
