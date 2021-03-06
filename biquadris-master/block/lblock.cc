#include "lblock.h"

//not done rotate yet
LBlock::LBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='L';
  theBlock.emplace_back(Cell{2,2,true,"LBlock"}); //(1,2)
  theBlock.emplace_back(Cell{3,0,true,"LBlock"}); //(2,0)
  theBlock.emplace_back(Cell{3,1,true,"LBlock"}); //(2,1)
  theBlock.emplace_back(Cell{3,2,true,"LBlock"}); //(2,2)
}

void LBlock::rotateClock(){
  if(orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row+1,nf.col-1, true, nf.type}; //(2,1)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row-2,nf.col, true, nf.type}; //(0,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row-1,nf.col-1, true, nf.type}; //(1,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row,nf.col-2, true, nf.type}; //(2,0)
        orientation = 1;
  }
  else if (orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col-1, true, nf.type}; //(1,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row+1,nf.col+2, true, nf.type}; //(1,2)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col+1, true, nf.type}; //(1,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-1,nf.col, true, nf.type}; //(1,0)
        orientation = 2;
  }
  else if (orientation == 2){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row-2,nf.col, true, nf.type}; //(0,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row+1,nf.col-1, true, nf.type}; //(2,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col, true, nf.type}; //(1,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-1,nf.col+1, true, nf.type}; //(0,1)
        orientation = 3;
  }
  else if (orientation == 3){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row+1,nf.col+2, true, nf.type}; //(1,2)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col-1, true, nf.type}; //(2,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row+1,nf.col, true, nf.type}; //(2,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+2,nf.col+1, true, nf.type}; //(2,2)
        orientation = 0;
  }
}


void LBlock::rotateCounterClock(){ // In this one the corrdinates given
  if(orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row-1,nf.col+1, true, nf.type}; //(2,1)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row+2,nf.col, true, nf.type}; //(0,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row+1,nf.col+1, true, nf.type}; //(1,0)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row,nf.col+2, true, nf.type}; //(2,0)
        orientation = 0;
  }
  else if (orientation == 2){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row,nf.col+1, true, nf.type}; //(2,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row-1,nf.col-2, true, nf.type}; //(1,2)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col-1, true, nf.type}; //(1,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+1,nf.col, true, nf.type}; //(1,0)
        orientation = 1;
  }
  else if (orientation == 3){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row+2,nf.col, true, nf.type}; //(0,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row-1,nf.col+1, true, nf.type}; //(2,1)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row,nf.col, true, nf.type}; //(1,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+1,nf.col-1, true, nf.type}; //(0,1)
        orientation = 2;
  }
  else if (orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row-1,nf.col-2, true, nf.type}; //(1,2)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col+1, true, nf.type}; //(2,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row-1,nf.col, true, nf.type}; //(2,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-2,nf.col-1, true, nf.type}; //(2,2)
        orientation = 3;
  }
}
