#include "level1.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Level1::Level1() {}
Level1::Level1(int seed):seed{seed} {srand(seed);}

Level1::~Level1() {}


Block* Level1::createBlock(){
  int random = rand() % 12;
  if (random == 0 || random == 1) return new JBlock{1};
  else if (random == 2 || random == 3) return new LBlock{1};
  else if (random == 4 || random == 5) return new TBlock{1};
  else if (random == 6 || random == 7) return new OBlock{1};
  else if (random == 8 || random == 9) return new IBlock{1};
  else if (random == 10) return new SBlock{1};
  return new ZBlock{1};
}
