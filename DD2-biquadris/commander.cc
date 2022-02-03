#include "commander.h"

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

#include "controller.h"
#include "player.h"

using namespace std;

Commander::Commander(Controller *controller)
    : controller{controller},
      commandMap{{"left", Commander::left},
                 {"right", Commander::right},
                 {"down", Commander::down},
                 {"clockwise", Commander::clockwise},
                 {"counterclockwise", Commander::counterclockwise},
                 {"drop", Commander::drop},
                 {"levelup", Commander::levelup},
                 {"leveldown", Commander::leveldown},
                 {"norandom", Commander::norandom},
                 {"random", Commander::random},
                 {"sequence", Commander::sequence},
                 {"I", Commander::I},
                 {"J", Commander::J},
                 {"L", Commander::L},
                 {"O", Commander::O},
                 {"S", Commander::S},
                 {"T", Commander::T},
                 {"Z", Commander::Z},
                 {"up", Commander::up},
                 {"restart", Commander::restart},
                 {"rename", Commander::rename},
                 {"togglemultiplespecialactions",
                  Commander::useMultipleSpecialActions}} {}

int getMultiplier(string &command) {
  string multiplierString;
  for (int i = 0; i < command.length();
       i++) {  // remove multiplier number from command
    char currChar = command[i];
    if (currChar >= '0' && currChar <= '9') {
      multiplierString += currChar;
    } else {
      command = command.substr(i, command.length() - i);
      break;
    }
  }
  // Multiplier is taken from input if numbers were inputted and 0 otherwise
  if (multiplierString.length() > 0) {
    return stoi(multiplierString);
  } else {
    return 1;
  }
}

int linesToDrop(int gameLevel) {
  if (gameLevel == 3 || gameLevel == 4) {
    return 1;
  } else {
    return 0;
  }
}

void Commander::runLeft(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  int down = linesToDrop(controller->getPlayingPlayer()->getLevel()) +
             controller->getPlayingPlayer()->getBoard().isHeavy();
  for (int i = 0; i < multiplier; i++) {
    currentBlock->left(down);
  }
}

void Commander::runRight(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  int down = linesToDrop(controller->getPlayingPlayer()->getLevel()) +
             controller->getPlayingPlayer()->getBoard().isHeavy();
  for (int i = 0; i < multiplier; i++) {
    currentBlock->right(down);
  }
}

void Commander::runDown(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  int down = linesToDrop(controller->getPlayingPlayer()->getLevel());
  for (int i = 0; i < multiplier; i++) {
    currentBlock->down(down + 1);  // down naturally should fall by 1
  }
}

void Commander::runUp(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  currentBlock->up(1);
}

void Commander::runClockwise(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  int drop = linesToDrop(controller->getPlayingPlayer()->getLevel());
  for (int i = 0; i < multiplier; i++) {
    currentBlock->clockwise(drop);
  }
}

void Commander::runCounterclockwise(int multiplier) {
  Blocks *currentBlock =
      controller->getPlayingPlayer()->getBoard().getCurrentBlock();
  int down = linesToDrop(controller->getPlayingPlayer()->getLevel());
  for (int i = 0; i < multiplier; i++) {
    currentBlock->counterclockwise(down);
  }
}

void Commander::promptSpecialAction() {
  cout << "Enter a special action" << endl;
  string specialAction;
  while (cin >> specialAction) {
    if (specialAction == "blind") {
      controller->getNotPlayingPlayer()->getBoard().setBlind();
      break;
    } else if (specialAction == "heavy") {
      controller->getNotPlayingPlayer()->getBoard().setHeavy();
      break;
    } else if (specialAction == "force") {
      char blockChar;
      if (cin >> blockChar &&
          (blockChar == 'I' || blockChar == 'J' || blockChar == 'L' ||
           blockChar == 'O' || blockChar == 'S' || blockChar == 'T' ||
           blockChar == 'Z')) {
        controller->getNotPlayingPlayer()->getBlockByType(blockChar);
        break;
      }
      cout << "bad letter" << endl;
    } else if (specialAction == "moveUp") {
      auto currentPlayer = controller->getPlayingPlayer();
      currentPlayer->setCanUp(true);
      // controller->setCanUp(true);
      // that player have 5 chances to up it's blocks
      currentPlayer->setUpCount(5);
      break;
    } else {
      cout << "bad special action" << endl;
    }
  }
}

void Commander::runDrop(int multiplier) {
  for (int i = 0; i < multiplier; i++) {
    if (controller->getIsGameOver()) {  // Check game over every iteration
      return;
    }
    int linesCleared =
        controller->getPlayingPlayer()
            ->dropBlock();  // multiple lines, prompt special action
    // make the graphic display available
    controller->updateDisplay();
    while (linesCleared > 1) {
      promptSpecialAction();
      --linesCleared;
      if (!controller->enableMultiSpecialAction()) {
        break;  // if multiple not toggled, break after one
      }
    }

    if (controller->getPlayingPlayer()
            ->getBoard()
            .shouldDropStar()) {  // level4 extra blocks
      controller->getPlayingPlayer()->getBlockByType('*');
      controller->getPlayingPlayer()->dropBlock();
    }

    controller->changePlayer();
  }
}

void Commander::operateLevelUp(int multiplier) {
  for (int i = 0; i < multiplier; i++) {
    controller->getPlayingPlayer()->levelUp();
  }
}

void Commander::operateLevelDown(int multiplier) {
  for (int i = 0; i < multiplier; i++) {
    controller->getPlayingPlayer()->levelDown();
  }
}

void Commander::parseCommand(string command) {
  // getMultiplier returns the multiplier and modifies command to remove the
  // numbers
  int multiplier = getMultiplier(command);

  Commander::Command chosenCommand =
      noCommand;  // Set default command if no command matches

  bool commandFound = false;    // Keep track of command matches and cancel
                                // command if there is ambiguity
  for (auto &x : commandMap) {  // look for command in the commandMap
    if (command == x.first.substr(0, command.length())) {
      chosenCommand = x.second;
      if (commandFound) {
        cerr << "ambiguous input, please try again" << endl;
        return;
      }
      commandFound = true;
    }
  }

  if (controller->getIsGameOver()) {  // If in game over state, the only allowed
    // action is restart
    if (chosenCommand == restart) {
      controller->restartGame();
    } else {
      cout << "invalid command, game over" << endl;
      return;
    }
  }

  if (chosenCommand == Commander::left) {
    runLeft(multiplier);
  } else if (chosenCommand == Commander::up) {
    if (controller->getPlayingPlayer()->getCanUp() &&
        controller->getPlayingPlayer()->getUpCount() > 0) {
      runUp(multiplier);
      int upCount = controller->getPlayingPlayer()->getUpCount();
      upCount--;
      controller->getPlayingPlayer()->setUpCount(upCount);
    }
  } else if (chosenCommand == Commander::right) {
    runRight(multiplier);
  } else if (chosenCommand == Commander::down) {
    runDown(multiplier);
  } else if (chosenCommand == Commander::clockwise) {
    runClockwise(multiplier);
  } else if (chosenCommand == Commander::counterclockwise) {
    runCounterclockwise(multiplier);
  } else if (chosenCommand == Commander::drop) {
    runDrop(multiplier);
  } else if (chosenCommand == Commander::levelup) {
    operateLevelUp(multiplier);
  } else if (chosenCommand == Commander::leveldown) {
    operateLevelDown(multiplier);
  } else if (chosenCommand == Commander::norandom) {
    string filename;
    if (cin >> filename) {
      controller->getPlayingPlayer()->norandom(filename);
    }
  } else if (chosenCommand == Commander::random) {
    controller->getPlayingPlayer()->random();
  } else if (chosenCommand == Commander::sequence) {
    string filename;
    if (cin >> filename) {
      ifstream file{filename};

      string fileCommand;
      while (file >> fileCommand) {
        parseCommand(fileCommand);
      }
    }
  } else if (chosenCommand == Commander::I) {
    controller->getPlayingPlayer()->getBlockByType('I');
  } else if (chosenCommand == Commander::J) {
    controller->getPlayingPlayer()->getBlockByType('J');
  } else if (chosenCommand == Commander::L) {
    controller->getPlayingPlayer()->getBlockByType('L');
  } else if (chosenCommand == Commander::O) {
    controller->getPlayingPlayer()->getBlockByType('O');
  } else if (chosenCommand == Commander::S) {
    controller->getPlayingPlayer()->getBlockByType('S');
  } else if (chosenCommand == Commander::T) {
    controller->getPlayingPlayer()->getBlockByType('T');
  } else if (chosenCommand == Commander::Z) {
    controller->getPlayingPlayer()->getBlockByType('Z');
  } else if (chosenCommand == Commander::restart) {
    controller->restartGame();
  } else if (chosenCommand == Commander::rename) {
    string oldName;
    string newName;
    if (cin >> oldName >> newName) {
      if (commandMap.count(oldName) == 1) {
        Commander::Command iCommand = commandMap[oldName];
        commandMap.insert(pair<string, Commander::Command>(newName, iCommand));
        commandMap.erase(oldName);
      }
    }
  } else if (chosenCommand == Commander::useMultipleSpecialActions) {
    controller->useMultipleSpecialActionsOrNot();
    if (controller->enableMultiSpecialAction()) {
      cout << "Enable Multiple Special Actions" << endl;
    } else {
      cout << "Disable Multiple Special Actions" << endl;
    }
  } else {
    cerr << "bad command" << endl;
  }
}
