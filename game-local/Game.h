#pragma once

#include <stdint.h>

#define WINNER_GAIN 10
#define LOSER_LOSS   5
#define TIE_GAIN     1

enum Player : uint8_t {
  SERVER,
  CLIENT,
  NPLAYER,
};

enum Trick : uint8_t {
  ROCK,
  PAPER,
  SCISSOR,
  NTRICK,
  WINNER,
  LOSER,
  TIE,
};

class Game {
private:
  int32_t score[NPLAYER];

public:
  Game();
  void play(Trick[NPLAYER]);  // written back: WINNER/LOSER/TIE
  int32_t getScore(Player);
};
