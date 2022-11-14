#pragma once

#include "SignalLight.h"
#include "Terminal.h"
#include "Board.h"

#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>
#include <ssd1306.h>
#include <nano_engine.h>

#define PIN_X A0
#define PIN_Y A1
#define PIN_P A2
#define PIN_LIGHT_IN  2
#define PIN_LIGHT_OUT 9
#define PIN_RST 3
#define PIN_CES 4
#define PIN_DC  5

extern Terminal *terminal;
extern LiquidCrystal_PCF8574 LCD;
extern SignalLight SLED;
extern SignalLight BLED;  // use only: on(), off()
extern Board board;

void init_terminal();
