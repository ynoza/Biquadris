#ifndef LEVEL_H
#define LEVEL_H
#include "../block/oblock.h"
#include "../block/iblock.h"
#include "../block/jblock.h"
#include "../block/sblock.h"
#include "../block/zblock.h"
#include "../block/lblock.h"
#include "../block/tblock.h"

class Block;

class Level {
protected:
  int blockCount = 0;
public:
  Level();
  virtual void changerandom(std::string scriptfile)=0; //change the level from being random to taking a scriptfile
  virtual ~Level();
  virtual Block * createBlock () = 0; //creates a block according to the level
  void setBCZero (); //set the position of block count for scriptfile 1
};

#endif
