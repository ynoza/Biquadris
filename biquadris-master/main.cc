#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  bool bonus = false;
  bool textonly = false; //default is with graphicsdisplay
  int startlevel = 0; //default
  int seed = 69; //random seed starting
  string scriptfile1 = "biquadris_sequence1.txt"; //given start seq player 1
  string scriptfile2 = "biquadris_sequence2.txt"; //give start seq player 2
    for (int i = 1; i < argc; ++i) {
        string theArg = argv[i];
        if (theArg == "-text") textonly = true;  //textonly argument
        if (theArg == "-enablebonus") bonus = true;  //textonly argument
        else if (theArg == "-seed"){
        i++;
          if (i < argc){
            int part2 = stoi(argv[i]);
            seed = part2;
          }
        }
        else if (theArg == "-scriptfile1"){ //change scriptfile1 for level0
          i++;
            if (i < argc){
              string part2 = argv[i];
              scriptfile1=part2;
          }
        }
        else if (theArg == "-scriptfile2"){ //change scriptfile2 for level0
          i++;
            if (i < argc){
              string part2 = argv[i];
              scriptfile2=part2;
          }
        }
        else if (theArg == "-startlevel"){ //change the startinglevel for the game
          i++;
            if (i < argc){
              string part2 = argv[i];
              istringstream ss{part2};
              ss >> startlevel;
              if (startlevel < 0 || startlevel > 4) startlevel = 0; //only 4 levels
          }
        }
    }
    int highscore = 0;
    while (1){
      try{
        Game theGame {scriptfile1, scriptfile2, seed, startlevel, highscore, textonly, bonus};
        highscore=theGame.play();
      } catch (...) {break;} //if they put invalid input wen asked to restart then they ll quit the game
    }
}
