#include "Game.h"
#include "Component.h"
#include <Arduino.h>

Game::Game(): score { }, board { }
{
  // empty function body
}

void Game::initialize()
{
  for(uint8_t i = 0; i < BOARD_HEIGHT; ++i)
    for(uint8_t j = 0; j < BOARD_WIDTH; ++j)
      board[i][j] = 0;
}

bool Game::judge(uint8_t x_in, uint8_t y_in)
{
  uint8_t chess = board[x_in][y_in];
  int8_t x = (int8_t)x_in;
  int8_t y = (int8_t)y_in;
  int8_t dx[4] = {0, 1, 1,  1};
  int8_t dy[4] = {1, 0, 1, -1};

  if(chess == 0)
    return false;
  for(uint8_t i = 0; i < 4; ++i)
  {
    uint8_t c = 1;
    uint8_t x0 = x;
    uint8_t y0 = y;
    while(c < 5)
    {
      uint8_t x1 = x0 + dx[i];
      uint8_t y1 = y0 + dy[i];
      if(x1 < 0 || x1 >= BOARD_HEIGHT || y1 < 0 || y1 >= BOARD_WIDTH)
        break;
      if(board[x1][y1] != chess)
        break;
      ++c;
      x0 = x1;
      y0 = y1;
    }
    x0 = x;
    y0 = y;
    while(c < 5)
    {
      uint8_t x1 = x0 - dx[i];
      uint8_t y1 = y0 - dy[i];
      if(x1 < 0 || x1 >= BOARD_HEIGHT || y1 < 0 || y1 >= BOARD_WIDTH)
        break;
      if(board[x1][y1] != chess)
        break;
      ++c;
      x0 = x1;
      y0 = y1;
    }
    if(c == 5)
      return true;
  }
  return false;
}

void Game::tie()
{
  for(uint8_t p = 0; p < NPLAYER; ++p)
      score[p] += TIE_GAIN;
}

void Game::win(Player player)
{
  for(uint8_t p = 0; p < NPLAYER; ++p)
    if(p == player)
      score[p] += WINNER_GAIN;
    else
      score[p] -= LOSER_LOSS;
}

bool Game::play(Player player, uint8_t *xp, uint8_t *yp, Hop op)
{
  uint8_t x = *xp;
  uint8_t y = *yp;
  switch(op)
  {
  case UP:
    if(x == BOARD_HEIGHT - 1)
      return false;
    ++x;
    while(x < BOARD_HEIGHT - 1 && board[x][y])
      ++x;
    if(board[x][y] == 0)
      *xp = x;
    return false;
  case DOWN:
    if(x == 0)
      return false;
    --x;
    while(x && board[x][y])
      --x;
    if(board[x][y] == 0)
      *xp = x;
    return false;
  case LEFT:
    if(y == 0)
      return false;
    --y;
    while(y && board[x][y])
      --y;
    if(board[x][y] == 0)
      *yp = y;
    return false;
  case RIGHT:
    if(y == BOARD_WIDTH - 1)
      return false;
    ++y;
    while(y < BOARD_WIDTH - 1 && board[x][y])
      ++y;
    if(board[x][y] == 0)
      *yp = y;
    return false;
  case PRESS:
    if(board[x][y] == 0)
    {
      board[x][y] = player + 1;
      if(judge(x, y))
      {
        win(player);
        return true;
      }
    }
    return false;
  }
}

Score Game::getScore(Player player)
{
  return score[player];
}

bool Game::init_xy(uint8_t *xp, uint8_t *yp)
{
  for(uint8_t i = 0; i < BOARD_HEIGHT; ++i)
    for(uint8_t j = 0; j < BOARD_WIDTH; ++j)
      if(board[i][j] == 0)
      {
        *xp = i;
        *yp = j;
        return true;
      }
  tie();
  return false;
}
