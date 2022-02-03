#include "lblock.h"

using namespace std;

LBlock::LBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 3;
    this->levels = levelVal;
}

void LBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    // create pointers to cells in the currBlock
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    bottomLeftCell->setLetter("L");
    Cell *firstCell = blockGrid[3][1];
    firstCell->setLetter("L");
    Cell *secondCell = blockGrid[3][2];
    secondCell->setLetter("L");
    Cell *thirdCell = blockGrid[2][2];
    thirdCell->setLetter("L");
    // add to vector
    blockCells.push_back(bottomLeftCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool LBlock::isLostGame()
{
    if (bottomLeftCell->fullyFilled() || blockGrid[3][1]->fullyFilled() || blockGrid[3][2]->fullyFilled() || blockGrid[2][2]->fullyFilled())
    {
        return true;
    }
    return false;
}

string LBlock::getType() const
{
    return "L";
}

Cell *LBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> LBlock::getBlockCells() const
{
    return blockCells;
}

bool LBlock::canValidMove(vector<Cell *> newBlockCells) const
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
                blockCells[i]->setLetter("L"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; // newBlockCells does not overlap any existing blocks
}

bool LBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        if (rotation == 3)
        {
            int rowOne = cells[0]->getCurrRow();
            int firstCol = cells[0]->getCurrCol();
            bottomLeftCell = blockGrid[rowOne][firstCol - 1];
        }
        else if (rotation == 0 || rotation == 1 || rotation == 2)
        {
            bottomLeftCell = cells[0];
        }
        blockCells.clear(); // remove all past cells
        blockCells = cells; 
        return true;
    }
    return false;
}

vector<Cell *> LBlock::getPositionZero()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 2]);
    return tempCells;
}

vector<Cell *> LBlock::getPositionOne()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
    return tempCells;
}

vector<Cell *> LBlock::getPositionTwo()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 2]);
    return tempCells;
}

vector<Cell *> LBlock::getPositionThree()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol + 1]);
    return tempCells;
}

void LBlock::clockwise(int dropAmount)
{
    vector<Cell *> newRotation;
    if (rotation == 0)
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
    else if (rotation == 1)
    {
        if (bottomLeftCell->getCurrCol() + 3 > 10)
        {
            return; 
        }
        try
        {
            newRotation = getPositionTwo();
        }
        catch (...)
        {
            return;
        }
        if (canValidMove(newRotation))
        {
            maxWidth = 3;
            rotation++;
        }
    }
    else if (rotation == 2)
    {
        try
        {
            newRotation = getPositionThree();
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
    else if (rotation == 3)
    {
        if (bottomLeftCell->getCurrCol() + 3 > 10)
        {
            return; // can't rotate
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
            rotation = 0;
        }
    }
    if (replaceCells(newRotation, "L"))
        down(dropAmount);
}

void LBlock::counterclockwise(int dropAmount)
{
    vector<Cell *> newRotation;
    if (rotation == 0)
    {
        try
        {
            newRotation = getPositionThree();
        }
        catch (...)
        {
            return;
        }
        if (canValidMove(newRotation))
        {
            maxWidth = 2;
            rotation = 3;
        }
    }
    else if (rotation == 1)
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
            rotation--;
        }
    }
    else if (rotation == 2)
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
            rotation--;
        }
    }
    else if (rotation == 3)
    {
        if (bottomLeftCell->getCurrCol() + 3 > 10)
        {
            return;
        }
        try
        {
            newRotation = getPositionTwo();
        }
        catch (...)
        {
            return;
        }
        if (canValidMove(newRotation))
        {
            maxWidth = 3;
            rotation--;
        }
    }
    if (replaceCells(newRotation, "L"))
        down(dropAmount);
}

void LBlock::left(int dropAmount)
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
    if (replaceCells(newMovement, "L"))
        down(dropAmount);
}

void LBlock::right(int dropAmount)
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
    if (replaceCells(newMovement, "L"))
        down(dropAmount);
}

bool LBlock::down(int dropAmount)
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
        if (replaceCells(newMovement, "L"))
            continue;
        else
            return false;
    }
    return true;
}

bool LBlock::up(int dropAmount)
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
        if (replaceCells(newMovement, "L"))
            continue;
        else
            return false;
    }
    return true;
}

void LBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

LBlock::~LBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
