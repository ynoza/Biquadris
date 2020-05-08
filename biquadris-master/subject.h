#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "info.h"
class Observer;
class Block;
class TextDisplay;

class Subject {
  std::vector<Observer*> observers;

 public:
  void attach(Observer *o);
  void updateScore (int scorep1, int scorep2, bool text);
  void notifyObservers();
  void setNext (char letterp1, char letterp2);
  void setLevel (int levelp1, int levelp2, bool text);
  void blind(bool theBlindp1, bool theBlindp2);
  void printDisplays (std::ostream &out, TextDisplay *td1, TextDisplay *td2, bool text);
  virtual Info getInfo() const;

  virtual ~Subject() = 0;
};

#endif
