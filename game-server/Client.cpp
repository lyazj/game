#include "Component.h"
#include "Client.h"

void Client::play()
{
  uint8_t op = handle.read();
  SLED.send(op);
}
