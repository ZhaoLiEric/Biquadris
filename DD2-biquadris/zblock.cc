#include "zblock.h"
#include "blocks.h"

using namespace std;

ZBlock::ZBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 3;
    this->levels = levelVal;
}

void ZBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    // create pointers to cells in the currBlock
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    Cell *zeroCell = blockGrid[3][1];
    zeroCell->setLetter("Z");
    Cell *firstCell = blockGrid[3][2];
    firstCell->setLetter("Z");
    Cell *secondCell = blockGrid[2][0];
    secondCell->setLetter("Z");
    Cell *thirdCell = blockGrid[2][1];
    thirdCell->setLetter("Z");
    blockCells.push_back(zeroCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool ZBlock::isLostGame()
{
    if (blockGrid[3][1]->fullyFilled() || blockGrid[3][2]->fullyFilled() || blockGrid[2][0]->fullyFilled() || blockGrid[2][1]->fullyFilled())
    {
        return true;
    }
    return false;
}

string ZBlock::getType() const
{
    return "Z";
}

Cell *ZBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> ZBlock::getBlockCells() const
{
    return blockCells;
}

bool ZBlock::canValidMove(vector<Cell *> newBlockCells) const
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
                blockCells[i]->setLetter("Z"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; 
}

bool ZBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        if (rotation == 0 || rotation == 2)
        {
            int rowOne = cells[0]->getCurrRow();
            int firstCol = cells[0]->getCurrCol();
            bottomLeftCell = blockGrid[rowOne][firstCol - 1];
        }
        else if (rotation == 1 || rotation == 3)
        {
            bottomLeftCell = cells[0];
        }
        blockCells.clear(); // remove all past cells from vector
        blockCells = cells; // reassign vector to new cells
        return true;
    }
    return false;
}

vector<Cell *> ZBlock::getPositionZero()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    return tempCells;
}

vector<Cell *> ZBlock::getPositionOne()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol + 1]);
    return tempCells;
}

void ZBlock::clockwise(int dropAmount)
{
    vector<Cell *> newRotation;
    if (rotation == 0 || rotation == 2)
    { 
        try
        {
            newRotation = getPositionOne();
        }
        catch (...)
        {
            return;
        }
        if (canValidMove(newRotation))
        {
            maxWidth = 2;
            rotation++;
        }
    }
    else if (rotation == 1 || rotation == 3)
    { 
        if (bottomLeftCell->getCurrCol() + 3 > 10)
        {
            return; 
        }
        try
        {
            newRotation = getPositionZero();
        }
        catch (...)
        {
            return;
        }
        if (canValidMove(newRotation))
        {
            maxWidth = 3;
            if (rotation == 1)
                rotation++;
            else
                rotation = 0;
        }
    }
    if (replaceCells(newRotation, "Z"))
        down(dropAmount);
}

void ZBlock::counterclockwise(int dropAmount)
{
    clockwise(dropAmount);
}

void ZBlock::left(int dropAmount)
{
    if (bottomLeftCell->getCurrCol() == 0)
    {
        return; 
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++)
    {
        curRow = blockCells[i]->getCurrRow();
        curCol = blockCells[i]->getCurrCol();
        newMovement.push_back(blockGrid[curRow][curCol - 1]);
    }
    if (replaceCells(newMovement, "Z"))
        down(dropAmount);
}

void ZBlock::right(int dropAmount)
{
    if (bottomLeftCell->getCurrCol() + maxWidth > 10)
    {
        return; 
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++)
    {
        curRow = blockCells[i]->getCurrRow();
        curCol = blockCells[i]->getCurrCol();
        newMovement.push_back(blockGrid[curRow][curCol + 1]);
    }
    if (replaceCells(newMovement, "Z"))
        down(dropAmount);
}

bool ZBlock::down(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 17)
        {
            return false; 
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int i = 0; i < blockCells.size(); i++)
        {
            curRow = blockCells[i]->getCurrRow();
            curCol = blockCells[i]->getCurrCol();
            newMovement.push_back(blockGrid[curRow + 1][curCol]);
        }
        if (replaceCells(newMovement, "Z"))
            continue;
        else
            return false;
    }
    return true;
}

bool ZBlock::up(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 3)
        {
            return false;
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int i = 0; i < blockCells.size(); i++)
        {
            curRow = blockCells[i]->getCurrRow();
            curCol = blockCells[i]->getCurrCol();
            newMovement.push_back(blockGrid[curRow - 1][curCol]);
        }
        if (replaceCells(newMovement, "Z"))
            continue;
        else
            return false;
    }
    return true;
}

void ZBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

ZBlock::~ZBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
