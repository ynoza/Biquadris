#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <iostream>
#include "observer.h"

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
  bool blind;
 public:
  TextDisplay();

  void notify(Subject &whoNotified);
  void updateScore (int scorep1, int scorep2);
  void setNext (char letter);
  void setLevel (int levelp1, int levelp2);
  void setBlind (bool theBlind);

  void printDisplays (std::ostream &out, TextDisplay &td1, TextDisplay &td2);

  std::vector<std::vector<char>> getTheDisplay ();
  bool getBlind ();

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
