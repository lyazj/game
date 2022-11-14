#include "Game.h"

Game::Game(): score { }
{
  // empty function body
}

void Game::play(Trick trick[NPLAYER])
{
  bool valid = true;
  for(uint8_t player = 0; player < NPLAYER; ++player)
    if(trick[player] >= NTRICK)
    {
      valid = false;
      trick[player] = LOSER;
      score[player] -= LOSER_LOSS;
    }
  if(!valid)
  {
    for(uint8_t player = 0; player < NPLAYER; ++player)
      if(trick[player] != LOSER)
      {
        trick[player] = WINNER;
        score[player] += WINNER_GAIN;
      }
    return;
  }
  // result: {0: tie, 1: SERVER wins, 2: CLIENT wins}
  uint8_t result = (trick[SERVER] - trick[CLIENT] + 3) % 3;
  if(result == 0)
  {
    trick[SERVER] = TIE;
    trick[CLIENT] = TIE;
    score[SERVER] += TIE_GAIN;
    score[CLIENT] += TIE_GAIN;
  }
  else
  {
    uint8_t winner = result - 1;
    uint8_t loser = 1 - winner;
    trick[winner] = WINNER;
    trick[loser] = LOSER;
    score[winner] += WINNER_GAIN;
    score[loser] -= LOSER_LOSS;
  }
}

int32_t Game::getScore(Player player)
{
  return score[player];
}
