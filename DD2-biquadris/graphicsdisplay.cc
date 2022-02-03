#include "graphicsdisplay.h"

#include <string>

using namespace std;
bool gameIsOver = false;

const int cellLength = 772 / 26;

void GraphicsDisplay::titlePrinter() {
  string result = "BIQUADRIS";
  xw->drawString(11.5 * cellLength, 2 * cellLength, result);
}

void GraphicsDisplay::levelPrinter(int level1, int level2) {
  string result = "Levels:       ";
  string firstLevel = result + to_string(level1);
  string secondLevel = result + to_string(level2);
  xw->drawString(4 * cellLength, 4 * cellLength, firstLevel);
  xw->drawString(17 * cellLength, 4 * cellLength, secondLevel);
}

void GraphicsDisplay::scorePrinter(int score1, int score2) {
  string result = "Score: ";

  // board one
  string firstScore = to_string(score1);
  while (firstScore.length() < 7) {
    firstScore = " " + firstScore;
  }
  firstScore = result + firstScore;
  xw->drawString(4 * cellLength, 5 * cellLength, firstScore);

  // board two
  string secondScore = to_string(score2);
  while (secondScore.length() < 7) {
    secondScore = " " + secondScore;
  }
  secondScore = result + secondScore;
  xw->drawString(17 * cellLength, 5 * cellLength, secondScore);
}

void GraphicsDisplay::hiScorePrinter(int score1, int score2) {
  string result = "High: ";

  // board one
  string firstScore = to_string(score1);
  while (firstScore.length() < 8) {
    firstScore = " " + firstScore;
  }
  firstScore = result + firstScore;
  xw->drawString(4 * cellLength, 6 * cellLength, firstScore);

  // board two
  string secondScore = to_string(score2);
  while (secondScore.length() < 8) {
    secondScore = " " + secondScore;
  }
  secondScore = result + secondScore;
  xw->drawString(17 * cellLength, 6 * cellLength, secondScore);
}

int getCellColour(char blocks) {
  if (blocks == 'I') {
    return Xwindow::WebGray;
  } else if (blocks == 'J') {
    return Xwindow::DarkBlue;
  } else if (blocks == 'L') {
    return Xwindow::Coral;
  } else if (blocks == 'O') {
    return Xwindow::Goldenrod;
  } else if (blocks == 'S') {
    return Xwindow::Lime;
  } else if (blocks == 'T') {
    return Xwindow::Indigo;
  } else if (blocks == 'Z') {
    return Xwindow::Crimson;
  } else if (blocks == '?') {
    return Xwindow::DeepPink;
  } else {  // if (blocks == '*') {
    return Xwindow::Sienna;
  }
}

void GraphicsDisplay::boardPrinter() {
  // board one
  xw->fillRectangle(1 * cellLength, 7 * cellLength, 11 * cellLength + 2,
                    18 * cellLength + 2, Xwindow::Black);
  // board two
  xw->fillRectangle(14 * cellLength, 7 * cellLength, 11 * cellLength + 2,
                    18 * cellLength + 2, Xwindow::Black);
  // scores
  xw->fillRectangle(2 * cellLength, 3 * cellLength, 24 * cellLength,
                    3 * cellLength, Xwindow::White);
  // next blocks areas
  xw->fillRectangle(2 * cellLength, 27 * cellLength, 11 * cellLength + 2,
                    18 * cellLength + 2, Xwindow::White);
  xw->fillRectangle(15 * cellLength, 27 * cellLength, 11 * cellLength + 2,
                    18 * cellLength + 2, Xwindow::White);
}

void GraphicsDisplay::boardBlocksPrinter(Board &firstPlayerBoard,
                                         Board &secondPlayerBoard) {
  string firstBoardLine, secondBoardLine;
  for (int i = 0; i < 18; ++i) {
    firstBoardLine = firstPlayerBoard.getLine(i);
    secondBoardLine = secondPlayerBoard.getLine(i);
    for (int j = 0; j < firstBoardLine.length(); ++j) {
      if (firstBoardLine[j] != '.') {
        xw->fillRectangle((j + 1) * cellLength + 2, (i + 7) * cellLength + 2,
                          cellLength - 2, cellLength - 2,
                          getCellColour(firstBoardLine[j]));
      }
    }
    for (int j = 0; j < secondBoardLine.length(); ++j) {
      if (secondBoardLine[j] != '.') {
        xw->fillRectangle((j + 14) * cellLength + 2, (i + 7) * cellLength + 2,
                          cellLength - 2, cellLength - 2,
                          getCellColour(secondBoardLine[j]));
      }
    }
  }
}

void GraphicsDisplay::nextBlockPrinter(int x, int y, char blocks) {
  if (blocks == 'I') {
    xw->fillRectangle(x * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 3) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  } else if (blocks == 'J') {
    xw->fillRectangle(x * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle(x * cellLength + 2, y * cellLength + 2, cellLength - 2,
                      cellLength - 2, getCellColour(blocks));
  } else if (blocks == 'L') {
    xw->fillRectangle(x * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  } else if (blocks == 'O') {
    xw->fillRectangle(x * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle(x * cellLength + 2, y * cellLength + 2, cellLength - 2,
                      cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  } else if (blocks == 'S') {
    xw->fillRectangle(x * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  } else if (blocks == 'T') {
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle(x * cellLength + 2, y * cellLength + 2, cellLength - 2,
                      cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  } else {  // if (blocks == 'Z') {
    xw->fillRectangle((x + 1) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 2) * cellLength + 2, (y + 1) * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
    xw->fillRectangle(x * cellLength + 2, y * cellLength + 2, cellLength - 2,
                      cellLength - 2, getCellColour(blocks));
    xw->fillRectangle((x + 1) * cellLength + 2, y * cellLength + 2,
                      cellLength - 2, cellLength - 2, getCellColour(blocks));
  }
}

void GraphicsDisplay::nextPrinter(char firstPlayerBlock,
                                  char secondPlayerBlock) {
  string next = "Next: ";
  // board one
  xw->drawString(2 * cellLength, 26 * cellLength - 10, next);
  nextBlockPrinter(2, 27, firstPlayerBlock);
  // board two
  xw->drawString(15 * cellLength, 26 * cellLength - 10, next);
  nextBlockPrinter(15, 27, secondPlayerBlock);
}

void GraphicsDisplay::undraw() {
  if (gameIsOver) {
    xw->fillRectangle(1 * cellLength, 7 * cellLength, 24 * cellLength + 2,
                      18 * cellLength + 2, Xwindow::White);
  }
  xw->fillRectangle(1 * cellLength, 30 * cellLength, 40 * cellLength,
                    12 * cellLength, Xwindow::White);
}

void GraphicsDisplay::resultPrinter(
    int score1,
    int score2) {  
  string gameOver = "GAME OVER";
  string winMessage;
  if (score1 == score2) {
    winMessage = "Same score. Tie!!!";
  } else if (score1 > score2) {
    winMessage = "Player 1 wins!!!\n";
  } else {
    winMessage = "Player 2 wins!!!\n";
  }
  string restartMessage = "Press [R] to restart the game.";
  xw->fillRectangle(1 * cellLength, 7 * cellLength, 24 * cellLength + 2,
                    18 * cellLength + 2, Xwindow::Crimson);
  xw->drawString(12 * cellLength, 15 * cellLength, gameOver);
  xw->drawString(11 * cellLength, 16 * cellLength, winMessage);
  xw->drawString(9 * cellLength, 18 * cellLength, restartMessage);
  gameIsOver = true;
}

GraphicsDisplay::GraphicsDisplay(Controller *controller) {
  this->controller = controller;
  xw = new Xwindow;
}

GraphicsDisplay::~GraphicsDisplay() { delete xw; }

void GraphicsDisplay::displayBoard() {
  undraw();
  titlePrinter();
  boardPrinter();
  levelPrinter(controller->getFirstPlayer()->getLevel(),
               controller->getSecondPlayer()->getLevel());
  scorePrinter(controller->getFirstPlayer()->getScore().getCurrentScore(),
               controller->getSecondPlayer()->getScore().getCurrentScore());
  hiScorePrinter(controller->getFirstPlayer()->getScore().getHighScore(),
                 controller->getSecondPlayer()->getScore().getHighScore());
  if (controller->getIsGameOver()) {
    resultPrinter(controller->getFirstPlayer()->getScore().getCurrentScore(),
                  controller->getSecondPlayer()->getScore().getCurrentScore());
  } else {
    boardBlocksPrinter(controller->getFirstPlayer()->getBoard(),
                       controller->getSecondPlayer()->getBoard());
    nextPrinter(
        controller->getFirstPlayer()->getBoard().getNextBlock()->getType()[0],
        controller->getSecondPlayer()->getBoard().getNextBlock()->getType()[0]);
  }
}

int GraphicsDisplay::getPressedKey() { return xw->getEvent(); }
