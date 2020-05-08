#ifndef GRID_H
#define GRID_H
#include <vector>
#include "cell.h"
#include <memory>
class Block;
class TextDisplay;
class GraphicsDisplay;

class Grid {
  std::vector<std::vector<Cell>> theGrid;
  std::vector <Block *> blocksInGrid;
  TextDisplay *td = nullptr;
public:
  void init (bool bonus);
  // Will delete the row and bring all cells above it down
  int deleteRow (const int rowNum);
  // Will check if a row is full and then call deleteRow to delete it
  int clearRow (int level, int * score);


  // For attaching
  Observer * getTextDisplay();
  // For printng
  TextDisplay * getDisplay();

  //To check rotate
  bool rotateCheck(Block * theBlock, bool clock);

  // For Blocks
  void left (Block * theBlock);
  void right (Block * theBlock);
  void down (Block * theBlock);
  void up (Block * theBlock);
  void clockwise (Block * theBlock);
  void counterclockwise (Block * theBlock);

  void addBlock (Block * theBlock);
  void setBlock (Block * theBlock);
  void hideBlock (Block * theBlock); //Used when moving block left, right, down

  bool endgamecondition(Block * theBlock);
  bool checkgeneralgameover();

  ~Grid();
};
#endif
