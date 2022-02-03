#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "blocks.h"
#include "cell.h"
#include <string>

class Board
{
    Blocks *currBlock;
    Blocks *nextBlock;
    std::vector<std::vector<Cell *>> theGrid;
    std::vector<Blocks *> blockList;
    int levels;
    int lastClear;
    bool blind;
    bool heavy;

public:
    Board();
    Blocks *getCurrentBlock();
    Blocks *getNextBlock();
    int updateBlockList(); 
    void clearBoard(); // clear the whole board
    bool isRowFull(int);
    void entireRowClear(int); // clear the entire row
    int dropBlock(int &); // return score if any rows cleared
    std::string getLine(int);
    void EntireRowCopy(int rowOne, int rowTwo); //Copy the contents of one row to the next row
    void init(); // init the board
    void setLevel(int); 
    void generateNewBlock(Blocks *);
    void changeBlock(Blocks *);
    void setBlind();
    void setHeavy();
    int isHeavy();
    bool shouldDropStar();
    ~Board();
};

#endif 
