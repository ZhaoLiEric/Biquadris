#include "cell.h"

using namespace std;

Cell::Cell(const int x, const int y) : rowCord{x}, colCord{y}, letter{""}, livesCounter{-1} {}


int Cell::getCurrRow()
{
    return rowCord;
}

int Cell::getCurrCol()
{
    return colCord;
}

string Cell::getLetter()
{
    return letter;
}

void Cell::setLetter(const string &s)
{
    letter = s;
}

bool Cell::fullyFilled()
{
    if (letter == "")
    { 
        return false;
    }
    return true;
}

void Cell::copyData(Cell *other)
{
    livesCounter = other->livesCounter;
    letter = other->letter;
}

Cell::~Cell() {}
