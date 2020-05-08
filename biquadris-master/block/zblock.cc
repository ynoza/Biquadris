#include "zblock.h"


ZBlock::ZBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='Z';
  theBlock.emplace_back(Cell{2,0,true,"ZBlock"});
  theBlock.emplace_back(Cell{2,1,true,"ZBlock"});
  theBlock.emplace_back(Cell{3,1,true,"ZBlock"});
  theBlock.emplace_back(Cell{3,2,true,"ZBlock"});
}


void ZBlock::rotateClock(){
  if(orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row-1,nf.col+1, true, nf.type}; //(0,1)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col, true, nf.type}; //(1,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row-1,nf.col-1, true, nf.type}; //(1,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row,nf.col-2, true, nf.type}; //(2,0)
        orientation = 1;
  }
  else if (orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row+1,nf.col-1, true, nf.type}; //(1,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col, true, nf.type}; //(1,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row+1,nf.col+1, true, nf.type}; //(2,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row,nf.col+2, true, nf.type}; //(2,2)
        orientation = 0;
  }
}

void ZBlock::rotateCounterClock(){
  rotateClock();
}
