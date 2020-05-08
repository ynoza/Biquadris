#include "level2.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Level2::Level2() {}
Level2::Level2(int seed):seed{seed} {srand(seed);}

Level2::~Level2() {}


Block* Level2::createBlock(){
  int random = rand() % 14;
  if (random == 0 || random == 1) return new JBlock{2};
  else if (random == 2 || random == 3) return new LBlock{2};
  else if (random == 4 || random == 5) return new TBlock{2};
  else if (random == 6 || random == 7) return new OBlock{2};
  else if (random == 8 || random == 9) return new IBlock{2};
  else if (random == 10 || random == 11) return new SBlock{2};
  return new ZBlock{2};
}
