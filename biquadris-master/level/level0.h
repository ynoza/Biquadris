#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"

class Block;

class Level0 : public Level{
  std::string scriptfile1;
public:
  //Level0(const std::string scriptfile1, const std::string scriptfile2,
  //  int  * blockCount, int * player);
  Level0();
  void changerandom(std::string scriptfile){}; //change the level from being random to taking a scriptfile
  Level0(std::string scriptfile1); //constrcutor
  ~Level0();
  Block * createBlock() override;
};

#endif
