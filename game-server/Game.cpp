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

uint8_t Game::judge()  // TODO
{
  // TODO: score
}

void Game::summary()  // TODO
{
  // TODO: score
}

void Game::play(Player player, uint8_t *xp, uint8_t *yp, Hop op)
{
  uint8_t x = *xp;
  uint8_t y = *yp;
  if(x >= BOARD_HEIGHT || y >= BOARD_WIDTH)
  {
    BLED.on();
    for(;;);  // FIXME
  }
  switch(op)
  {
  case UP:
    if(x == 0)
      return;
    --x;
    while(x && board[x][y])
      --x;
    if(board[x][y] == 0)
      *xp = x;
    return;
  case DOWN:
    if(x == BOARD_HEIGHT - 1)
      return;
    ++x;
    while(x < BOARD_HEIGHT - 1 && board[x][y])
      ++x;
    if(board[x][y] == 0)
      *xp = x;
    return;
  case LEFT:
    if(y == 0)
      return;
    --y;
    while(y && board[x][y])
      --y;
    if(board[x][y] == 0)
      *yp = y;
    return;
  case RIGHT:
    if(y == BOARD_WIDTH - 1)
      return;
    ++y;
    while(y < BOARD_WIDTH - 1 && board[x][y])
      ++y;
    if(board[x][y] == 0)
      *yp = y;
    return;
  case PRESS:
    if(board[x][y] == 0)
      board[x][y] = player + 1;
    return;
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
  return false;
}
