#ifndef LBLOCK_H
#define LBLOCK_H

#include "blocks.h"

class LBlock : public Blocks
{
    std::vector<std::vector<Cell *>> blockGrid;
    std::vector<Cell *> getPositionZero();
    std::vector<Cell *> getPositionOne();
    std::vector<Cell *> getPositionTwo();
    std::vector<Cell *> getPositionThree();
    bool canValidMove(std::vector<Cell *>) const override;// check if block can valid move
    bool replaceCells(std::vector<Cell *>, std::string) override;

public:
    void init(Cell *, std::vector<std::vector<Cell *>>) override;
    LBlock(int levelVal = 0);

    std::string getType() const override;
    Cell *getBottomLeftCell() const override;
    std::vector<Cell *> getBlockCells() const override;
    void clockwise(int dropAmount = 0) override;
    void counterclockwise(int dropAmount = 0) override;
    void left(int dropAmount = 0) override;
    void right(int dropAmount = 0) override;
    bool down(int dropAmount = 1) override;
    bool up(int dropAmount = 1) override;
    void drop() override;
    bool isLostGame() override;
    ~LBlock() override;
};

#endif
