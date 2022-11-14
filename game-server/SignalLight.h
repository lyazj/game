#pragma once

#define SIGNAL_UNIT 100

#include "Game.h"

class SignalLight {
private:
  uint8_t pinIn;
  uint8_t pinOut;
public:
  SignalLight(uint8_t, uint8_t);
  void on();
  void off();
  bool isOn();
  bool isOff();
  unsigned long send(uint8_t);
  uint8_t receive();
};
