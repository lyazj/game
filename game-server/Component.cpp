#include "Server.h"
#include "Client.h"
#include "Component.h"

#include <Wire.h>

LiquidCrystal_PCF8574 LCD(0x3f);
SignalLight SLED(PIN_LIGHT_IN, PIN_LIGHT_OUT);
SignalLight BLED(LED_BUILTIN, LED_BUILTIN);
Board board;

void setup()
{
  pinMode(PIN_LIGHT_IN, INPUT);
  pinMode(PIN_LIGHT_OUT, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  SLED.off();
  BLED.off();
  Wire.begin();
  Wire.beginTransmission(0x3f);
  Wire.endTransmission();
  LCD.begin(16, 2);
  LCD.setBacklight(255);
  LCD.clear();
  LCD.home();
  LCD.print("Hello, World!");
  delay(1000);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  st7735_128x160_spi_init(PIN_RST, PIN_CES, PIN_DC);
  ssd1306_setMode(LCD_MODE_NORMAL);
  ssd1306_clearScreen8();
  board.initialize();
}

void loop()
{
  terminal->play();
}
