#include "oblock.h"

OBlock::OBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='O';
  theBlock.emplace_back(Cell{2,0,true,"OBlock"});
  theBlock.emplace_back(Cell{2,1,true,"OBlock"});
  theBlock.emplace_back(Cell{3,0,true,"OBlock"});
  theBlock.emplace_back(Cell{3,1,true,"OBlock"});
}


void OBlock::rotateClock(){}

void OBlock::rotateCounterClock(){}
