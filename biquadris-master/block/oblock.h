#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"

class OBlock : public Block {
public:
  OBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
