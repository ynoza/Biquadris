#include "iblock.h"
#include <iostream>

using namespace std;

IBlock::IBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='I';
  theBlock.emplace_back(Cell{3,0,true,"IBlock"});
  theBlock.emplace_back(Cell{3,1,true,"IBlock"});
  theBlock.emplace_back(Cell{3,2,true,"IBlock"});
  theBlock.emplace_back(Cell{3,3,true,"IBlock"});

}

void IBlock::rotateClock(){
  if(orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col, true, nf.type}; //(0,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row-1,nf.col-1, true, nf.type}; //(1,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row-2,nf.col-2, true, nf.type}; //(2,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-3,nf.col-3, true, nf.type}; //(3,0)
        orientation = 1;
  }
  else if (orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col, true, nf.type}; //(3,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row+1,nf.col+1, true, nf.type}; //(3,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row+2,nf.col+2, true, nf.type}; //(3,2)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+3,nf.col+3, true, nf.type}; //(3,3)
        orientation = 0;
  }
}


void IBlock::rotateCounterClock(){
  rotateClock();
}
