#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"

class Block;

class Level4 : public Level{
  bool random; //boolean which is true when creating a block randomly
  std::string scriptfile1;
  int seed;
public:
  Level4();
  void changerandom(std::string scriptfile); //change the level from being random to taking a scriptfile
  Level4(bool random, std::string scriptfile1, int seed);
  ~Level4();
  Block * createBlock() override;
};


#endif
