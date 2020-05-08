#include <vector>
#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "./block/block.h"
#include <memory>

using namespace std;

Grid::~Grid(){
  delete td;
  for (auto b: blocksInGrid){
    delete b;
  }
}

// Initializes the grid to contain 198 cells 18x11 and have a textdisplay attached
//    as an observer
void Grid::init (bool bonus){
  //unique_ptr<TextDisplay> newT {new TextDisplay()};
  TextDisplay * newTd = new TextDisplay{};
  td = newTd;
  for (int rowNum = 0; rowNum < 18; ++ rowNum){
    vector<Cell> v;
    theGrid.emplace_back(v);
    for (int colNum = 0; colNum < 11; ++ colNum){
      (theGrid[rowNum]).emplace_back(Cell {rowNum, colNum, false, "Empty"});
    }
  }
  for (int rowNum = 0; rowNum < 18; ++ rowNum){
    for (int colNum = 0; colNum < 11; ++ colNum){
      theGrid[rowNum][colNum].attach(newTd);
    }
  }
}

// Will check all the rows to see if an entire row is full
//    if an entire row is full then it will delete the row
int Grid::clearRow(int level, int * score){
  int numDeleted = 0;
  for (int rowNum = 0; rowNum < 18; ++ rowNum){
    for (int colNum = 0; colNum < 11; ++ colNum){
      bool empty = theGrid[rowNum][colNum].isEmpty();
      if (empty) break;
      else if (!empty && colNum == 10){
        *score += deleteRow(rowNum);
        numDeleted ++;
        rowNum --; // Check the same row again after you move everything down
        break;
      }
    }
  }
  if (numDeleted >= 1){
    *score += (level + numDeleted) * (level + numDeleted);
  }
  return numDeleted;
}

// Actually delete the row and bring all the cells above this row down
int Grid::deleteRow (const int rowNum){
  int scoreIncrement = 0;
  int size = blocksInGrid.size();
  for (int colNum = 0; colNum < 11; ++ colNum){
    theGrid[rowNum][colNum].setPiece(false, "Empty");
    for (int i = 0; i < size; i ++){
      scoreIncrement += blocksInGrid[i]->deleteCell(rowNum, colNum);
    }
  }
  for (int i = rowNum; i >= 0; i --){
    for (int colNum = 0; colNum < 11; ++ colNum){
      if (!theGrid[i][colNum].isEmpty()){
        Info cellInfo = theGrid[i][colNum].getInfo();
        theGrid[i][colNum].setPiece(false, "Empty");
        theGrid[i+1][colNum].setPiece(true, cellInfo.type);
      }
    }
  }
  for (int i = 0; i < size; i ++){
    blocksInGrid[i]->cellOneDown(rowNum);
  }
  return scoreIncrement;
}

Observer * Grid::getTextDisplay(){ return td; }
TextDisplay * Grid::getDisplay(){ return td; }

// Moving a block left
void Grid::left (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    if (c.getCol() - 1 < 0) return;
    Info checkInfo = theGrid[c.getRow()][c.getCol()-1].getInfo();
    if (checkInfo.type != "Empty" || checkInfo.isOccupied){
      return;
    }
  }
  theBlock->left();
}
// Moving a block right
void Grid::right (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    if (c.getCol() + 1 > 10) return;
    Info checkInfo = theGrid[c.getRow()][c.getCol()+1].getInfo();
    if (checkInfo.type != "Empty" || checkInfo.isOccupied){
      return;
    }
  }
  theBlock->right();
}
// Moving a block down
void Grid::down (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    if (c.getRow() + 1 > 16) throw 1;
    Info checkInfo = theGrid[c.getRow()+1][c.getCol()].getInfo();
    if (checkInfo.type != "Empty" || checkInfo.isOccupied){ throw 1; }
  }
  theBlock->down();
}
//Moving block up
void Grid::up (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    if (theBlock->getLetter() == 'I' && c.getRow() - 1 < 3) throw 1;
    else if (c.getRow() - 1 < 2) throw 1;
    Info checkInfo = theGrid[c.getRow()-1][c.getCol()].getInfo();
    if (checkInfo.type != "Empty" || checkInfo.isOccupied){ throw 1; }
  }
  theBlock->up();
}
// Checking to see if the block will rotate properly given the blocks around it
bool Grid::rotateCheck (Block * theBlock, bool clockwise){
  char letter = theBlock->getLetter();
  vector<Cell> cells = theBlock->getCells();
  int orientation = theBlock->getOrientation();
  Info cell1 = cells[0].getInfo();
  Info cell2 = cells[1].getInfo();
  Info cell3 = cells[2].getInfo();
  Info cell4 = cells[3].getInfo();

  if (letter == 'I'){
    for (int i = 1; i < 4; i ++){
      if (orientation == 0){
        if (!theGrid[cell1.row-i][cell1.col].isEmpty()) return false;
      } else {
        if (cell1.col + i > 10) return false;
        if (!theGrid[cell1.row][cell1.col+i].isEmpty()) return false;
      }
    }
  } else if (letter == 'J' || letter == 'L'){
    for (int i = 1; i < 3; i ++){
      if (orientation == 1 && !clockwise && letter == 'L'){
        if (!theGrid[cell1.row][cell1.col+1].isEmpty()) return false;
        if (!theGrid[cell3.row][cell3.col+2].isEmpty()) return false;
      } else if (orientation == 3 && !clockwise && letter == 'L'){\
        if (!theGrid[cell1.row+1][cell1.col].isEmpty()) return false;
        if (!theGrid[cell1.row+2][cell1.col].isEmpty()) return false;
        if (!theGrid[cell3.row][cell3.col+1].isEmpty()) return false;
        return true;
      } else if (orientation == 0){
        if (!theGrid[cell2.row-i][cell2.col].isEmpty()) return false;
        if (!theGrid[cell3.row-i][cell3.col].isEmpty()) return false;
      } else if (orientation == 1){
        if (cell3.col+i > 10) return false;
        if (!theGrid[cell3.row][cell3.col+i].isEmpty()) return false;
        if (letter=='J' && !theGrid[cell4.row][cell4.col+i].isEmpty()) return false;
      } else if (orientation == 2){
        if (!theGrid[cell3.row+1][cell3.col].isEmpty()) return false;
        if (letter=='J' && !theGrid[cell4.row+1][cell4.col].isEmpty()) return false;
        if (letter=='L' && !theGrid[cell4.row-1][cell4.col].isEmpty()) return false;
        if (!theGrid[cell3.row-1][cell3.col].isEmpty()) return false;
        if (letter=='J' && !theGrid[cell3.row-2][cell3.col].isEmpty()) return false;
        return true;
      } else if (orientation == 3){
        if (letter == 'J'){
          if (!theGrid[cell1.row-1][cell1.col].isEmpty()) return false;
          if (!theGrid[cell2.row][cell2.col+1].isEmpty()) return false;
        } else if (letter == 'L'){
          if (cell2.col + 1 > 10) return false;
          if (!theGrid[cell2.row][cell2.col+1].isEmpty()) return false;
          if (!theGrid[cell3.row][cell3.col+1].isEmpty()) return false;
          if (!theGrid[cell2.row][cell2.col-1].isEmpty()) return false;
        }
        return true;
      }
    }
  } else if (letter == 'S'){
    if (orientation == 0){
      if (!theGrid[cell3.row-1][cell3.col].isEmpty()) return false;
      if (!theGrid[cell3.row-2][cell3.col].isEmpty()) return false;
    } else if (orientation == 1){
      if (cell4.col + 1 > 10) return false;
      if (!theGrid[cell3.row][cell3.col-1].isEmpty()) return false;
      if (!theGrid[cell4.row][cell4.col+1].isEmpty()) return false;
    }
  } else if (letter == 'Z'){
    if (orientation == 0){
      if (!theGrid[cell1.row+1][cell1.col].isEmpty()) return false;
      if (!theGrid[cell2.row-1][cell2.col].isEmpty()) return false;
    } else if (orientation == 1){
      if (cell4.col + 2 > 10) return false;
      if (!theGrid[cell4.row][cell4.col+1].isEmpty()) return false;
      if (!theGrid[cell4.row][cell4.col+2].isEmpty()) return false;
    }
  } else if (letter == 'T'){
    if (orientation == 0){
      if (!theGrid[cell2.row-1][cell2.col].isEmpty()) return false;
    } else if (orientation == 1){
      if (!theGrid[cell2.row][cell2.col+1].isEmpty()) return false;
    } else if (orientation == 2){
      if (!theGrid[cell2.row+1][cell2.col].isEmpty()) return false;
    } else if (orientation == 3){
      if (!theGrid[cell2.row][cell2.col-1].isEmpty()) return false;
    }
  }
  return true;
}

void Grid::clockwise (Block * theBlock){
  if (rotateCheck (theBlock, true)){
    theBlock->rotateClock();
  }
}
void Grid::counterclockwise (Block * theBlock){
  if (rotateCheck (theBlock, false)){
    theBlock->rotateCounterClock();
  }
}

void Grid::addBlock (Block * theBlock){
  blocksInGrid.emplace_back(theBlock);
  this->setBlock(theBlock);
}

void Grid::setBlock (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    Info cellInfo = c.getInfo();
    int rowNum = cellInfo.row;
    int colNum = cellInfo.col;
    theGrid[rowNum][colNum].setPiece(cellInfo.isOccupied, cellInfo.type);
  }
}


void Grid::hideBlock (Block * theBlock){
  vector<Cell> cells = theBlock->getCells();
  for (auto &c: cells){
    Info cellInfo = c.getInfo();
    int rowNum = cellInfo.row;
    int colNum = cellInfo.col;
    theGrid[rowNum][colNum].setPiece(false, "Empty");
  }
}


//use this to check before a block is dropped
bool Grid::checkgeneralgameover(){
  for(int i=0; i < 11; i++){
    if (!(theGrid[2][i].isEmpty())) return true;
  }
  return false;
}


bool Grid::endgamecondition(Block * nextBlock){
  if (nextBlock->getLetter() == 'I') return (theGrid[3][0].isEmpty() && theGrid[3][1].isEmpty()
      && theGrid[3][2].isEmpty() && theGrid[3][3].isEmpty());
  else if (nextBlock->getLetter() == 'Z') return (theGrid[3][1].isEmpty() && theGrid[3][2].isEmpty()
      && theGrid[2][0].isEmpty() && theGrid[2][1].isEmpty());
  else if (nextBlock->getLetter() == 'S') return (theGrid[3][1].isEmpty() && theGrid[3][0].isEmpty()
      && theGrid[2][2].isEmpty() && theGrid[2][1].isEmpty());
  else if (nextBlock->getLetter() == 'O') return (theGrid[3][0].isEmpty() && theGrid[3][1].isEmpty()
      && theGrid[2][0].isEmpty() && theGrid[2][1].isEmpty());
  else if (nextBlock->getLetter() == 'T') return (theGrid[2][0].isEmpty() && theGrid[2][1].isEmpty()
      && theGrid[2][2].isEmpty() && theGrid[3][1].isEmpty());
  else if (nextBlock->getLetter() == 'L') return (theGrid[3][0].isEmpty() && theGrid[3][1].isEmpty()
      && theGrid[3][2].isEmpty() && theGrid[2][2].isEmpty());
  return (theGrid[3][0].isEmpty() && theGrid[3][1].isEmpty() && theGrid[3][2].isEmpty()
      && theGrid[2][0].isEmpty());
}
