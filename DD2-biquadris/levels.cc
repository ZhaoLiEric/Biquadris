#include "levels.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include "starblock.h"
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

Blocks *Levels::createBlockByType(char blockChar, int levels)
{
    if (blockChar == 'I')
    {
        return new IBlock{levels};
    }
    else if (blockChar == 'J')
    {
        return new JBlock{levels};
    }
    else if (blockChar == 'L')
    {
        return new LBlock{levels};
    }
    else if (blockChar == 'O')
    {
        return new OBlock{levels};
    }
    else if (blockChar == 'S')
    {
        return new SBlock{levels};
    }
    else if (blockChar == 'T')
    {
        return new TBlock{levels};
    }
    else if (blockChar == 'Z')
    {
        return new ZBlock{levels};
    }
    else if (blockChar == '*')
    {
        return new StarBlock{levels};
    }
    else
    {
        return nullptr;
    }
}

void Levels::norandom(std::string)
{
   
}

void Levels::random()
{
    
}

Levels::~Levels() = default;

// levels 0
Level0::Level0(bool isPlayerOne, string sequence1, string sequence2) : // Add each letter from input file to a vector
                                                                       index{0}
{
    string sequenceFile = isPlayerOne ? sequence1 : sequence2; // set sequence
    ifstream file{sequenceFile};

    char letter;
    while (file >> letter)
    {
        sequence.push_back(letter);
    }
}

Blocks *Level0::generateNewBlock()
{

    Blocks *newBlock = createBlockByType(sequence[index], 0);

    index++; // increase index, reset to zero if past end of vector
    if (index >= sequence.size())
    {
        index = 0;
    }

    return newBlock;
}

void Level0::setSeed(int newSeed)
{
    //Does nothing because not random
}

// levels 1
char Level1::generateRandom()
{
    int r = rand() % 12;
    if (r < 2)
    {
        return 'I';
    }
    else if (r < 4)
    {
        return 'J';
    }
    else if (r < 6)
    {
        return 'L';
    }
    else if (r < 8)
    {
        return 'O';
    }
    else if (r < 9)
    {
        return 'S';
    }
    else if (r < 11)
    {
        return 'T';
    }
    else
    { // if (r < 12) {
        return 'Z';
    }
}

Level1::Level1() = default;

Blocks *Level1::generateNewBlock()
{
    Blocks *newBlock = createBlockByType(generateRandom(), 1);

    return newBlock;
}

void Level1::setSeed(int newSeed)
{
    seed = newSeed;
    srand(seed);
}

// levels 2
char Level2::generateRandom()
{
    int r = rand() % 7;
    if (r < 1)
    {
        return 'I';
    }
    else if (r < 2)
    {
        return 'J';
    }
    else if (r < 3)
    {
        return 'L';
    }
    else if (r < 4)
    {
        return 'O';
    }
    else if (r < 5)
    {
        return 'S';
    }
    else if (r < 6)
    {
        return 'T';
    }
    else
    { // if (r < 7) {
        return 'Z';
    }
}

Level2::Level2() = default;

Blocks *Level2::generateNewBlock()
{
    Blocks *newBlock = createBlockByType(generateRandom(), 2);

    return newBlock;
}

void Level2::setSeed(int newSeed)
{
    seed = newSeed;
    srand(seed);
}

// levels 3
char Level3::generateRandom()
{
    int r = rand() % 9;
    if (r < 1)
    {
        return 'I';
    }
    else if (r < 2)
    {
        return 'J';
    }
    else if (r < 3)
    {
        return 'L';
    }
    else if (r < 4)
    {
        return 'O';
    }
    else if (r < 6)
    {
        return 'S';
    }
    else if (r < 7)
    {
        return 'T';
    }
    else
    { // if (r < 9) {
        return 'Z';
    }
}

Level3::Level3() : useSequence{false} {}

Blocks *Level3::generateNewBlock()
{
    char nextBlockChar;

    if (useSequence)
    {
        nextBlockChar = sequence[index];

        index++;
        if (index >= sequence.size())
        {
            index = 0;
        }
    }
    else
    {
        nextBlockChar = generateRandom();
    }

    Blocks *newBlock = createBlockByType(nextBlockChar, 3);

    return newBlock;
}

void Level3::norandom(string filename)
{
    useSequence = true;

    ifstream file{filename};

    char letter;
    while (file >> letter)
    {
        sequence.push_back(letter);
    }
}

void Level3::random()
{
    useSequence = false;
    index = 0;
    sequence.clear();
}

void Level3::setSeed(int newSeed)
{
    seed = newSeed;
    srand(seed);
}

// levels 4
char Level4::generateRandom()
{
    int r = rand() % 9;
    if (r < 1)
    {
        return 'I';
    }
    else if (r < 2)
    {
        return 'J';
    }
    else if (r < 3)
    {
        return 'L';
    }
    else if (r < 4)
    {
        return 'O';
    }
    else if (r < 6)
    {
        return 'S';
    }
    else if (r < 7)
    {
        return 'T';
    }
    else
    { // if (r < 9) {
        return 'Z';
    }
}

Level4::Level4() : useSequence{false} {}

Blocks *Level4::generateNewBlock()
{
    char nextBlockChar;

    if (useSequence)
    {
        nextBlockChar = sequence[index];

        index++;
        if (index >= sequence.size())
        {
            index = 0;
        }
    }
    else
    {
        nextBlockChar = generateRandom();
    }

    Blocks *newBlock = createBlockByType(nextBlockChar, 3);

    return newBlock;
}

void Level4::norandom(string filename)
{
    useSequence = true;

    ifstream file{filename};

    char letter;
    while (file >> letter)
    {
        sequence.push_back(letter);
    }
}

void Level4::random()
{
    useSequence = false;
    index = 0;
    sequence.clear();
}

void Level4::setSeed(int newSeed)
{
    seed = newSeed;
    srand(seed);
}

