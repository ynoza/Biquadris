#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"

class IBlock : public Block {
public:
  IBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
