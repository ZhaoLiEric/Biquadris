#include "textdisplay.h"

#include <string>

#include "controller.h"
#include "player.h"
using namespace std;

void levelPrinter(int firstPlayerLevel, int secondPlayerLevel) {
  string res = "Levels:    ";
  cout << res << firstPlayerLevel;
  cout << "       ";
  cout << res << secondPlayerLevel;
  cout << endl;
}

void scorePrinter(int firstPlayerScore, int secondPlayerScore) {
  string res = "Score: ";

  string firstScore = to_string(firstPlayerScore);
  while (firstScore.length() < 4) {
    firstScore = " " + firstScore;
  }
  cout << res << firstScore;

  cout << "       ";

  string secondScore = to_string(secondPlayerScore);
  while (secondScore.length() < 4) {
    secondScore = " " + secondScore;
  }
  cout << res << secondScore;

  cout << endl;
}

void hiScorePrinter(int firstPlayerHighScore, int secondPlayerHighScore) {
  string res = "High: ";

  string firstScore = to_string(firstPlayerHighScore);
  while (firstScore.length() < 5) {
    firstScore = " " + firstScore;
  }
  cout << res << firstScore;

  cout << "       ";

  string secondScore = to_string(secondPlayerHighScore);
  while (secondScore.length() < 5) {
    secondScore = " " + secondScore;
  }
  cout << res << secondScore;

  cout << endl;
}

void boardPrinter(Board &firstPlayerBoard, Board &secondPlayerBoard) {
  for (int i = 0; i < 18; ++i) {
    cout << firstPlayerBoard.getLine(i);
    cout << "       ";
    cout << secondPlayerBoard.getLine(i);
    cout << endl;
  }
}

void dashPrinter() {
  cout << "-----------";
  cout << "       ";
  cout << "-----------";
  cout << endl;
}

void nextPrinter() {
  cout << "Next:      ";
  cout << "       ";
  cout << "Next:      ";
  cout << endl;
}

void blockTopPrinter(char blocks) {
  if (blocks == 'I') {
    cout << "           ";
  } else if (blocks == 'J') {
    cout << "J          ";
  } else if (blocks == 'L') {
    cout << "  L        ";
  } else if (blocks == 'O') {
    cout << "OO         ";
  } else if (blocks == 'S') {
    cout << " SS        ";
  } else if (blocks == 'T') {
    cout << "TTT        ";
  } else {  // if (currBlock == 'Z') {
    cout << "ZZ        ";
  }
}

void blockBottomPrinter(char blocks) {
  if (blocks == 'I') {
    cout << "IIII       ";
  } else if (blocks == 'J') {
    cout << "JJJ        ";
  } else if (blocks == 'L') {
    cout << "LLL        ";
  } else if (blocks == 'O') {
    cout << "OO         ";
  } else if (blocks == 'S') {
    cout << "SS         ";
  } else if (blocks == 'T') {
    cout << " T         ";
  } else {  // if (currBlock == 'Z') {
    cout << " ZZ        ";
  }
};

void printBlocks(char firstPlayerBlock, char secondPlayerBlock) {
  blockTopPrinter(firstPlayerBlock);
  cout << "       ";
  blockTopPrinter(secondPlayerBlock);
  cout << endl;
  blockBottomPrinter(firstPlayerBlock);
  cout << "       ";
  blockBottomPrinter(secondPlayerBlock);
  cout << endl;
}

TextDisplay::TextDisplay(Controller *controller) {
  this->controller = controller;
}

TextDisplay::~TextDisplay() = default;

void TextDisplay::displayBoard() {
  levelPrinter(controller->getFirstPlayer()->getLevel(),
               controller->getSecondPlayer()->getLevel());
  scorePrinter(controller->getFirstPlayer()->getScore().getCurrentScore(),
               controller->getSecondPlayer()->getScore().getCurrentScore());
  hiScorePrinter(controller->getFirstPlayer()->getScore().getHighScore(),
                 controller->getSecondPlayer()->getScore().getHighScore());
  dashPrinter();
  boardPrinter(controller->getFirstPlayer()->getBoard(),
               controller->getSecondPlayer()->getBoard());
  dashPrinter();
  nextPrinter();
  printBlocks(controller->getFirstPlayer()
                  ->getBoard()
                  .getNextBlock()
                  ->getType()[0],  // get blocks type
              controller->getSecondPlayer()
                  ->getBoard()
                  .getNextBlock()
                  ->getType()[0]);  // string to char
}
