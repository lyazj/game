#pragma once

#include "Game.h"

class Client {
private:
  Trick getClientTrick();  // block until input available or timeout
  void putClientTrick(Trick);
  Trick getClientStatus();  // block until input available or timeout
  void applyStatus(Trick);

public:
  Client();
  void play();
};
