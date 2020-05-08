#ifndef CELL_H
#define CELL_H
#include "info.h"
#include "subject.h"

class Cell : public Subject {
  Info info;
public:
  Cell (int row, int col, bool isOccupied, std::string type);
  Cell (const Cell &other);
  Cell &operator=(const Cell &other);
  Cell (Cell &&other);
  Cell &operator=(Cell &&other);

  // Setting a piece down on the board
  void setPiece(bool occupied, std::string newType);

  // Accessor Methods for Cell
  Info getInfo () const;
  int getRow (); //get row of cell
  int getCol (); //get col of cell
  bool isEmpty(); //check is cell is empty

  ~Cell ();

};

#endif
