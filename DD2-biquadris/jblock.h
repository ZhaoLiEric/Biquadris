#ifndef JBLOCK_H
#define JBLOCK_H

#include "blocks.h"

class JBlock : public Blocks
{
    std::vector<std::vector<Cell *>> blockGrid;
    std::vector<Cell *> getPositionZero();
    std::vector<Cell *> getPositionOne();
    std::vector<Cell *> getPositionTwo();
    std::vector<Cell *> getPositionThree();
    bool canValidMove(std::vector<Cell *>) const override;
    bool replaceCells(std::vector<Cell *>, std::string) override;

public:
    void init(Cell *, std::vector<std::vector<Cell *>>) override;
    JBlock(int levelVal = 0);
    Cell *getBottomLeftCell() const override;
    std::string getType() const override;

    std::vector<Cell *> getBlockCells() const override;
    void left(int dropAmount = 0) override;
    void right(int dropAmount = 0) override;
    bool down(int dropAmount = 1) override;
    bool up(int dropAmount = 1) override;
    void clockwise(int dropAmount = 0) override;
    void counterclockwise(int dropAmount = 0) override;

    void drop() override;
    bool isLostGame() override;
    ~JBlock() override;
};

#endif
