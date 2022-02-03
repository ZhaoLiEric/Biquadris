#include "blocks.h"

#include <cmath>
using namespace std;

Blocks::~Blocks() {}

int Blocks::updateBlock() {
  int score = 0;
  for (int i = 0; i < blockCells.size(); i++) {
    // delete cell from currBlock if it has been deleted
    if (!(blockCells[i]->fullyFilled())) {
      blockCells.erase(blockCells.begin() + i);
      i -= 1;
    }
  }
  if (blockCells.size() == 0) {
    score += pow(levels + 1, 2);
  }
  return score;
}

void Blocks::setLevel(int newLevel) { levels = newLevel; }
