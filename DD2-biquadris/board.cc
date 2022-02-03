#include "board.h"

#include <cmath>
#include <string>

using namespace std;

const int width = 11;
const int height = 18;

Board::Board()
    : currBlock{nullptr},
      nextBlock{nullptr},
      levels{0},
      lastClear{0},
      blind{false},
      heavy{false} {
  init();
}

void Board::init() {
  for (int i = 0; i < height; ++i) {
    vector<Cell *> vec;
    for (int j = 0; j < width; ++j) {
      Cell *newCell = new Cell(i, j);
      vec.push_back(newCell);
    }
    theGrid.push_back(vec);
  }
}

void Board::clearBoard() {
  delete currBlock;  // delete the currBlock in the grid
  currBlock = nullptr;
  delete nextBlock;
  nextBlock = nullptr;

  for (auto &blocks : blockList) {
    delete blocks;
  }
  blockList.clear();

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      delete theGrid[i][j];  // delete the cell in the grid
    }
  }
  theGrid.clear();
}

bool Board::isRowFull(int row) {
  for (int j = 0; j < width; ++j) {
    if (!theGrid[row][j]->fullyFilled()) {
      return false;
    }
  }
  return true;
}

void Board::entireRowClear(int row) {
  for (int j = 0; j < width; ++j) {
    theGrid[row][j]->setLetter("");
  }
}

int Board::dropBlock(int &linesCleared) {
  int numLines = 0;
  int scoredPoints = 0;
  currBlock->drop();
  blockList.push_back(currBlock);

  int blockRow = currBlock->getBottomLeftCell()->getCurrRow();
  while (isRowFull(blockRow)) {
    numLines += 1; 
    EntireRowCopy(blockRow - 1, blockRow);
    scoredPoints += updateBlockList();
    for (int i = blockRow - 1; i > 2; --i) {
      EntireRowCopy(i - 1, i);
    }
  }
  currBlock = nullptr;

  // reset special actions
  blind = false;
  heavy = false;

  if (numLines > 0) {
    if (levels == 4) {
      lastClear = 0;
    }
    linesCleared = numLines;
    scoredPoints += pow(numLines + levels, 2);
    return scoredPoints;
  } else {
    if (levels == 4) {
      lastClear++;
    }
    return 0;
  }
}

string Board::getLine(int row) {
  string result = "";
  for (int j = 0; j < width; ++j) {
    if (blind && row >= 2 && row <= 11 && j >= 2 && j <= 8) {
      result += "?";
    } else if (theGrid[row][j]->fullyFilled()) {
      result += theGrid[row][j]->getLetter();
    } else {
      result += ".";
    }
  }
  return result;
}

Blocks *Board::getCurrentBlock() { return currBlock; }

Blocks *Board::getNextBlock() { return nextBlock; }

void Board::EntireRowCopy(int rowOne, int rowTwo) {
  for (int j = 0; j < width; ++j) {
    // Copies data of first row into second row
    theGrid[rowTwo][j]->copyData(theGrid[rowOne][j]);
  }
  entireRowClear(rowOne);
}

int Board::updateBlockList() {
  int scoredPoints = 0;
  for (int i = 0; i < blockList.size(); ++i) {
    int score = blockList[i]->updateBlock();
    if (score > 0) {
      delete blockList[i];
      blockList.erase(blockList.begin() + i);
      i -= 1;
    }
    scoredPoints += score;
  }
  return scoredPoints;
}

void Board::setLevel(int newLevel) {
  levels = newLevel;
  lastClear = 0;
}

void Board::generateNewBlock(Blocks *newBlock) {
  if (!nextBlock) {  
    nextBlock = newBlock;
    return;
  }

  delete currBlock;

  currBlock = nextBlock;
  nextBlock = newBlock;
  currBlock->init(theGrid[3][0], theGrid);
}

void Board::changeBlock(Blocks *newBlock) {
  delete currBlock;

  currBlock = newBlock;
  if (currBlock->getType() == "*") {
    currBlock->init(theGrid[3][5], theGrid);
  } else {
    currBlock->init(theGrid[3][0], theGrid);
  }
}

void Board::setBlind() { blind = true; }

void Board::setHeavy() { heavy = true; }

int Board::isHeavy() { return heavy ? 2 : 0; }

bool Board::shouldDropStar() {
  // if levels 4 and last clear was a multiple of 5, drop a blocks 
  return (levels == 4) && (lastClear % 5 == 0);
}

Board::~Board() { this->clearBoard(); }
