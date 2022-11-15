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
  int8_t dx[8] = {0, 1,  0, -1, 1,  1, -1, -1};
  int8_t dy[8] = {1, 0, -1,  0, 1, -1, -1,  1};

  if(chess == 0)
    return false;
  for(uint8_t i = 0; i < 8; ++i)
  {
    if(x + (dx[i] << 2) < 0)
      continue;
    if(x + (dx[i] << 2) >= BOARD_HEIGHT)
      continue;
    if(y + (dy[i] << 2) < 0)
      continue;
    if(y + (dy[i] << 2) >= BOARD_WIDTH)
      continue;

    int8_t xx = x;
    int8_t yy = y;
    for(uint8_t j = 1; j <= 4; ++j)
    {
      xx += dx[i];
      yy += dy[i];
      if(board[xx][yy] != chess)
        break;
    }
    if(j == 5)
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
    if(x == 0)
      return false;
    --x;
    while(x && board[x][y])
      --x;
    if(board[x][y] == 0)
      *xp = x;
    return false;
  case DOWN:
    if(x == BOARD_HEIGHT - 1)
      return false;
    ++x;
    while(x < BOARD_HEIGHT - 1 && board[x][y])
      ++x;
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
