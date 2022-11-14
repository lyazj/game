#include "Server.h"
#include "Component.h"

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
  if(game.init_xy(&x, &y) == 0)  /* game over */
  {
    BLED.on();
    for(;;);  // FIXME
  }
  do {
    board.pend(x, y);
    op = getOp();
    game.play(player, &x, &y, op);
  }
  while(op != PRESS);
  board.addPiece(player);
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
