#ifndef OBLOCK_H
#define OBLOCK_H

#include "blocks.h"

class OBlock : public Blocks
{
    std::vector<std::vector<Cell *>> blockGrid;
    std::vector<Cell *> getPositionZero();
    std::vector<Cell *> getPositionOne();
    bool canValidMove(std::vector<Cell *>) const override;
    bool replaceCells(std::vector<Cell *>, std::string) override;

public:
    OBlock(int levelVal = 0);
    void init(Cell *, std::vector<std::vector<Cell *>>) override;
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
    ~OBlock() override;
};

#endif
