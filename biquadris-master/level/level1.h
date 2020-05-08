#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"

class Block;

class Level1 : public Level{
  int seed;
public:
  Level1(int seed);
  void changerandom(std::string scriptfile){}; //change the level from being random to taking a scriptfile
  Level1();
  ~Level1();
  Block * createBlock() override;
};

#endif
