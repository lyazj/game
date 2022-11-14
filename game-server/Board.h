#pragma once

#include "Game.h"
#include <ssd1306.h>

class Board {
private:
  bool pending;
  uint8_t pendingX;
  uint8_t pendingY;
  uint8_t color[BOARD_HEIGHT][BOARD_WIDTH];
  void drawBoard();
  static const uint8_t boardColor;
  static const uint8_t pieceColor[NPLAYER];
  static const uint8_t pendingColor;
public:
  void initialize();
  void addPiece(Player p);
  void pend(uint8_t x, uint8_t y);
};
