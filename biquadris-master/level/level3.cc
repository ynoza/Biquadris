#include "level3.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

Level3::Level3(){}

Level3::Level3(bool random, std::string scriptfile1, int seed): random{random},
scriptfile1{scriptfile1}, seed{seed}{srand(seed);}

void Level3::changerandom(string scriptfile){
  if (random) random = false;
  else random = true;
  scriptfile1 = scriptfile;
}


Level3::~Level3() {}

Block * chooseBlockl3(string whichBlock){
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

Block * Level3::createBlock(){
  if (random){
    int rando = rand() % 9;
    if (rando == 0 || rando == 1) return new SBlock{3};
    else if (rando == 2 || rando == 3) return new ZBlock{3};
    else if (rando == 4) return new TBlock{3};
    else if (rando == 5) return new OBlock{3};
    else if (rando == 6) return new IBlock{3};
    else if (rando == 7) return new JBlock{3};
    return new LBlock{3};
  } else {
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
		return chooseBlockl3(blocktype);
  }
}
