#include "graphicsdisplay.h"
#include <iostream>
#include <sstream>

using namespace std;

// Initializes the GraphicsDisplay with a blue background
GraphicsDisplay::GraphicsDisplay(): xw{490, 500}{
  xw.drawString(100, 20, "Level: ");
  xw.drawString(100, 35, "Score: ");
  xw.drawString(360, 20, "Level: ");
  xw.drawString(360, 35, "Score: ");
  xw.drawString(10, 425, "Next: ");
  xw.drawString(280, 425, "Next: ");
  xw.drawString(210, 10, "Highscore: ");
  xw.fillRectangle (0, 45, 220, 3, 2);
  xw.fillRectangle (270, 45, 230, 3, 2);
  xw.fillRectangle (0, 400, 220, 3, 2);
  xw.fillRectangle (270, 400, 230, 3, 2);
}

void GraphicsDisplay::gameOver(int sp1, int sp2){

  //xw.fillRectangle(220, 220, 40, 20, 8);
  if (sp1 > sp2){
    xw.fillRectangle(190,20, 130, 20, 3);
    xw.drawString(200, 35, "PLAYER ONE HAS WON");
  } else if (sp2 > sp1){
    xw.fillRectangle(190, 20, 130, 20, 3);
    xw.drawString (200, 35, "PLAYER TWO HAS WON");
  } else {
    xw.fillRectangle(205,20, 80, 20, 3);
    xw.drawString (215, 35, "IT'S A TIE");
  }
  xw.fillRectangle(500, 100, 10, 10, 2);

}


//prints the general display
void GraphicsDisplay::printDisplays (ostream &out, TextDisplay &td1, TextDisplay &td2){
  vector<vector<char>> p1 = td1.getTheDisplay(); //for player 1
  vector<vector<char>> p2 = td2.getTheDisplay(); //for player 2
  bool blindp1 = td1.getBlind(); //check if player 1 should be blind
  bool blindp2 = td2.getBlind();
  int size1 = p1.size();
  int size2 = p1[0].size();
  for (int i = 3; i < size1; i ++){
    if (i == 21 || i == 20) continue;
    for (int j = 0; j < size2; j ++){
      if (blindp1 && j >= 2 && j <= 8 && i >= 5 && i <= 17) {
        xw.fillRectangle(j* 20, i*20, 20, 20, 2);
      } else if (p1[i][j]  == 'L') { //for blocks
        xw.fillRectangle(j* 20, i*20, 20, 20, 1);
      }
      else if (p1[i][j]  == 'S'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 8);
      }
      else if (p1[i][j]  == 'J'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 3);
      }
      else if (p1[i][j]  == 'O'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 4);
      }
      else if (p1[i][j]  == 'I'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 5);
      }
      else if (p1[i][j]  == 'Z'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 6);
      }
      else if (p1[i][j]  == 'T'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 7);
      }
      else if (p1[i][j] == '*'){
        xw.fillRectangle(j* 20, i*20, 20, 20, 9);
      } else xw.fillRectangle(j* 20, i*20, 20, 20, 0);
    }
  }

  size1 = p2.size();
  size2 = p2[0].size();
  for (int i = 3; i < size1; i ++){
    if (i == 21 || i == 20) continue;
    for (int j = 0; j < size2; j ++){
      if (blindp2 && j >= 2 && j <= 8 && i >= 5 && i <= 17) {
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 2);
      } else if (p2[i][j]  == 'L') {
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 1);
      }
      else if (p2[i][j]  == 'S'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 8);
      }
      else if (p2[i][j]  == 'J'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 3);
      }
      else if (p2[i][j]  == 'O'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 4);
      }
      else if (p2[i][j]  == 'I'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 5);
      }
      else if (p2[i][j]  == 'Z'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 6);
      }
      else if (p2[i][j]  == 'T'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 7);
      }
      else if (p2[i][j] == '*'){
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 9);
      }
      else {
        xw.fillRectangle(j* 20+ 270, i*20, 20, 20, 0);
      }
    }
  }
}

void GraphicsDisplay::updateScore(int scorep1, int scorep2){
  xw.clearRectangle(140, 25, 50, 15);
  xw.clearRectangle(400, 25, 50, 15);

  stringstream ss1, ss2;
  ss1 << scorep1;
  string s1, s2;
  ss1 >> s1;
  ss2 << scorep2;
  ss2 >> s2;

  xw.drawString(140, 36, s1);
  xw.drawString(400, 36, s2);
}

void GraphicsDisplay::setLevel (int levelp1, int levelp2) {
  xw.clearRectangle(140, 10, 50, 15);
  xw.clearRectangle(400, 10, 50, 15);

  stringstream ss1, ss2;
  ss1 << levelp1;
  string s1, s2;
  ss1 >> s1;
  ss2 << levelp2;
  ss2 >> s2;

  xw.drawString(140, 21, s1);
  xw.drawString(400, 21, s2);
}

void GraphicsDisplay::updateHighScore(int highscore){
  xw.clearRectangle(270, 0, 50, 15);
  stringstream ss;
  ss << highscore;
  string s;
  ss >> s;
  xw.drawString(274, 11, s);
}

void GraphicsDisplay::playerTurn(bool turn){
  xw.clearRectangle(30, 30, 40, 10);
  xw.clearRectangle(430, 30, 40, 10);

  if (turn){
    xw.fillRectangle(30, 30, 40, 10, 2);
    //xw.drawString(264, 11, s);
  } else {
    xw.fillRectangle(430, 30, 40, 10, 2);
  }

}
