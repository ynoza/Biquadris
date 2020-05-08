#ifndef LBLOCK_H
#define LBLOCK_H

#include "block.h"

class LBlock : public Block {
public:
  LBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
