#ifndef CELL_H
#define CELL_H

#include <string>

class Cell
{
    int livesCounter;
    const int rowCord;
    const int colCord;
    std::string letter;

public:
    Cell(int x, int y);
    bool fullyFilled();
    void setLetter(const std::string &);
    void copyData(Cell *other);
    int getCurrRow();
    int getCurrCol();
    std::string getLetter();
    ~Cell();
};

#endif
