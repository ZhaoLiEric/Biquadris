#include "tblock.h"

using namespace std;

TBlock::TBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 3;
    this->levels = levelVal;
}

void TBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    // create pointers to cells in the currBlock
    Cell *zeroCell = blockGrid[3][1];
    zeroCell->setLetter("T");
    Cell *firstCell = blockGrid[2][0];
    firstCell->setLetter("T");
    Cell *secondCell = blockGrid[2][1];
    secondCell->setLetter("T");
    Cell *thirdCell = blockGrid[2][2];
    thirdCell->setLetter("T");
    // add to vector
    blockCells.push_back(zeroCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool TBlock::isLostGame()
{
    if (blockGrid[3][1]->fullyFilled() || blockGrid[2][0]->fullyFilled() || blockGrid[2][1]->fullyFilled() || blockGrid[2][2]->fullyFilled())
    {
        return true;
    }
    return false;
}

string TBlock::getType() const
{
    return "T";
}

Cell *TBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> TBlock::getBlockCells() const
{
    return blockCells;
}

bool TBlock::canValidMove(vector<Cell *> newBlockCells) const
{
    for (int i = 0; i < blockCells.size(); i++)
    {
        blockCells[i]->setLetter(""); // temporarily set old currBlock cells to empty letter
    }
    for (int i = 0; i < newBlockCells.size(); i++)
    {
        if (newBlockCells[i]->fullyFilled())
        { // check if cell is already occupied by another currBlock
            for (int i = 0; i < blockCells.size(); i++)
            {
                blockCells[i]->setLetter("T"); // temporarily set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; // newBlockCells does not overlap any existing blocks
}

bool TBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        // set bottomLeftCell
        if (rotation == 0 || rotation == 1)
        {
            int rowOne = cells[0]->getCurrRow();
            int firstCol = cells[0]->getCurrCol();
            bottomLeftCell = blockGrid[rowOne][firstCol - 1];
        }
        else if (rotation == 2 || rotation == 3)
        {
            bottomLeftCell = cells[0];
        }
        blockCells.clear(); // remove all past cells from vector
        blockCells = cells; // reassign vector to new cells
        return true;
    }
    return false;
}

vector<Cell *> TBlock::getPositionZero()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 2]);
    return tempCells;
}

vector<Cell *> TBlock::getPositionOne()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol + 1]);
    return tempCells;
}

vector<Cell *> TBlock::getPositionTwo()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    return tempCells;
}

vector<Cell *> TBlock::getPositionThree()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
    return tempCells;
}

void TBlock::clockwise(int dropAmount)
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
            return; // can't rotate
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
    if (replaceCells(newRotation, "T"))
        down(dropAmount);
}

void TBlock::counterclockwise(int dropAmount)
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
            return; // can't rotate
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
    if (replaceCells(newRotation, "T"))
        down(dropAmount);
}

void TBlock::left(int dropAmount)
{
    if (bottomLeftCell->getCurrCol() == 0)
    {
        return; // can't move left
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++)
    {
        curRow = blockCells[i]->getCurrRow();
        curCol = blockCells[i]->getCurrCol();
        newMovement.push_back(blockGrid[curRow][curCol - 1]);
    }
    if (replaceCells(newMovement, "T"))
        down(dropAmount);
}

void TBlock::right(int dropAmount)
{
    if (bottomLeftCell->getCurrCol() + maxWidth > 10)
    {
        return; // can't move right
    }
    vector<Cell *> newMovement;
    int curRow, curCol;
    for (int i = 0; i < blockCells.size(); i++)
    {
        curRow = blockCells[i]->getCurrRow();
        curCol = blockCells[i]->getCurrCol();
        newMovement.push_back(blockGrid[curRow][curCol + 1]);
    }
    if (replaceCells(newMovement, "T"))
        down(dropAmount);
}

bool TBlock::down(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 17)
        {
            return false; // can't move down, at bottom row
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int i = 0; i < blockCells.size(); i++)
        {
            curRow = blockCells[i]->getCurrRow();
            curCol = blockCells[i]->getCurrCol();
            newMovement.push_back(blockGrid[curRow + 1][curCol]);
        }
        if (replaceCells(newMovement, "T"))
            continue;
        else
            return false;
    }
    return true;
}

bool TBlock::up(int dropAmount)
{
    for (int i = 0; i < dropAmount; i++)
    {
        if (bottomLeftCell->getCurrRow() == 3)
        {
            return false; // can't move down, at bottom row
        }
        vector<Cell *> newMovement;
        int curRow, curCol;
        for (int i = 0; i < blockCells.size(); i++)
        {
            curRow = blockCells[i]->getCurrRow();
            curCol = blockCells[i]->getCurrCol();
            newMovement.push_back(blockGrid[curRow - 1][curCol]);
        }
        if (replaceCells(newMovement, "T"))
            continue;
        else
            return false;
    }
    return true;
}

void TBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

TBlock::~TBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
