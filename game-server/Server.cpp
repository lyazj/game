#include "Server.h"
#include "Component.h"

void Server::newGame()
{
  updateScorer();
  getOp();
  game.initialize();
  board.initialize();
}

void Server::updateScorer()
{
  Score score[NPLAYER];
  for(uint8_t i = 0; i < NPLAYER; ++i)
    score[i] = game.getScore((Player)i);
  scorer.update(score);
}

void Server::play()
{
  uint8_t x, y, op;
  bool win;
  if(game.init_xy(&x, &y) == 0)  // tie
    return newGame();
  do {
    board.pend(x, y);
    op = getOp();
    win = game.play(player, &x, &y, op);
  }
  while(op != PRESS);
  board.addPiece(player);
  if(win)
    return newGame();
  player = (uint8_t)player + 1;
  if(player == NPLAYER)
    player = 0;
}

uint8_t Server::getOp()
{
  uint8_t op;
  if(player == SERVER)
    return handle.read();
  for(;;)
  {
    op = SLED.receive();
    if(op < NHOP)
      return op;
  }
}
