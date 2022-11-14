#include "Client.h"

#include <string>  // TODO: remove this directive
#include <iostream>  // TODO: remove this directive
#include <fstream>  // TODO: remove this directive

using namespace std;  // TODO: remove this statement

// ctos then stoc to avoid deadlock
ofstream ctos("ctos.fifo");  // TODO: remove this statement
ifstream stoc("stoc.fifo");  // TODO: remove this statement

Client::Client()
{
  // empty function body
}

Trick Client::getClientTrick()  // TODO: turn to low-level hardware
{
  string input;
  clog << "INFO: client's decision now" << endl;
  while(getline(cin, input))
  {
    if(input == "client rock")
      return ROCK;
    if(input == "client paper")
      return PAPER;
    if(input == "client scissor")
      return SCISSOR;
    cerr << "ERROR: invalid client trick, try again..." << endl;
  }
  cerr << "ERROR: error getting client trick" << endl;
  exit(EXIT_SUCCESS);
}

void Client::putClientTrick(Trick trick)  // TODO: turn to low-level hardware
{
  string output;
  if(trick == ROCK)
    output = "client rock";
  else if(trick == PAPER)
    output = "client paper";
  else if(trick == SCISSOR)
    output = "client scissor";
  else
  {
    cerr << "ERROR: invalid client trick" << endl;
    return;
  }
  ctos << output << endl;
}

Trick Client::getClientStatus()  // TODO: turn to low-level hardware
{
  clog << "INFO: server's decision now" << endl;
  string input;
  if(!getline(stoc, input))
    return NTRICK;  /* invalid input */
  if(input == "client wins")
    return WINNER;
  if(input == "client losses")
    return LOSER;
  if(input == "tie")
    return TIE;
  return NTRICK;  /* invalid input */
}

void Client::applyStatus(Trick status)  // TODO: turn to low-level hardware
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
  cout << output << endl;
}

void Client::play()
{
  Trick trick;
  trick = getClientTrick();
  putClientTrick(trick);
  trick = getClientStatus();
  applyStatus(trick);
}
