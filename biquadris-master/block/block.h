#ifndef BLOCK_H
#define BLOCK_H
#include "../cell.h"
#include <vector>

class Block {
protected:
  std::vector <Cell> theBlock; //array of cells in block
  char letter; //letter representing a block
  int levelMade;
  int orientation; //orientation of block in rotation
  int cellsLeft;
public:
  void left (); //moves left
  void right (); //moves right
  void down (); //move block down
  void up (); //move block down
  //void drop (); we are going to have drop be called in grid itself

  // When deleting a row, you can call this on the block with a cell on that row
  //    and col
  int deleteCell (const int r, const int c); //deletes a cell
  void deleteBlock (); //deletes every cell in a block
  void cellOneDown (const int r); //moves every cell in a row 1 down

  //Accessor methods
  std::vector<Cell> getCells (); //get cells of a block
  char getLetter (); //get letter representing the block
  int getOrientation ();

  virtual void rotateClock () = 0;
  virtual void rotateCounterClock() = 0;
  virtual ~Block ();

};

#endif
