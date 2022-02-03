#include "player.h"

#include "levels.h"

using namespace std;

Player::Player(bool isPlayerOne, string sequence1, string sequence2) {
  this->isPlayerOne = isPlayerOne;
  this->gameLevel = 0;
  this->setSequences(sequence1, sequence2);
  this->levels = new Level0{isPlayerOne, sequence1, sequence2};
  this->canUp = false;
}

void Player::levelUp() {
  if (gameLevel == 4) {
    return;
  }

  gameLevel++;
  board.setLevel(gameLevel);
  if (gameLevel == 1) {
    delete levels;
    levels = new Level1{};
    levels->setSeed(seed);
  } else if (gameLevel == 2) {
    delete levels;
    levels = new Level2{};
    levels->setSeed(seed);
  } else if (gameLevel == 3) {
    delete levels;
    levels = new Level3{};
    levels->setSeed(seed);
  } else if (gameLevel == 4) {
    delete levels;
    levels = new Level4{};
    levels->setSeed(seed);
  }
}

void Player::levelDown() {
  if (gameLevel == 0) {
    return;
  }

  gameLevel--;
  board.setLevel(gameLevel);
  if (gameLevel == 0) {
    delete levels;
    levels = new Level0{isPlayerOne, sequence1, sequence2};
    levels->setSeed(seed);
  } else if (gameLevel == 1) {
    delete levels;
    levels = new Level1{};
    levels->setSeed(seed);
  } else if (gameLevel == 2) {
    delete levels;
    levels = new Level2{};
    levels->setSeed(seed);
  } else if (gameLevel == 3) {
    delete levels;
    levels = new Level3{};
    levels->setSeed(seed);
  }
}

void Player::norandom(string filename) { levels->norandom(filename); }

void Player::random() { levels->random(); }

int Player::dropBlock() {  // called from commander
  int linesCleared = 0;
  int pointsScored = board.dropBlock(linesCleared);
  score.addScore(pointsScored);

  return linesCleared;
}

Board &Player::getBoard() { return board; }

Score &Player::getScore() { return score; }

int Player::getLevel() { return gameLevel; }

void Player::setLevel(int newLevel) {
  gameLevel = newLevel;
  board.setLevel(gameLevel);
  if (gameLevel == 0) {
    delete levels;
    levels = new Level0{isPlayerOne, sequence1, sequence2};
  } else if (gameLevel == 1) {
    delete levels;
    levels = new Level1{};
    levels->setSeed(seed);
  } else if (gameLevel == 2) {
    delete levels;
    levels = new Level2{};
    levels->setSeed(seed);
  } else if (gameLevel == 3) {
    delete levels;
    levels = new Level3{};
    levels->setSeed(seed);
  }
}

void Player::setSequences(string newSequence1, string newSequence2) {
  sequence1 = newSequence1;
  sequence2 = newSequence2;
}

void Player::setSeed(int seedVal) { seed = seedVal; }

void Player::restartGame() {
  board.clearBoard();
  board.init();
  score.resetScore();

  delete levels;
  levels = new Level0{isPlayerOne, sequence1, sequence2};
}

Player::~Player() { delete levels; }

void Player::generateNewBlock() {
  Blocks *newBlock = levels->generateNewBlock();
  board.generateNewBlock(newBlock);
}

void Player::getBlockByType(char blockChar) {
  Blocks *newBlock = levels->createBlockByType(blockChar, gameLevel);
  board.changeBlock(newBlock);
}

void Player::setCanUp(bool canUp) { this->canUp = canUp; }

bool Player::getCanUp() { return this->canUp; }

void Player::setUpCount(int upCount) { this->upCount = upCount; }

int Player::getUpCount() { return this->upCount; }
