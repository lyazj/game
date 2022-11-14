#include "Server.h"

#include <string>  // TODO: remove this directive
#include <iostream>  // TODO: remove this directive
#include <fstream>  // TODO: remove this directive

using namespace std;  // TODO: remove this statement

// ctos then stoc to avoid deadlock
ifstream ctos("ctos.fifo");  // TODO: remove this statement
ofstream stoc("stoc.fifo");  // TODO: remove this statement

Server::Server()
{
  // empty function body
}

Trick Server::getClientTrick()  // TODO: turn to low-level hardware
{
  clog << "INFO: client's decision now" << endl;
  string input;
  if(!getline(ctos, input))
    return NTRICK;  /* invalid input */
  if(input == "client rock")
    return ROCK;
  if(input == "client paper")
    return PAPER;
  if(input == "client scissor")
    return SCISSOR;
  return NTRICK;  /* invalid input */
}

Trick Server::getServerTrick()  // TODO: turn to low-level hardware
{
  string input;
  clog << "INFO: server's decision now" << endl;
  while(getline(cin, input))
  {
    if(input == "server rock")
      return ROCK;
    if(input == "server paper")
      return PAPER;
    if(input == "server scissor")
      return SCISSOR;
    cerr << "ERROR: invalid server trick, try again..." << endl;
  }
  cerr << "ERROR: error getting server trick" << endl;
  exit(EXIT_SUCCESS);
}

void Server::putClientStatus(Trick status)  // TODO: turn to low-level hardware
{
  string output;
  if(status == WINNER)
    output = "client wins";
  else if(status == LOSER)
    output = "client losses";
  else if(status == TIE)
    output = "tie";
  else
  {
    cerr << "ERROR: invalid client status" << endl;
    return;
  }
  stoc << output << endl;
}

void Server::applyStatus(Trick status)  // TODO: turn to low-level hardware
{
  string output;
  if(status == WINNER)
    output = "server wins";
  else if(status == LOSER)
    output = "server losses";
  else if(status == TIE)
    output = "tie";
  else
  {
    cerr << "ERROR: invalid server status" << endl;
    return;
  }
  cout << output << endl;
}

void Server::updateDisplay()  // TODO: turn to low-level hardware
{
  clog << "INFO: server : client = "
       << game.getScore(SERVER)
       << " : "
       << game.getScore(CLIENT)
       << endl;
}

void Server::play()
{
  Trick trick[NPLAYER];
  trick[CLIENT] = getClientTrick();
  trick[SERVER] = getServerTrick();
  game.play(trick);
  putClientStatus(trick[CLIENT]);
  applyStatus(trick[SERVER]);
  updateDisplay();
}
