#ifndef JBLOCK_H
#define JBLOCK_H

#include "block.h"

class JBlock : public Block {
public:
  JBlock(int level);
  void rotateClock() override;
  void rotateCounterClock() override;
};

#endif
