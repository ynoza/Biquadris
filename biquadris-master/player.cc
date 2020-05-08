#include "player.h"
#include "block/block.h"
#include "level/level.h"

Player::~Player(){
  delete nextBlock;
}
