#ifndef BLOCKS_H
#define BLOCKS_H

#include <iostream>
#include <vector>
#include "cell.h"

class Blocks
{
protected:
    Cell *bottomLeftCell;           // pointer point to the bottom left cell
    std::vector<Cell *> blockCells; // contain all cells of currBlock
    int levels;                      // current Blocks levels
    virtual bool canValidMove(std::vector<Cell *>) const = 0;
    virtual bool replaceCells(std::vector<Cell *>, std::string) = 0;
    int rotation; // time that can rotate
    int maxWidth; 

public:
    int updateBlock();
    void setLevel(int);
    virtual void init(Cell *, std::vector<std::vector<Cell *>>) = 0;
    virtual std::string getType() const = 0;
    virtual Cell *getBottomLeftCell() const = 0; // get the cell at bottom left to operate
    virtual std::vector<Cell *> getBlockCells() const = 0;
    virtual void clockwise(int dropAmount = 0) = 0;
    virtual void counterclockwise(int dropAmount = 0) = 0;
    virtual bool up(int dropAmount = 1) = 0;
    virtual bool down(int dropAmount = 1) = 0;
    virtual void left(int dropAmount = 0) = 0;
    virtual void right(int dropAmount = 0) = 0;

    virtual void drop() = 0;
    virtual bool isLostGame() = 0;

    virtual ~Blocks();
};

#endif 
