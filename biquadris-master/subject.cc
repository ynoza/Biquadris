#include "subject.h"
#include "observer.h"
#include "textdisplay.h"
using namespace std;

Info Subject::getInfo() const {return Info{0, 0, false, "Empty"};}
//attach the observers to the vector
void Subject::attach(Observer *o){ observers.emplace_back(o);}
//uodate the subject for the grid
void Subject::updateScore(int scorep1, int scorep2, bool text){
  observers[0]->updateScore(scorep1, scorep2);
  observers[1]->updateScore(scorep2, scorep1);
  if (!text) observers[2]->updateScore(scorep1, scorep2);
}
//sets the next block
void Subject::setNext (char letterp1, char letterp2) {
  observers[0]->setNext(letterp1);
  observers[1]->setNext(letterp2);
}
//set the level of the grid
void Subject::setLevel (int levelp1, int levelp2, bool text) {
  observers[0]->setLevel(levelp1, levelp1);
  observers[1]->setLevel(levelp2, levelp2);
  if (!text) observers[2]->setLevel(levelp1, levelp2);
}
//sets up blind special feature for the grid afterwards
void Subject::blind(bool theBlindp1, bool theBlindp2) {
  observers[0]->setBlind(theBlindp1);
  observers[1]->setBlind(theBlindp2);
}

void Subject::printDisplays(ostream &out, TextDisplay *td1, TextDisplay *td2, bool text) {
  observers[0]->printDisplays(out, *td1, *td2);
  if (!text) observers[2]->printDisplays(out, *td1, *td2);
}
//notifys the observers
void Subject::notifyObservers(){
  for (auto &ob : observers) ob->notify(*this);
}

Subject::~Subject() {}
