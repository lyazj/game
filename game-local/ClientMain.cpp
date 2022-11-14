#include "Client.h"

Client client;

void setup()
{

}

void loop()
{
  client.play();
}

int main()
{
  setup();
  while(true)
    loop();
}
