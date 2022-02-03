#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "commander.h"
// Forward Declarations
class Player;
class DisplayObserver;
class GraphicsDisplay;

class Controller {
  bool isFirstPlayer;
  bool isGameOver;
  bool useGraphic; // choose use graphic display or not
  bool isKeyboard;
  Player *firstPlayer;
  Player *secondPlayer;
  DisplayObserver *textDisplay;
  GraphicsDisplay *graphicsDisplay;
  Commander commander;

  bool multipleSpecialActions;

  std::map<int, std::string> keyMap;

  void initGame();
  void printKeyboardInfo();

 public:
  // bool canUp;
  Player *getPlayingPlayer();
  Player *getNotPlayingPlayer();
  void startGame(int seed, std::string sequence1, std::string sequence2,
                 int startlevel);
  bool isGraphic;
  void updateDisplay();
  Controller(std::string, std::string, bool, bool);

  void restartGame(); // restart the game if needed
  void changePlayer();
  bool getIsGameOver();
  Player *getFirstPlayer();
  Player *getSecondPlayer();
  void useMultipleSpecialActionsOrNot();
  bool enableMultiSpecialAction();
  void setGraphic(bool isGraphic);
  bool getGraphic();
  // void setCanUp(bool);
  // bool getCanUp();
  ~Controller();
};

#endif
