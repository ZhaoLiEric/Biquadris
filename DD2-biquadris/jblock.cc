#include "jblock.h"

using namespace std;

JBlock::JBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 3;
    this->levels = levelVal;
}

void JBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    // create pointers to cells in the currBlock
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    bottomLeftCell->setLetter("J");
    Cell *firstCell = blockGrid[3][1];
    firstCell->setLetter("J");
    Cell *secondCell = blockGrid[3][2];
    secondCell->setLetter("J");
    Cell *thirdCell = blockGrid[2][0];
    thirdCell->setLetter("J");
    // add to vector
    blockCells.push_back(bottomLeftCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool JBlock::isLostGame()
{
    if (bottomLeftCell->fullyFilled() || blockGrid[3][1]->fullyFilled() || blockGrid[3][2]->fullyFilled() || blockGrid[2][0]->fullyFilled())
    {
        return true;
    }
    return false;
}

string JBlock::getType() const
{
    return "J";
}

Cell *JBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> JBlock::getBlockCells() const
{
    return blockCells;
}

bool JBlock::canValidMove(vector<Cell *> newBlockCells) const
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
                blockCells[i]->setLetter("J"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; // newBlockCells does not overlap any existing blocks
}

bool JBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        if (rotation == 2)
        {
            int rowOne = cells[0]->getCurrRow();
            int firstCol = cells[0]->getCurrCol();
            bottomLeftCell = blockGrid[rowOne][firstCol - 2];
        }
        else if (rotation == 0 || rotation == 1 || rotation == 3)
        {
            bottomLeftCell = cells[0];
        }
        blockCells.clear(); // remove all past cells from vector
        blockCells = cells; // reassign vector to new cells
        return true;
    }
    return false;
}

vector<Cell *> JBlock::getPositionZero()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    return tempCells;
}

vector<Cell *> JBlock::getPositionOne()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    // add new rotation to tempCells
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol + 1]);
    return tempCells;
}

vector<Cell *> JBlock::getPositionTwo()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 2]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 2]);
    return tempCells;
}

vector<Cell *> JBlock::getPositionThree()
{
    int bottomLeftRow = bottomLeftCell->getCurrRow();
    int bottomLeftCol = bottomLeftCell->getCurrCol();
    vector<Cell *> tempCells;
    tempCells.push_back(bottomLeftCell);
    tempCells.push_back(blockGrid[bottomLeftRow][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 1][bottomLeftCol + 1]);
    tempCells.push_back(blockGrid[bottomLeftRow - 2][bottomLeftCol + 1]);
    return tempCells;
}

void JBlock::clockwise(int dropAmount)
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
            rotation = 0;
        }
    }
    if (replaceCells(newRotation, "J"))
        down(dropAmount);
}

void JBlock::counterclockwise(int dropAmount)
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
    if (replaceCells(newRotation, "J"))
        down(dropAmount);
}

void JBlock::left(int dropAmount)
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
    if (replaceCells(newMovement, "J"))
        down(dropAmount);
}

void JBlock::right(int dropAmount)
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
    if (replaceCells(newMovement, "J"))
        down(dropAmount);
}

bool JBlock::down(int dropAmount)
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
        if (replaceCells(newMovement, "J"))
            continue;
        else
            return false;
    }
    return true;
}

bool JBlock::up(int dropAmount)
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
        if (replaceCells(newMovement, "J"))
            continue;
        else
            return false;
    }
    return true;
}

void JBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

JBlock::~JBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
