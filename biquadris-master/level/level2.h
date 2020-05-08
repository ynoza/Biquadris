#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"

class Block;

class Level2 : public Level{
  int seed;
public:
  Level2();
  Level2(int seed);
  void changerandom(std::string scriptfile){}; //change the level from being random to taking a scriptfile
  ~Level2();
  Block * createBlock() override;
};

#endif
