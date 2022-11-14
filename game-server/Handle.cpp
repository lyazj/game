#include "Component.h"
#include "Handle.h"

uint8_t Handle::read_single(uint8_t pin)
{
  if(pin == PIN_P)
    return analogRead(pin) >= 10;
  float val = (float)(analogRead(pin) * VAL_NSEG) / VAL_MAX;
  long v = round(val);
  if(v > VAL_NSEG)
    return OP_INVALID;
  return v;
}

uint8_t Handle::read_buf(uint8_t buf[3])
{
  uint8_t i;
  uint8_t s = 0;
  uint8_t pin[3] = {PIN_X, PIN_Y, PIN_P};
read_buf_restart:
  for(i = 0; i < 3; ++i)
    if((buf[i] = read_single(pin[i])) == OP_INVALID)
      goto read_buf_restart;
    else
      s += buf[i] != OP_DEFAULT;
  return s;
}

uint8_t Handle::read()
{
  uint8_t buf[3];
  uint8_t val;
  for(;;)
  {
    if(read_buf(buf) == 1)
    {
      if(buf[0] != OP_DEFAULT)
        val = buf[0] == 0 ? LEFT : RIGHT;
      else if(buf[1] != OP_DEFAULT)
        val = buf[1] == 0 ? UP : DOWN;
      else
        val = PRESS;
      delay(10);
      break;
    }
  }
  while(read_buf(buf));
  delay(10);
  return val;
}
