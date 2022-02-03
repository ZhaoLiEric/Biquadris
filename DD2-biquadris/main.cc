#include <iostream>
#include <string>

#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
  bool useGraphic = true;
  bool isKeyboard = false;
  int seed = 1;
  string sequence1 = "sequence1.txt";
  string sequence2 = "sequence2.txt";
  int startLevel = 0;
  for (int i = 0; i < argc; ++i)
  {
    string input = argv[i];
    if (input == "-text")
    {
      useGraphic = false;
    }
    else if (input == "-keyboard")
    {
      isKeyboard = true;
    }
    else if (input == "-seed")
    {
      seed = stoi(argv[i + 1]);
    }
    else if (input == "-scriptfile1")
    {
      sequence1 = argv[i + 1];
    }
    else if (input == "-scriptfile2")
    {
      sequence2 = argv[i + 1];
    }
    else if (input == "-startlevel")
    {
      startLevel = stoi(argv[i + 1]);
    }
  }
  //Initialize the game
  Controller bq(sequence1, sequence2, useGraphic, isKeyboard);
  bq.startGame(seed, sequence1, sequence2, startLevel);
}
