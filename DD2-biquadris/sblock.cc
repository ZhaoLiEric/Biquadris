#include "sblock.h"

using namespace std;

SBlock::SBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 3;
    this->levels = levelVal;
}

void SBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    bottomLeftCell->setLetter("S");
    Cell *firstCell = blockGrid[3][1];
    firstCell->setLetter("S");
    Cell *secondCell = blockGrid[2][1];
    secondCell->setLetter("S");
    Cell *thirdCell = blockGrid[2][2];
    thirdCell->setLetter("S");
    // add to vector
    blockCells.push_back(bottomLeftCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool SBlock::isLostGame()
{
    if (bottomLeftCell->fullyFilled() || blockGrid[3][1]->fullyFilled() || blockGrid[2][1]->fullyFilled() || blockGrid[2][2]->fullyFilled())
    {
        return true;
    }
    return false;
}

string SBlock::getType() const
{
    return "S";
}

Cell *SBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> SBlock::getBlockCells() const
{
    return blockCells;
}

bool SBlock::canValidMove(vector<Cell *> newBlockCells) const
{
    for (int i = 0; i < blockCells.size(); i++)
    {
        blockCells[i]->setLetter(""); // set old currBlock cells to empty letter
    }
    for (int i = 0; i < newBlockCells.size(); i++)
    {
        if (newBlockCells[i]->fullyFilled())
        { // check if cell is already occupied by another currBlock
            for (int i = 0; i < blockCells.size(); i++)
            {
                blockCells[i]->setLetter("S"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; 
}

bool SBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        if (rotation == 1 || rotation == 3)
        {
            int rowOne = cells[0]->getCurrRow();
            int firstCol = cells[0]->getCurrCol();
            bottomLeftCell = blockGrid[rowOne][firstCol - 1];
        }
        else if (rotation == 0 || rotation == 2)
        {
            bottomLeftCell = cells[0];
        }
        blockCells.clear(); // remove all past cells from vector
        blockCells = cells; // reassign vector to new cells
        return true;
    }
    return false;
}

vector<Cell *> SBlock::getPositionZero()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 2]);
    return tempCells;
}

vector<Cell *> SBlock::getPositionOne()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
    return tempCells;
}

void SBlock::clockwise(int dropAmount)
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
    if (replaceCells(newRotation, "S"))
        down(dropAmount);
}

void SBlock::counterclockwise(int dropAmount)
{
    clockwise(dropAmount);
}

void SBlock::left(int dropAmount)
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
    if (replaceCells(newMovement, "S"))
        down(dropAmount);
}

void SBlock::right(int dropAmount)
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
    if (replaceCells(newMovement, "S"))
        down(dropAmount);
}

bool SBlock::down(int dropAmount)
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
        if (replaceCells(newMovement, "S"))
            continue;
        else
            return false;
    }
    return true;
}

bool SBlock::up(int dropAmount)
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
        if (replaceCells(newMovement, "S"))
            continue;
        else
            return false;
    }
    return true;
}

void SBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

SBlock::~SBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
