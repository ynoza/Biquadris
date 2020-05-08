#include "jblock.h"

JBlock::JBlock(int levelMade) {
  this->levelMade=levelMade;
  orientation=0;
  cellsLeft=4;
  letter ='J';
  theBlock.emplace_back(Cell{2,0,true,"JBlock"});
  theBlock.emplace_back(Cell{3,0,true,"JBlock"});
  theBlock.emplace_back(Cell{3,1,true,"JBlock"});
  theBlock.emplace_back(Cell{3,2,true,"JBlock"});
}

void JBlock::rotateClock(){
  if(orientation == 0){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row-1,nf.col+1, true, nf.type}; //(0,1)
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
        theBlock[0] = Cell {nf.row+2,nf.col+1, true, nf.type}; //(2,2)
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
        theBlock[0] = Cell {nf.row,nf.col-2, true, nf.type}; //(2,0)
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
        theBlock[0] = Cell {nf.row-1,nf.col, true, nf.type}; //(1,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col-1, true, nf.type}; //(2,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row+1,nf.col, true, nf.type}; //(2,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row+2,nf.col+1, true, nf.type}; //(2,2)
        orientation = 0;
  }
}


void JBlock::rotateCounterClock(){ // In this one the corrdinates given
  //is the starting ones, and the coordinates above refer to where they are ebing switched to
  if(orientation == 1){
        Info nf = theBlock[0].getInfo();
        theBlock[0] = Cell {nf.row+1,nf.col-1, true, nf.type}; //(0,1)
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
        theBlock[0] = Cell {nf.row-2,nf.col-1, true, nf.type}; //(2,2)
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
        theBlock[0] = Cell {nf.row,nf.col+2, true, nf.type}; //(2,0)
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
        theBlock[0] = Cell {nf.row+1,nf.col, true, nf.type}; //(1,0)
        nf = theBlock[1].getInfo();
        theBlock[1] = Cell {nf.row,nf.col+1, true, nf.type}; //(2,0)
        nf = theBlock[2].getInfo();
        theBlock[2] = Cell {nf.row-1,nf.col, true, nf.type}; //(2,1)
        nf = theBlock[3].getInfo();
        theBlock[3] = Cell {nf.row-2,nf.col-1, true, nf.type}; //(2,2)
        orientation = 3;
  }
}
