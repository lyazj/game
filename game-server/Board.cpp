#include "Board.h"
#include "Component.h"

#define POS(i) (4 + (i) * 8)

const uint8_t Board::boardColor = RGB_COLOR8(255, 255, 255);
const uint8_t Board::pieceColor[NPLAYER] = {
  RGB_COLOR8(0, 0, 255),
  RGB_COLOR8(0, 255, 0),
};
const uint8_t Board::pendingColor = RGB_COLOR8(255, 0, 0);

void Board::initialize()
{
  pending = 0;
  for(uint8_t i = 0; i < BOARD_HEIGHT; ++i)
    for(uint8_t j = 0; j < BOARD_WIDTH; ++j)
      color[i][j] = 0;
  ssd1306_clearScreen8();
  drawBoard();
}

void Board::drawBoard()
{
  ssd1306_setColor(boardColor);
  for(uint8_t i = 0; i < BOARD_HEIGHT; ++i)
    for(uint8_t j = 0; j < BOARD_WIDTH; ++j)
      ssd1306_drawRect8(POS(i), POS(j), POS(i + 1), POS(j + 1));
}

void Board::addPiece(Player p)
{
  if(pending == 0)
    return;
  uint8_t x = pendingX;
  uint8_t y = pendingY;
  if(color[x][y])
    return;
  pending = 0;
  ssd1306_setColor(color[x][y] = pieceColor[p]);
  ssd1306_fillRect8(POS(x) + 1, POS(y) + 1, POS(x + 1) - 1, POS(y + 1) - 1);
}

void Board::pend(uint8_t x, uint8_t y)
{
  if(pending)
  {
    uint8_t x = pendingX;
    uint8_t y = pendingY;
    ssd1306_setColor(color[x][y]);
    ssd1306_fillRect8(POS(x) + 1, POS(y) + 1, POS(x + 1) - 1, POS(y + 1) - 1);
  }
  pendingX = x;
  pendingY = y;
  ssd1306_setColor(pendingColor);
  ssd1306_fillRect8(POS(x) + 1, POS(y) + 1, POS(x + 1) - 1, POS(y + 1) - 1);
  pending = 1;
}
