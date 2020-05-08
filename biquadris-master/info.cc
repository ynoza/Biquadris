#include "info.h"

using namespace std;

//ctor
Info::Info (int row, int col, bool isOccupied, string type):
  row{row}, col{col}, isOccupied{isOccupied}, type{type}{}

Info::Info (const Info &other): row{other.row}, col{other.col},
  isOccupied{other.isOccupied}, type{other.type}{}

Info &Info::operator= (const Info &other){
  row = other.row;
  col = other.col;
  isOccupied = other.isOccupied;
  type = other.type;
  return *this;
}
