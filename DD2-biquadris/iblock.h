#ifndef IBLOCK_H
#define IBLOCK_H

#include "blocks.h"

class IBlock : public Blocks
{
    std::vector<std::vector<Cell *>> blockGrid;
    bool canValidMove(std::vector<Cell *>) const override;
    bool replaceCells(std::vector<Cell *>, std::string) override;
    std::vector<Cell *> getPositionZero();
    std::vector<Cell *> getPositionOne();


public:
    Cell *getBottomLeftCell() const override;
    void init(Cell *, std::vector<std::vector<Cell *>>) override;
    IBlock(int levelVal = 0);
    std::string getType() const override;
    
    std::vector<Cell *> getBlockCells() const override;
    void clockwise(int dropAmount = 0) override;
    void counterclockwise(int dropAmount = 0) override;
    void left(int dropAmount = 0) override;
    void right(int dropAmount = 0) override;
    bool down(int dropAmount = 1) override;
    bool up(int dropAmount = 1) override;
    void drop() override;
    bool isLostGame() override;
    ~IBlock() override;
};

#endif
