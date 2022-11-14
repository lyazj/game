#include "Scorer.h"
#include "Component.h"

void Scorer::update(Score score[NPLAYER])
{
  LCD.clear();
  for(uint8_t i = 0; i < NPLAYER; ++i)
  {
    LCD.setCursor(0, i);
    LCD.print("Player");
    LCD.print(i);
    LCD.print(": ");
    LCD.print(score[i]);
  }
}
