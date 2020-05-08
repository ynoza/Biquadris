#ifndef PLAYER_H
#define PLAYER_H
#include "grid.h"
#include <vector>

class Block;
class Level;

struct Player {
  int score = 0;
  int level = 0;
  Level * theLevel = nullptr;
  bool randomSequence = true; //if the seuqnce is random
  bool heavy = false; //for level 3 and 4 if a block is heavy
  Block * currBlock = nullptr;
  Block * nextBlock = nullptr;
  Grid gameGrid;
  int level4count = 0; //count number of turns for starblock
  ~Player();
};

#endif
