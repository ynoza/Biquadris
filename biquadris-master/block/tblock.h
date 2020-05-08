#ifndef TBLOCK_H
#define TBLOCK_H

#include "block.h"

class TBlock : public Block {
public:
  TBlock(int levelMade);
  void rotateClock() override;
  void rotateCounterClock() override;
};
#endif
