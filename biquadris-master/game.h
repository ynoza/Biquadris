#ifndef GAME_H
#define GAME_H
#include <string>
#include "subject.h"
#include "./block/block.h"
#include "grid.h"
#include "player.h"
#include <iostream>

class Game : public Subject{
  std::string scriptfile1;
  std::string scriptfile2;
  std::istream &in = std::cin;
  std::ostream &out = std::cout;
  GraphicsDisplay * newGD = nullptr;
  int seed;
  // Both of the players
  Player player1;
  Player player2;
  int highscore;
  bool textonly;
  bool bonus;
  bool turn = true;
public:
  // Constructor for Game
  Game (std::string scriptfile1, std::string scriptfile2,
    int seed, int level, int highscore, bool textonly, bool bonus);
  void printWinner(int sp1, int sp2);
  // Main function that will do everything
  int play();
  // Will be used for printing outputs to the displays
  void printDisplay(std::ostream& output);
  friend std::ostream &operator<<(std::ostream &out, const Game &g);
  ~Game ();
};
#endif
