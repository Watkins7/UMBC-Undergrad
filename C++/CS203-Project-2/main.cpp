/*
** File: Main.cpp
** Project: CMSC 202 Project 2, Spring 2020
** Author: William Atkins
** Date: 3/5/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is part of the Subnautica in CMSC 202 @ UMBC
** This is main for project 2
*/

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {

   srand(time(NULL));
   Game newGame;
   newGame.StartGame();

   return 0;
}