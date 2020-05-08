#include "sblock.h"

SBlock::SBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='S';
  theBlock.emplace_back(Cell{2,1,true,"SBlock"});
  theBlock.emplace_back(Cell{2,2,true,"SBlock"});
  theBlock.emplace_back(Cell{3,0,true,"SBlock"});
  theBlock.emplace_back(Cell{3,1,true,"SBlock"});
}

void SBlock::rotateClock(){
  if(orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col-1, true, nf.type}; //(1,1)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row-1,nf.col-2, true, nf.type}; //(2,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col+1, true, nf.type}; //(0,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-1,nf.col, true, nf.type}; //(1,0)
        orientation = 1;
  }
  else if (orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col+1, true, nf.type}; //(1,1)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row+1,nf.col+2, true, nf.type}; //(1,2)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col-1, true, nf.type}; //(2,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+1,nf.col, true, nf.type}; //(2,1)
        orientation = 0;
  }
}

void SBlock::rotateCounterClock(){
  rotateClock();
}
