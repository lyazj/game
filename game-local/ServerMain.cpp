#include "Server.h"

Server server;

void setup()
{

}

void loop()
{
  server.play();
}

int main()
{
  setup();
  while(true)
    loop();
}
