#ifndef INFO_H
#define INFO_H
#include <string>

struct Info {
  int row;
  int col;
  bool isOccupied;
  std::string type; //the type of block it is
  Info (int row, int col, bool isOccupied, std::string type);
  Info (const Info &other);
  Info &operator= (const Info &other);
};

#endif
