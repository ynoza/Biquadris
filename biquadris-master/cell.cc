#include "cell.h"
#include <utility>

using namespace std;
//ctor
Cell::Cell (int row, int col, bool isOccupied, string type):
  info{row, col, isOccupied, type}{}

//copy ctor
Cell::Cell (const Cell &other): Subject{}, info{other.info.row, other.info.col,
                                     other.info.isOccupied, other.info.type}{}


//Copy assignment
Cell &Cell::operator=(const Cell &other){
  Info cellInfo = other.getInfo();
  info.row = cellInfo.row;
  info.col = cellInfo.col;
  info.isOccupied = cellInfo.isOccupied;
  info.type = cellInfo.type;
  return *this;
}

//move operator
Cell::Cell (Cell &&other): info{other.info}{}
Cell &Cell::operator=(Cell &&other){
  using std::swap;
  swap (info, other.info);
  return *this;
}

// Will nottify textdisplay and graphicsdisplay and set the piece
void Cell::setPiece(bool occupied, string newType){
  info.isOccupied = occupied;
  info.type = newType;
  this->notifyObservers();
}

Info Cell::getInfo () const { return info; } //get general info of a cell
int Cell::getRow(){return info.row;} //get row pos of cell
int Cell::getCol(){return info.col;} //get col pol of cell
//check if a cell is empty, meaning it does not have a block on it
bool Cell::isEmpty (){
  if (info.type == "Empty") return true;
  return false;
}

Cell::~Cell(){}
