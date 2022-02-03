#include "controller.h"

#include "graphicsdisplay.h"
#include "player.h"
#include "textdisplay.h"

using namespace std;

Controller::Controller(string sequence1, string sequence2, bool useGraphic,
                       bool isKeyboard)
    : isFirstPlayer{true},
      isGameOver{false},
      useGraphic{useGraphic},
      isKeyboard{isKeyboard},
      firstPlayer{new Player{true, sequence1, sequence2}},
      secondPlayer{new Player{false, sequence1, sequence2}},
      textDisplay{new TextDisplay{this}},
      graphicsDisplay{new GraphicsDisplay{this}},
      commander{Commander{this}},
      multipleSpecialActions{false},
      keyMap{{0x71, "left"},
             {0x72, "right"},
             {0x74, "down"},
             {0x6F, "clockwise"},
             {0x36, "counterclockwise"},
             {0x41, "drop"},
             {0x15, "levelup"},
             {0x14, "leveldown"},
             {0x1E, "up"},
             //  {0x0B, "norandom"},
             //  {0x0A, "random"},
             //  {0x0E, "sequence"},
             {0x1F, "I"},
             {0x2C, "J"},
             {0x2E, "L"},
             {0x20, "O"},
             {0x27, "S"},
             {0x1C, "T"},
             {0x34, "Z"},
             {0x1B, "restart"},
             //  {0x44, "rename"},
             {0x13, "togglemultiplespecialactions"}} {}

void Controller::printKeyboardInfo() {
  cout << "Keyboard instructions: " << endl;
  cout << "<: move left" << endl;
  cout << ">: move right" << endl;
  cout << "v: move down" << endl;
  cout << "^: rotate clockwise" << endl;
  cout << "c: rotate counterclockwise" << endl;
  cout << "space: drop" << endl;
  cout << "=: levelup" << endl;
  cout << "-: leveldown" << endl;
  cout << "I: mutate to I blocks" << endl;
  cout << "J: mutate to J blocks" << endl;
  cout << "L: mutate to L blocks" << endl;
  cout << "O: mutate to O blocks" << endl;
  cout << "S: mutate to S blocks" << endl;
  cout << "T: mutate to T blocks" << endl;
  cout << "Z: mutate to Z blocks" << endl;
  cout << "R: restart the game" << endl;
  cout << "0: enable/disable multiple special actions" << endl;
}

void Controller::updateDisplay() {
  textDisplay->displayBoard();
  if (useGraphic) {
    graphicsDisplay->displayBoard();
  }
}

void Controller::initGame() {
  firstPlayer->generateNewBlock();
  firstPlayer->generateNewBlock();
  secondPlayer->generateNewBlock();
  secondPlayer->generateNewBlock();
}

void Controller::startGame(int seed, string sequence1, string sequence2,
                           int startlevel) {
  // Set start levels
  firstPlayer->setLevel(startlevel);
  secondPlayer->setLevel(startlevel);

  // Set seed
  firstPlayer->setSeed(seed);
  secondPlayer->setSeed(seed);

  initGame();
  updateDisplay();

  string command;
  int keycode;
  if (isKeyboard) {
    printKeyboardInfo();
    while (true) {
      keycode = graphicsDisplay->getPressedKey();
      if (keycode == 0x09) break;
      command = keyMap[keycode];
      commander.parseCommand(command);
      updateDisplay();
    }
  } else {
    while (cin >> command) {
      commander.parseCommand(command);
      updateDisplay();
    }
  }
}

void Controller::changePlayer() {
  try {
    getPlayingPlayer()->generateNewBlock();
    isFirstPlayer = !isFirstPlayer;
  } catch (runtime_error &err) {
    cerr << err.what() << endl;
    isGameOver = true;
  }
}

bool Controller::getIsGameOver() { return isGameOver; }

Player *Controller::getPlayingPlayer() {
  if (isFirstPlayer) {
    return firstPlayer;
  } else {
    return secondPlayer;
  }
}

Player *Controller::getNotPlayingPlayer() {
  if (isFirstPlayer) {
    return secondPlayer;
  } else {
    return firstPlayer;
  }
}

Player *Controller::getFirstPlayer() { return firstPlayer; }

Player *Controller::getSecondPlayer() { return secondPlayer; }

Controller::~Controller() {
  delete firstPlayer;
  delete secondPlayer;
  delete textDisplay;
  delete graphicsDisplay;
}

void Controller::useMultipleSpecialActionsOrNot() {
  multipleSpecialActions = !multipleSpecialActions;
}
bool Controller::enableMultiSpecialAction() { return multipleSpecialActions; }

void Controller::setGraphic(bool isGraphic) { this->isGraphic = isGraphic; }
bool Controller::getGraphic() { return this->isGraphic; }

/*
void Controller::setCanUp(bool canUp){
    this->canUp = canUp;
}

bool Controller::getCanUp(){
    return this->canUp;
}*/

void Controller::restartGame() {
  firstPlayer->restartGame();  // reset the board
  secondPlayer->restartGame();
  isFirstPlayer = true;  // player one begins

  initGame();  // create starting blocks

  isGameOver = false;  // allow play again
}
