#include "game.h"
#include "./level/level0.h"
#include "./level/level1.h"
#include "./level/level2.h"
#include "./level/level3.h"
#include "./level/level4.h"
#include "./block/block.h"
#include "./block/gblock.h"
#include "graphicsdisplay.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>


using namespace std;

// Constructor for Game
Game::Game(string scriptfile1, string scriptfile2, int seed, int level, int highscore,
  bool textonly, bool bonus):
  scriptfile1{scriptfile1}, scriptfile2{scriptfile2}, seed{seed},
  highscore{highscore}, textonly{textonly},bonus{bonus}{
    (player1.gameGrid).init(false);
    (player2.gameGrid).init(false);
    player1.level = level;
    player2.level = level;
}

// getInput will check if 'input' is a substring of the string 'comparison'
//    this method is particularly useful for when a user types in something like
//    clock when they want to input clockwise
bool getInput(int *movement, string input, string comparison, bool *correctInput){
  istringstream ss{input};
  ss >> *movement;
  if (!(input[0] == '0') && *movement == 0) *movement = 1;
  ss >> input;
  if (*movement < 0) *movement = 0;

  int size = input.size();
  if (size == 1) return false;
  for (int i = 0; i < size; i ++){
    if (!(input[i] == comparison[i])) {
      *movement = 0;
      return false;
    }
  }
  *correctInput = true;
  return true;
}

string opposite(string op){
  string ret;
  int n;
  bool correctInput;
  if (getInput(&n, op, "down", &correctInput)) {
    ret+= std::to_string(n);
    ret+="up";
  }
  else if (getInput(&n, op, "right", &correctInput)){
    ret+= std::to_string(n);
    ret+="left";
  }
  else if (getInput(&n, op, "left", &correctInput)){
    ret+= std::to_string(n);
    ret+="right";
  }
  else if (getInput(&n, op, "levelup", &correctInput)){
    ret+= std::to_string(n);
    ret+="leveldown";
  }
  else if (getInput(&n, op, "leveldown", &correctInput)){
    ret+= std::to_string(n);
    ret+="levelup";
  }
  else if (getInput(&n, op, "clockwise", &correctInput)){
    ret+= std::to_string(n);
    ret+="counterclockwise";
  }
  else if (getInput(&n, op, "counterclockwise", &correctInput)){
    ret+= std::to_string(n);
    ret+="clockwise";
  }
  return ret;
}

Block * chartoblock(char force, int ll){
    if (force == 'Z') return new ZBlock{ll};
    else if (force == 'J') return new JBlock{ll};
    else if (force == 'T') return new TBlock{ll};
  	else if (force == 'O') return new OBlock{ll};
  	else if (force == 'I') return new IBlock{ll};
    else if (force == 'L') return new LBlock{ll};
  	else if (force == 'S') return new SBlock{ll};
  else {
    throw 1;
    return nullptr;
  }
}

// Main method that will play the program
int Game::play(){
  string input;
  int numCleared = 0; // Counts how many lines cleared
  int movement; // Counts if an input like '5left', and holds the 5
  bool sequence = false; // To see if the command sequence is true
  ifstream fileinput; // Will be the input that sequence takes
  bool correctInput = false;
  int dropcount = 0;
  bool und =false;
  bool rotateForHeavy = true;

  // Creating all the levels for Player 1 and Player 2
  auto level0p1 = make_unique<Level0>(scriptfile1);
  auto level1p1 = make_unique<Level1>(seed);
  auto level2p1 = make_unique<Level2>(seed);
  auto level3p1 = make_unique<Level3>(player1.randomSequence,scriptfile1,seed);
  auto level4p1 = make_unique<Level4>(player1.randomSequence,scriptfile1,seed);
  auto level0p2 = make_unique<Level0>(scriptfile2);
  auto level1p2 = make_unique<Level1>(seed);
  auto level2p2 = make_unique<Level2>(seed);
  auto level3p2 = make_unique<Level3>(player2.randomSequence,scriptfile2,seed);
  auto level4p2 = make_unique<Level4>(player2.randomSequence,scriptfile2,seed);

  // Will make the player's level equal to the level inputted by the player
  if (player1.level == 0) player1.theLevel = level0p1.get();
  else if (player1.level == 1) player1.theLevel = level1p1.get();
  else if (player1.level == 2) player1.theLevel = level2p1.get();
  else if (player1.level == 3) player1.theLevel = level3p1.get();
  else if (player1.level == 4) player1.theLevel = level4p1.get();
  if (player2.level == 0) player2.theLevel = level0p2.get();
  else if (player2.level == 1) player2.theLevel = level1p2.get();
  else if (player2.level == 2) player2.theLevel = level2p2.get();
  else if (player2.level == 3) player2.theLevel = level3p2.get();
  else if (player2.level == 4) player2.theLevel = level4p2.get();

  // Attaching a text display and a Graphics disaplay to the Player and the Game
  this->attach((player1.gameGrid).getTextDisplay());
  this->attach((player2.gameGrid).getTextDisplay());
  if (!textonly) {
    newGD = new GraphicsDisplay();
    this->attach(newGD);
  }

  // Initializes the grid for both players to have their blocks ready
  updateScore(player1.score, player2.score, textonly);
  if (!textonly) newGD->updateHighScore(highscore);
  setLevel(player1.level, player2.level, textonly);
  player1.currBlock = (player1.theLevel)->createBlock();
  player2.currBlock = (player2.theLevel)->createBlock();
  (player1.gameGrid).addBlock(player1.currBlock);
  (player2.gameGrid).addBlock(player2.currBlock);
  player1.nextBlock = (player1.theLevel)->createBlock();
  player2.nextBlock = (player2.theLevel)->createBlock();
  setNext(player1.nextBlock->getLetter(), player2.nextBlock->getLetter());
  if (!textonly) newGD->playerTurn(true);
  printDisplay(out);

  Player * thePlayer = nullptr;
  while (1){
    // thePlayer is initialzed
    if (turn) thePlayer = &player1;
    else thePlayer = &player2;
    numCleared = 0;

    vector<string> undoInputs;
    undoInputs.clear();

    while (1){
      // Will use the fileinput
      if (sequence && fileinput >> input){}
      else if (dropcount == 0){
        sequence = false;
        in >> input;
        if (in.eof()) throw 1;
        undoInputs.emplace_back(input);
      }
      if (bonus && thePlayer->level < 3 && getInput(&movement, input, "undo", &correctInput)){
        if (undoInputs.size() > 0) undoInputs.pop_back();
        int i = undoInputs.size();
        if (i > 0){
            string lastInput = undoInputs.back();
            undoInputs.pop_back();
            input = opposite(lastInput);
        }
      }

      if ((input == "L") ||(input == "I") || (input == "J") ||
        (input == "Z") || (input == "S") || (input == "T") || (input == "O")){
          (thePlayer->gameGrid).hideBlock(thePlayer->currBlock);
          Block * temp = chartoblock(input[0], thePlayer->level);
          if((thePlayer->gameGrid).endgamecondition(temp)){
            thePlayer->currBlock->deleteBlock();
            thePlayer->currBlock=chartoblock(input[0], thePlayer->level);
            (thePlayer->gameGrid).addBlock(thePlayer->currBlock);
            correctInput = true;
          }
          else (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
          delete temp;
      } else if (getInput(&movement, input, "restart", &correctInput)) {
        if (highscore < max(player1.score, player2.score)) highscore=max(player1.score, player2.score);
        return highscore;
      } else if (getInput(&movement, input, "levelup", &correctInput) && input.size() >= 6){
        (thePlayer->theLevel)->setBCZero();
        for (int i = 0; i < movement; i ++){
          thePlayer->level ++;
        }
        if (thePlayer->level > 4) thePlayer->level = 4;
        if (turn){
          if (thePlayer->level == 0) thePlayer->theLevel = level0p1.get();
          else if (thePlayer->level == 1) thePlayer->theLevel = level1p1.get();
          else if (thePlayer->level == 3) thePlayer->theLevel = level3p1.get();
          else if (thePlayer->level == 2) thePlayer->theLevel = level2p1.get();
          else if (thePlayer->level == 4) thePlayer->theLevel = level4p1.get();
        } else {
          if (thePlayer->level == 0) thePlayer->theLevel = level0p2.get();
          else if (thePlayer->level == 1) thePlayer->theLevel = level1p2.get();
          else if (thePlayer->level == 3) thePlayer->theLevel = level3p2.get();
          else if (thePlayer->level == 2) thePlayer->theLevel = level2p2.get();
          else if (thePlayer->level == 4) thePlayer->theLevel = level4p2.get();
        }
        setLevel(player1.level, player2.level, textonly);
      } else if (getInput(&movement, input, "leveldown", &correctInput) && input.size() >= 6){
        (thePlayer->theLevel)->setBCZero();
        for (int i = 0; i < movement; i ++){
          thePlayer->level --;
        }
        if (thePlayer->level < 0) thePlayer->level = 0;
        if (turn){
          if (thePlayer->level == 0) thePlayer->theLevel = level0p1.get();
          else if (thePlayer->level == 1) thePlayer->theLevel = level1p1.get();
          else if (thePlayer->level == 3) thePlayer->theLevel = level3p1.get();
          else if (thePlayer->level == 2) thePlayer->theLevel = level2p1.get();
          else if (thePlayer->level == 4) thePlayer->theLevel = level4p1.get();
        } else {
          if (thePlayer->level == 0) thePlayer->theLevel = level0p2.get();
          else if (thePlayer->level == 1) thePlayer->theLevel = level1p2.get();
          else if (thePlayer->level == 3) thePlayer->theLevel = level3p2.get();
          else if (thePlayer->level == 2) thePlayer->theLevel = level2p2.get();
          else if (thePlayer->level == 4) thePlayer->theLevel = level4p2.get();
        }
        setLevel(player1.level, player2.level, textonly);
      } else if (getInput(&movement, input, "sequence", &correctInput)){
        string infs;
        in >> infs;
        if (in.eof()) throw 1;

        sequence=true;
        fileinput.open(infs);
      } else if (getInput(&movement, input, "norandom", &correctInput) || input == "n"){
        string infs;
        in >> infs;
        if (in.eof()) throw 1;
        if (turn) scriptfile1=infs;
        else scriptfile2=infs;
        thePlayer->randomSequence=false;
        (thePlayer->theLevel)->changerandom(infs);
      } else if (getInput(&movement, input, "random", &correctInput)){
        thePlayer->randomSequence=true;
        (thePlayer->theLevel)->changerandom(scriptfile1);
      } else {
        (thePlayer->gameGrid).hideBlock(thePlayer->currBlock);
        if (getInput(&movement, input, "left", &correctInput) && input.size() >= 3) {
          for (int i = 0; i < movement; i++){
            (thePlayer->gameGrid).left(thePlayer->currBlock);
          }
        } else if (getInput(&movement, input, "right", &correctInput)) {
          for (int i = 0; i < movement; i++){
            (thePlayer->gameGrid).right(thePlayer->currBlock);
          }
        } else if (getInput(&movement, input, "down", &correctInput)){
          try {
            for (int i = 0; i < movement; i++){
              (thePlayer->gameGrid).down(thePlayer->currBlock);
            }
          } catch (...){}
        } else if (bonus && !und && getInput(&movement, input, "up", &correctInput)){
          try {
            for (int i = 0; i < movement; i++){
              (thePlayer->gameGrid).up(thePlayer->currBlock);
            }
          } catch (...){}
        } else if (dropcount > 0 || getInput(&movement, input, "drop", &correctInput)){
          if(movement > 1) dropcount = movement;
          if (dropcount > 0){
            if(dropcount > 1){
                if (turn) turn = false;
                else turn = true;
            }
            dropcount--;
          }
          while(1){
            try {
              (thePlayer->gameGrid).down(thePlayer->currBlock);
              (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
              (thePlayer->gameGrid).hideBlock(thePlayer->currBlock);
            } catch (...){
              (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
              numCleared += (thePlayer->gameGrid).clearRow(thePlayer->level, &(thePlayer->score));
              if (numCleared > 0) thePlayer->level4count=-1;
              if (highscore < max(player1.score,player2.score)) highscore=max(player1.score,player2.score);
              updateScore(player1.score, player2.score, textonly);
              if (!textonly) newGD->updateHighScore(highscore);
              break;
            }
          }
          break;
        } else if (getInput(&movement, input, "clockwise", &correctInput)) {
          for (int i = 0; i < movement; i++){
            (thePlayer->gameGrid).clockwise(thePlayer->currBlock);
          }
          rotateForHeavy = false;
        } else if (getInput(&movement, input, "counterclockwise", &correctInput)) {
          for (int i = 0; i < movement; i++){
            (thePlayer->gameGrid).counterclockwise(thePlayer->currBlock);
          }
          rotateForHeavy = false;
        } else if (undoInputs.size() > 0) undoInputs.pop_back();

        // This block will check if the level is greater than three, or if the
        //   the heavy function has been activiated, so that after the input has
        //   been put in it will drop
        if ((thePlayer->level >= 3 || thePlayer->heavy) && correctInput) {
          try {
            if (thePlayer->heavy && rotateForHeavy) {
              (thePlayer->gameGrid).down(thePlayer->currBlock);
              (thePlayer->gameGrid).down(thePlayer->currBlock);
            }
            if (thePlayer->level >= 3)  (thePlayer->gameGrid).down(thePlayer->currBlock);
          } catch (...) {
            (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
            numCleared += (thePlayer->gameGrid).clearRow(thePlayer->level, &(thePlayer->score));
            if (numCleared > 0) thePlayer->level4count=-1;
            if (highscore < max(player1.score,player2.score)) highscore=max(player1.score,player2.score);
            updateScore(player1.score, player2.score, textonly);
            if (!textonly) newGD->updateHighScore(highscore);
            numCleared += (thePlayer->gameGrid).clearRow(thePlayer->level, &thePlayer->score);
            if (numCleared > 0) thePlayer->level4count=-1;
            break;
          }
        }
        (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
      }
      rotateForHeavy = true;
      correctInput = false;
      printDisplay(out);
    }

    // Checks if the game is over
    if(!((thePlayer->gameGrid).endgamecondition(thePlayer->nextBlock))
         || (thePlayer->gameGrid).checkgeneralgameover()) {
      printDisplay(out);
      printWinner(player1.score,player2.score);
      break;
    }
    // Resetting certain variables
    rotateForHeavy = true;
    correctInput = false;
    turn = !turn;
    if (numCleared < 2 && !textonly) newGD->playerTurn(turn);
    else if (!textonly) newGD->playerTurn(!turn);
    blind (false, false);

    // Sets up that next turns blocks
    thePlayer->currBlock = thePlayer->nextBlock;
    (thePlayer->gameGrid).addBlock(thePlayer->currBlock);
    thePlayer->nextBlock = (thePlayer->theLevel)->createBlock();
    setNext(player1.nextBlock->getLetter(), player2.nextBlock->getLetter());

    // If the level is 4, then this block will print a star block based on
    //    the requirements
    if (thePlayer->level == 4) thePlayer->level4count++;
    if (thePlayer->level4count != 0 && thePlayer->level4count % 5 == 0){
      Block* gblock = new GBlock(thePlayer->level);
      (thePlayer->gameGrid).addBlock(gblock);
      (thePlayer->gameGrid).hideBlock(gblock);
      try {
        while(1) (thePlayer->gameGrid).down(gblock);
      }
      catch (...) {
        (thePlayer->gameGrid).setBlock(gblock);
        numCleared += (thePlayer->gameGrid).clearRow(thePlayer->level, &thePlayer->score);
        if (numCleared > 0) thePlayer->level4count=0;
      }
    }

    // If the number of lines is greater than 1, then it will accept input from
    //    the user in regards to special commands
    if (numCleared >= 2){
      turn = !turn;
      printDisplay(out);
      turn = !turn;
      out << "Enter a special move" << endl;
      in >> input;
      if (in.eof()) throw 1;
      if (input == "blind" && turn) blind(true, false);
      else if (input == "blind" && !turn)blind (false, true);
      else if (input == "force"){
        char force;
        in >> force;
        if (in.eof()) throw 1;
        // thePlayer is changed
        if (turn) thePlayer = &player1;
        else thePlayer = &player2;

        (thePlayer->gameGrid).hideBlock(thePlayer->currBlock);
        try{
          Block * temp = chartoblock(force, thePlayer->level);
          if((thePlayer->gameGrid).endgamecondition(temp)){
            thePlayer->currBlock->deleteBlock();
            thePlayer->currBlock=chartoblock(force, thePlayer->level);
            (thePlayer->gameGrid).addBlock(thePlayer->currBlock);
          }
         delete temp;
        }
        catch(...) {
          (thePlayer->gameGrid).setBlock(thePlayer->currBlock);
        }
      } else if (input == "heavy") {
        if (turn) thePlayer = &player1;
        else thePlayer = &player2;
        thePlayer->heavy = true;
      }
      else if (input == "restart"){
        if (highscore < max(player1.score, player2.score)) highscore=max(player1.score, player2.score);
        return highscore;
      }
      if (numCleared < 2 && !textonly) newGD->playerTurn(!turn);
      else if (!textonly) newGD->playerTurn(turn);
      printDisplay(out);
    } else printDisplay(out);
  }
  // After game is over it asks if the player wants to play again
  string inp;
  out << "Do you want to play again? Type restart if you do." << endl;
  in >> inp;
  if (in.eof()) throw 1;
  if (inp == "restart") return highscore;
  else throw 1;
}


// After the game has been completed it will print a statement that indicates
//  who won
void Game::printWinner(int sp1, int sp2){
  if (sp1 > sp2) out << "-------Player-One-Has-Won-------" <<endl;
  else if (sp1 < sp2) out << "-------Player-Two-Has-Won-------" <<endl;
  else out << "-------It's-A-Tie-------" <<endl;
  if (!textonly) newGD->gameOver(sp1, sp2);
}

// Will print the displays
void Game::printDisplay(ostream& output){
  out << "       Highscore: "<< highscore << endl;
  if (turn) out << "        PLAYER 1 GO " << endl;
  else out << "        PLAYER 2 GO " << endl;
  this->printDisplays(output, (player1.gameGrid).getDisplay(), (player2.gameGrid).getDisplay(), textonly);
}

Game::~Game(){}
