#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "subject.h"
class TextDisplay;

class Observer {
 public:
  virtual void updateScore(int scorep1, int scorep2) = 0;
  virtual void setLevel(int levelp1, int levelp2) = 0;
  virtual void notify(Subject &whoNotified);
  virtual void printDisplays(std::ostream &out, TextDisplay &td1, TextDisplay &td2) = 0;
  virtual void setNext(char letter); //set the next block
  virtual void setBlind(bool theBlind); //set the grid to be blind and let the observers know that
  //prints the display
  virtual ~Observer() = default;
};

#endif
