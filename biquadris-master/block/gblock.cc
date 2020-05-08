#include "gblock.h"

//Grayblock
GBlock::GBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=1;
  letter ='G';
  theBlock.emplace_back(Cell{0,5,true,"GBlock"});
}


void GBlock::rotateClock(){}

void GBlock::rotateCounterClock(){}
