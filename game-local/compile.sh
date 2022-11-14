#!/bin/bash

g++ -static ClientMain.cpp Client.cpp -o client
g++ -static ServerMain.cpp Server.cpp Game.cpp -o server
rm -f ctos.fifo stoc.fifo
mkfifo ctos.fifo stoc.fifo
