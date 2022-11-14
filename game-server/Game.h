#pragma once

#include "Handle.h"

#define BOARD_WIDTH  15
#define BOARD_HEIGHT 15

#define WINNER_GAIN 10
#define LOSER_LOSS   5
#define TIE_GAIN     1

typedef int32_t Score;

enum Player : uint8_t {
  SERVER,
  CLIENT,
  NPLAYER,
};

extern uint8_t color[NPLAYER];

class Game {
private:
  Score score[NPLAYER];
  uint8_t board[BOARD_HEIGHT][BOARD_WIDTH];
  void summary();
  void initialize();

public:
  Game();
  bool init_xy(uint8_t *x, uint8_t *y);
  void play(Player player, uint8_t *xp, uint8_t *yp, Hop op);
  uint8_t judge();
  Score getScore(Player);
};
