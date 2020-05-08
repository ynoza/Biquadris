#ifndef ZBLOCK_H
#define ZBLOCK_H

#include "block.h"

class ZBlock : public Block {
public:
  ZBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
