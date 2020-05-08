#ifndef SBLOCK_H
#define SBLOCK_H

#include "block.h"

class SBlock : public Block {
public:
  SBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
