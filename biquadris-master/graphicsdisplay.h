#ifndef GRAPICSDISPLAY_H
#define GRAPICSDISPLAY_H
#include "window.h"
#include "observer.h"
#include "info.h"
#include "subject.h"
#include "textdisplay.h"

class GraphicsDisplay : public Observer{
  Xwindow xw;
public:
  GraphicsDisplay();
  void playerTurn (bool turn);
  void gameOver (int sp1, int sp2);
  void printDisplays (std::ostream &out, TextDisplay &td1, TextDisplay &td2);
  void updateScore (int scorep1, int scorep2); //update the score
  void setLevel (int levelp1, int levelp2); //change the level on grphics display
  void updateHighScore(int highscore); //change the highscore
  ~GraphicsDisplay(){}
};

#endif
