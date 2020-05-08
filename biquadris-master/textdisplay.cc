#include "textdisplay.h"
#include "info.h"

using namespace std;

// Initializes textdisplay in contructor call
TextDisplay::TextDisplay(){
  blind = false;
  for (int rowNum = 0; rowNum < 25; ++ rowNum){
    vector<char> v;
    theDisplay.emplace_back(v);
    for (int colNum = 0; colNum < 11; ++ colNum){
      char dash = ' ';
      (theDisplay[rowNum]).emplace_back(dash);
    }
  }
  theDisplay[0][0] = 'L';
  theDisplay[0][1] = 'e';
  theDisplay[0][2] = 'v';
  theDisplay[0][3] = 'e';
  theDisplay[0][4] = 'l';
  theDisplay[0][5] = ':';
  theDisplay[1][0] = 'S';
  theDisplay[1][1] = 'c';
  theDisplay[1][2] = 'o';
  theDisplay[1][3] = 'r';
  theDisplay[1][4] = 'e';
  theDisplay[1][5] = ':';
  for (int i = 0; i < 11; i ++){
    theDisplay[2][i] = '-';
    theDisplay[20][i] = '-';
  }
  theDisplay[21][0] = 'N';
  theDisplay[21][1] = 'e';
  theDisplay[21][2] = 'x';
  theDisplay[21][3] = 't';
  theDisplay[21][4] = ':';
}

void TextDisplay::updateScore (int scorep1, int scorep2){
  int i = 10;
  theDisplay[1][10] = '0';
  while (scorep1 > 0){
    int digit = scorep1 % 10;
    if (digit == 0) theDisplay[1][i] = '0';
    else if (digit == 1) theDisplay[1][i] = '1';
    else if (digit == 2) theDisplay[1][i] = '2';
    else if (digit == 3) theDisplay[1][i] = '3';
    else if (digit == 4) theDisplay[1][i] = '4';
    else if (digit == 5) theDisplay[1][i] = '5';
    else if (digit == 6) theDisplay[1][i] = '6';
    else if (digit == 7) theDisplay[1][i] = '7';
    else if (digit == 8) theDisplay[1][i] = '8';
    else if (digit == 9) theDisplay[1][i] = '9';
    i --;
    scorep1 = scorep1 / 10;
  }
}
//setting up the nextblock
void TextDisplay::setNext (char letter){
  for (int i = 0; i < 5; i ++){
    theDisplay[22][i] = ' ';
    theDisplay[23][i] = ' ';
  }
  if (letter == 'I'){
    theDisplay[22][0] = 'I';
    theDisplay[22][1] = 'I';
    theDisplay[22][2] = 'I';
    theDisplay[22][3] = 'I';
  } else if (letter == 'L') {
    theDisplay[22][2] = 'L';
    theDisplay[23][2] = 'L';
    theDisplay[23][1] = 'L';
    theDisplay[23][0] = 'L';
  } else if (letter == 'O') {
    theDisplay[22][0] = 'O';
    theDisplay[22][1] = 'O';
    theDisplay[23][0] = 'O';
    theDisplay[23][1] = 'O';
  } else if (letter == 'S') {
    theDisplay[22][2] = 'S';
    theDisplay[22][1] = 'S';
    theDisplay[23][1] = 'S';
    theDisplay[23][0] = 'S';
  } else if (letter == 'Z') {
    theDisplay[22][0] = 'Z';
    theDisplay[22][1] = 'Z';
    theDisplay[23][1] = 'Z';
    theDisplay[23][2] = 'Z';
  } else if (letter == 'T') {
    theDisplay[22][0] = 'T';
    theDisplay[22][1] = 'T';
    theDisplay[22][2] = 'T';
    theDisplay[23][1] = 'T';
  } else if (letter == 'J') {
    theDisplay[22][0] = 'J';
    theDisplay[23][2] = 'J';
    theDisplay[23][1] = 'J';
    theDisplay[23][0] = 'J';
  }
}
//set the level
void TextDisplay::setLevel(int levelp1, int levelp2){
  if (levelp1 == 0) theDisplay[0][10] = '0';
  else if (levelp1 == 1) theDisplay[0][10] = '1';
  else if (levelp1 == 2) theDisplay[0][10] = '2';
  else if (levelp1 == 3) theDisplay[0][10] = '3';
  else theDisplay[0][10] = '4';
}

void TextDisplay::setBlind(bool theBlind){ blind = theBlind; }
//notify the subjects nearby
void TextDisplay::notify(Subject &whoNotified){
  Info newInfo = whoNotified.getInfo();
  if (newInfo.isOccupied){
    if (newInfo.type == "LBlock") theDisplay[newInfo.row+3][newInfo.col] = 'L';
    else if (newInfo.type == "SBlock") theDisplay[newInfo.row+3][newInfo.col] = 'S';
    else if (newInfo.type == "JBlock") theDisplay[newInfo.row+3][newInfo.col] = 'J';
    else if (newInfo.type == "OBlock") theDisplay[newInfo.row+3][newInfo.col] = 'O';
    else if (newInfo.type == "IBlock") theDisplay[newInfo.row+3][newInfo.col] = 'I';
    else if (newInfo.type == "ZBlock") theDisplay[newInfo.row+3][newInfo.col] = 'Z';
    else if (newInfo.type == "TBlock") theDisplay[newInfo.row+3][newInfo.col] = 'T';
    else if (newInfo.type == "GBlock") theDisplay[newInfo.row+3][newInfo.col] = '*';
  } else {
    theDisplay[newInfo.row+3][newInfo.col] = ' ';
  }
}

TextDisplay::~TextDisplay(){}

vector<vector<char>> TextDisplay::getTheDisplay () { return theDisplay; }
bool TextDisplay::getBlind() { return blind; }

void TextDisplay::printDisplays (ostream &out, TextDisplay &td1, TextDisplay &td2){
  for (int rowNum = 0; rowNum < 25; ++ rowNum){
    for (int colNum = 0; colNum < 11; ++ colNum){
      if (td1.blind && colNum >= 2 && colNum <= 8 && rowNum >= 5 && rowNum <= 17){
        out << '?';
      } else {
        out << td1.theDisplay[rowNum][colNum];
      }
    }
    out <<"      ";
    for (int colNum = 0; colNum < 11; ++ colNum){
      if (td2.blind && colNum >= 2 && colNum <= 8 && rowNum >= 5 && rowNum <= 17){
        out << '?';
      } else {
        out << td2.theDisplay[rowNum][colNum];
      }
    }
    out << endl;
  }
} //ostream works for special blind and for regular output
ostream &operator<<(ostream &out, const TextDisplay &td){
  for (int rowNum = 0; rowNum < 25; ++ rowNum){
    for (int colNum = 0; colNum < 11; ++ colNum){
      if (td.blind && colNum >= 2 && colNum <= 8 && rowNum >= 5 && rowNum <= 17){
        out << '?';
      } else {
        out << td.theDisplay[rowNum][colNum];
      }
    }
    out << endl;
  }
  return out;
}
