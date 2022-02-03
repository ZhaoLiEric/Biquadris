#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "controller.h"
#include "displayobserver.h"
#include "player.h"
#include "window.h"
class GraphicsDisplay : public DisplayObserver {
  Xwindow *xw;
  void titlePrinter(); //print title
  void levelPrinter(int, int);//print level
  void scorePrinter(int, int);//print the score
  void hiScorePrinter(int, int);//print the highest score
  void boardPrinter();
  void undraw();//undraw the graph
  void boardBlocksPrinter(Board &, Board &);
  void nextBlockPrinter(int, int, char);
  void nextPrinter(char, char);
  void resultPrinter(int, int);

 public:
  GraphicsDisplay(Controller *);
  void displayBoard() override;
  int getPressedKey();
  ~GraphicsDisplay() override;
};

#endif
