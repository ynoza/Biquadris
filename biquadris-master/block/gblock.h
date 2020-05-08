#ifndef GBLOCK_H
#define GBLOCK_H

#include "block.h"

class GBlock : public Block {
public:
  GBlock(int levelMade); //make a grayblock
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
