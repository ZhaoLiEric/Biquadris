#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "board.h"
#include "score.h"

// Forward Declaration
class Levels;
class Player {
 protected:
  bool isPlayerOne;
  int gameLevel;
  int seed;
  std::string sequence1;
  std::string sequence2;
  Levels *levels;
  Board board;
  Score score;
  bool canUp;
  int upCount;

 public:
  Board &getBoard();
  Score &getScore();
  int dropBlock();
  int getLevel();
  void setLevel(int);
  void setSequences(std::string, std::string);
  void setSeed(int);
  void levelUp();
  void levelDown();
  void norandom(std::string);
  void random();
  void restartGame();
  void generateNewBlock();
  void getBlockByType(char);
  void setCanUp(bool);
  bool getCanUp();

  Player(bool, std::string, std::string);
  ~Player();
  void setUpCount(int);
  int getUpCount();
};

#endif
