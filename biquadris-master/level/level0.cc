#include <fstream>
#include <iostream>
#include <cstdlib>
#include "level0.h"
#include <fstream>
#include <string>
#include <memory>
using namespace std;


Level0::Level0(string scriptfile1): scriptfile1{scriptfile1} {}
Level0::Level0(){}

Level0::~Level0(){}


Block * chooseBlock(string whichBlock){
  if (whichBlock == "Z") {
		return new ZBlock{0};
	} else if (whichBlock == "J") {
		return new JBlock{0};
	} else if (whichBlock == "T") {
		return new TBlock{0};
	} else if (whichBlock == "O") {
		return new OBlock{0};
	} else if (whichBlock == "I") {
		return new IBlock{0};
	} else if (whichBlock == "L") {
		return new LBlock{0};
	}
	return new SBlock{0};
}

Block * Level0::createBlock(){
  string blocktype;
  ifstream f1{scriptfile1};
    for (int i=0; i <= blockCount; i++){
      f1 >> blocktype;
      if (f1.eof()) {
        blockCount = 0;
        ifstream f1{scriptfile1};
        f1 >>blocktype;
        break;
      }
    }
    blockCount++;
    return chooseBlock(blocktype);
}
