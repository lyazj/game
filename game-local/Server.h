#pragma once

#include "Game.h"

class Server {
private:
  Game game;
  Trick getClientTrick();  // block until input available or timeout
  Trick getServerTrick();  // block until input available or timeout
  void putClientStatus(Trick);
  void applyStatus(Trick);
  void updateDisplay();

public:
  Server();
  void play();
};
