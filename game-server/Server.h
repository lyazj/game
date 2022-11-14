#pragma once

#include "Game.h"
#include "Terminal.h"
#include "Scorer.h"

class Server: public Terminal {
private:
  Player player = SERVER;
  Game game;
  Scorer scorer;
  void updateScorer();
  uint8_t getOp();

public:
  virtual void play() override;
};
