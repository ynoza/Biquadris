#include "block.h"
#include "../info.h"

using namespace std;

//Moves a block left
void Block::left (){
  for(auto &c:theBlock){ //go through every cell in block
    Info nf = c.getInfo();
    c = Cell {nf.row,nf.col-1, true, nf.type};
  }
}
//Moves a block down
void Block::right (){
  for(auto &c:theBlock){ //go through every cell in block
    Info nf = c.getInfo();
    c = Cell {nf.row,nf.col+1, true, nf.type};
  }
}
//Moves a block down
void Block::down (){
  for(auto &c:theBlock){ //go through every cell in block
    Info nf = c.getInfo();
    c = Cell {nf.row+1,nf.col, true, nf.type};
  }
}
//Movies block up
void Block::up (){
  for(auto &c:theBlock){ //go through every cell in block
    Info nf = c.getInfo();
    c = Cell {nf.row-1,nf.col, true, nf.type};
  }
}
//deletes every element of a block
void Block::deleteBlock (){
  for (auto &c: theBlock){ //go through every cell in block
    c = Cell {-1, -1, false, "Empty"}; //by changing the cell, the grid positions are invalid
  }
  cellsLeft=0;
}
//deletes a Cell
int Block::deleteCell (const int r, const int c){
  for (auto &cell: theBlock){ //go through every cell in block
    Info cellInfo = cell.getInfo();
    if (cellInfo.isOccupied){ //if its occupied then reduce the blocks by a cell
      if (cellInfo.row == r && cellInfo.col == c){
        cellsLeft -- ;
        cell = Cell {-1, -1, false, "Empty"};
        if (cellsLeft == 0) return (levelMade + 1) * (levelMade + 1); //need to know levelMade for score
        else return 0;
      }
    }
  }
  return 0;
}
//remove all cells in a row 1 down (taking in a row)
void Block::cellOneDown (const int r){
  for (auto &c: theBlock){
    Info cellInfo = c.getInfo();
    if (cellInfo.row <= r){
      c = Cell {cellInfo.row+1, cellInfo.col, cellInfo.isOccupied, cellInfo.type}; //updating the position of every cell
    }
  }
}
//rotating a block clockwise
void Block::rotateClock () {}
//rotating a block counterclockwise
void Block::rotateCounterClock() {}
//vector of cells in a block
vector<Cell> Block::getCells (){ return theBlock; }
//get letter that represents a block
char Block::getLetter(){ return letter; }
//the orientation in terms of the rotation
int Block::getOrientation(){ return orientation; }
//destructor
Block::~Block (){}
