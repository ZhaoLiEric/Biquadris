#include "oblock.h"

using namespace std;

OBlock::OBlock(int levelVal)
{
    this->bottomLeftCell = nullptr;
    this->rotation = 0;
    this->maxWidth = 2;
    this->levels = levelVal;
}

void OBlock::init(Cell *cell, vector<vector<Cell *>> grid)
{
    bottomLeftCell = cell;
    blockGrid = grid;
    // create pointers to cells in the currBlock
    if (isLostGame())
    {
        throw runtime_error("Game Over");
    }
    bottomLeftCell->setLetter("O");
    Cell *firstCell = blockGrid[3][1];
    firstCell->setLetter("O");
    Cell *secondCell = blockGrid[2][0];
    secondCell->setLetter("O");
    Cell *thirdCell = blockGrid[2][1];
    thirdCell->setLetter("O");
    // add to vector
    blockCells.push_back(bottomLeftCell);
    blockCells.push_back(firstCell);
    blockCells.push_back(secondCell);
    blockCells.push_back(thirdCell);
}

bool OBlock::isLostGame()
{
    if (bottomLeftCell->fullyFilled() || blockGrid[3][1]->fullyFilled() || blockGrid[2][0]->fullyFilled() || blockGrid[2][1]->fullyFilled())
    {
        return true;
    }
    return false;
}

string OBlock::getType() const
{
    return "O";
}

Cell *OBlock::getBottomLeftCell() const
{
    return bottomLeftCell;
}

vector<Cell *> OBlock::getBlockCells() const
{
    return blockCells;
}

bool OBlock::canValidMove(vector<Cell *> newBlockCells) const
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
                blockCells[i]->setLetter("O"); // set old currBlock cells to empty letter
            }
            return false;
        }
    }
    return true; // newBlockCells does not overlap any existing blocks
}

bool OBlock::replaceCells(vector<Cell *> cells, string letter)
{
    if (canValidMove(cells))
    {
        for (int i = 0; i < blockCells.size(); i++)
        {
            cells[i]->setLetter(letter);
        }
        bottomLeftCell = cells[0];
        blockCells.clear();       
        blockCells = cells;        
        return true;
    }
    return false;
}

void OBlock::clockwise(int dropAmount)
{
    down(dropAmount);
}

void OBlock::counterclockwise(int dropAmount)
{
    down(dropAmount);
}

void OBlock::left(int dropAmount)
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
    if (replaceCells(newMovement, "O"))
        down(dropAmount);
}

void OBlock::right(int dropAmount)
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
    if (replaceCells(newMovement, "O"))
        down(dropAmount);
}

bool OBlock::down(int dropAmount)
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
        if (replaceCells(newMovement, "O"))
            continue;
        else
            return false;
    }
    return true;
}

bool OBlock::up(int dropAmount)
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
        if (replaceCells(newMovement, "O"))
            continue;
        else
            return false;
    }
    return true;
}

void OBlock::drop()
{
    while (down() == true)
    {
        continue;
    }
}

OBlock::~OBlock()
{
    bottomLeftCell = nullptr;
    for (int i = 0; i < blockCells.size(); ++i)
    {
        blockCells[i]->setLetter("");
    }
    blockCells.clear();
}
