#include "iblock.h"

using namespace std;

IBlock::IBlock(int levelVal) {
  this->bottomLeftCell = nullptr;
  this->rotation = 0;
  this->maxWidth = 4;
  this->levels = levelVal;
}

void IBlock::init(Cell *cell, vector<vector<Cell *>> grid) {
  bottomLeftCell = cell;
  blockGrid = grid;
  if (isLostGame()) {
    throw runtime_error("Game Over");
  }
  // create pointers to cells in the currBlock
  bottomLeftCell->setLetter("I");
  Cell *firstCell = blockGrid[3][1];
  firstCell->setLetter("I");
  Cell *secondCell = blockGrid[3][2];
  secondCell->setLetter("I");
  Cell *thirdCell = blockGrid[3][3];
  thirdCell->setLetter("I");
  // add to vector
  blockCells.push_back(bottomLeftCell);
  blockCells.push_back(firstCell);
  blockCells.push_back(secondCell);
  blockCells.push_back(thirdCell);
}

bool IBlock::isLostGame() {
  if (bottomLeftCell->fullyFilled() || blockGrid[3][1]->fullyFilled() ||
      blockGrid[3][2]->fullyFilled() || blockGrid[3][3]->fullyFilled()) {
    return true;
  }
  return false;
}

string IBlock::getType() const { return "I"; }

Cell *IBlock::getBottomLeftCell() const { return bottomLeftCell; }

vector<Cell *> IBlock::getBlockCells() const { return blockCells; }

bool IBlock::canValidMove(vector<Cell *> newBlockCells) const {
  for (int i = 0; i < blockCells.size(); i++) {
    blockCells[i]->setLetter(
        "");  // set old currBlock cells to empty letter
  }
  for (int i = 0; i < newBlockCells.size(); i++) {
    //check if that cell is already occupied by another currBlock
    if (newBlockCells[i]->fullyFilled()) { 
                                            
      for (int i = 0; i < blockCells.size(); i++) {
        blockCells[i]->setLetter(
            "I");  
      }
      return false;
    }
  }
  return true; 
}

bool IBlock::replaceCells(vector<Cell *> cells, string letter) {
  if (canValidMove(cells)) {
    for (int i = 0; i < blockCells.size(); i++) {
      cells[i]->setLetter(letter);
    }
    bottomLeftCell = cells[0];  
    blockCells.clear();        
    blockCells = cells;       
    return true;
  }
  return false;
}

vector<Cell *> IBlock::getPositionZero() {
  int bottomLeftRow = bottomLeftCell->getCurrRow();
  int bottomLeftCol = bottomLeftCell->getCurrCol();
  vector<Cell *> tempCells;
  tempCells.push_back(bottomLeftCell);
  tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
  tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
  tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 3]);
  return tempCells;
}

vector<Cell *> IBlock::getPositionOne() {
  int bottomLeftRow = bottomLeftCell->getCurrRow();
  int bottomLeftCol = bottomLeftCell->getCurrCol();
  vector<Cell *> tempCells;
  tempCells.push_back(bottomLeftCell);
  tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
  tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
  tempCells.push_back(blockGrid[bottomLeftRow - 3][bottomLeftCol]);
  return tempCells;
}

void IBlock::clockwise(int dropAmount) {
  vector<Cell *> newRotation;
  if (rotation == 0 || rotation == 2) {  
    try {
      newRotation = getPositionOne();
    } catch (...) {
      return;
    }
    if (canValidMove(newRotation)) {
      maxWidth = 1;
      rotation++;
      down(dropAmount);
    }
  } else if (rotation == 1 ||
             rotation == 3) {  
    if (bottomLeftCell->getCurrCol() + 4 > 10) {
      return;  
    }
    try {
      newRotation = getPositionZero();
    } catch (...) {
      return;
    }
    if (canValidMove(newRotation)) {
      maxWidth = 4;
      if (rotation == 1)
        rotation++;
      else
        rotation = 0;
    }
  }
  if (replaceCells(newRotation, "I")) down(dropAmount);
}

void IBlock::counterclockwise(int dropAmount) { clockwise(dropAmount); }

void IBlock::left(int dropAmount) {
  if (bottomLeftCell->getCurrCol() == 0) {
    return;  
  }
  vector<Cell *> newMovement;
  int curRow, curCol;
  for (int i = 0; i < blockCells.size(); i++) {
    curRow = blockCells[i]->getCurrRow();
    curCol = blockCells[i]->getCurrCol();
    newMovement.push_back(blockGrid[curRow][curCol - 1]);
  }
  if (replaceCells(newMovement, "I")) down(dropAmount);
}

void IBlock::right(int dropAmount) {
  if (bottomLeftCell->getCurrCol() + maxWidth > 10) {
    return;  
  }
  vector<Cell *> newMovement;
  int curRow, curCol;
  for (int i = 0; i < blockCells.size(); i++) {
    curRow = blockCells[i]->getCurrRow();
    curCol = blockCells[i]->getCurrCol();
    newMovement.push_back(blockGrid[curRow][curCol + 1]);
  }
  if (replaceCells(newMovement, "I")) down(dropAmount);
}

bool IBlock::down(int dropAmount) {
  for (int i = 0; i < dropAmount; i++) {
    if (bottomLeftCell->getCurrRow() == 17) {
      return false;  
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++) {
      curRow = blockCells[i]->getCurrRow();
      curCol = blockCells[i]->getCurrCol();
      newMovement.push_back(blockGrid[curRow + 1][curCol]);
    }
    if (replaceCells(newMovement, "I"))
      continue;
    else
      return false;
  }
  return true;
}

bool IBlock::up(int dropAmount) {
  for (int i = 0; i < dropAmount; i++) {
    if (bottomLeftCell->getCurrRow() == 3) {
      return false;  
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++) {
      curRow = blockCells[i]->getCurrRow();
      curCol = blockCells[i]->getCurrCol();
      newMovement.push_back(blockGrid[curRow - 1][curCol]);
    }
    if (replaceCells(newMovement, "I"))
      continue;
    else
      return false;
  }
  return true;
}

void IBlock::drop() {
  while (down() == true) {
    continue;
  }
}

IBlock::~IBlock() {
  bottomLeftCell = nullptr;
  for (int i = 0; i < blockCells.size(); ++i) {
    blockCells[i]->setLetter("");
  }
  blockCells.clear();
}
