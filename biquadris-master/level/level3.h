#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"

class Block;

class Level3 : public Level{
  bool random; // boolean which is true when order of createblock needs to be randomized
  std::string scriptfile1;
  int seed;
public:
  Level3();
  void changerandom(std::string scriptfile); //change the level from being random to taking a scriptfile
  Level3(bool random, std::string scriptfile1, int seed);
  ~Level3();
  Block * createBlock() override;
};

#endif
