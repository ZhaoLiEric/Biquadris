#include "starblock.h"

using namespace std;

StarBlock::StarBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 4;
    this->levels = levelVal;
}

void StarBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    // create pointers to cells in the currBlock
    bottomLeftCell->setLetter("*");
    blockCells.push_back(bottomLeftCell);
}

bool StarBlock::isLostGame()
{
    return bottomLeftCell->fullyFilled();
}

string StarBlock::getType() const
{
    return "*";
}

Cell *StarBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> StarBlock::getBlockCells() const
{
    return blockCells;
}

bool StarBlock::canValidMove(vector<Cell *> newBlockCells) const
{
    for (int i = 0; i < blockCells.size(); i++)
    {
        blockCells[i]->setLetter(""); // set old currBlock cells to empty letter
    }
    for (int i = 0; i < newBlockCells.size(); i++)
    {
        if (newBlockCells[i]->fullyFilled())
        { 
            for (int i = 0; i < blockCells.size(); i++)
            {
                blockCells[i]->setLetter("*"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; 
}

bool StarBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        bottomLeftCell = cells[0]; // set bottomLeftCell
        blockCells.clear();        // remove all past cells from vector
        blockCells = cells;        // reassign vector to new cells
        return true;
    }
    return false;
}

void StarBlock::clockwise(int)
{
    // Do nothing
}

void StarBlock::counterclockwise(int)
{
    // Do nothing
}

void StarBlock::left(int)
{
    // Do nothing
}

void StarBlock::right(int)
{
    // Do nothing
}

bool StarBlock::down(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 17)
        {
            return false; // can't move down, at bottom row
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int j = 0; j < blockCells.size(); j++)
        {
            curRow = blockCells[j]->getCurrRow();
            curCol = blockCells[j]->getCurrCol();
            newMovement.push_back(blockGrid[curRow + 1][curCol]);
        }
        if (replaceCells(newMovement, "*"))
            continue;
        else
            return false;
    }
    return true;
}

bool StarBlock::up(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 3)
        {
            return false; 
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int j = 0; j < blockCells.size(); j++)
        {
            curRow = blockCells[j]->getCurrRow();
            curCol = blockCells[j]->getCurrCol();
            newMovement.push_back(blockGrid[curRow - 1][curCol]);
        }
        if (replaceCells(newMovement, "*"))
            continue;
        else
            return false;
    }
    return true;
}

void StarBlock::drop()
{
    while (down())
        ;
}

StarBlock::~StarBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
