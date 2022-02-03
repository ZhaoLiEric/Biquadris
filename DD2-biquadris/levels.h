#ifndef LEVELS_H
#define LEVELS_H

#include <string>
#include <vector>

// Forward Declaration
class Blocks;

class Levels
{
public:
    Blocks *createBlockByType(char, int);
    virtual Blocks *generateNewBlock() = 0;
    virtual void norandom(std::string);
    virtual void random();
    virtual ~Levels() = 0;
    virtual void setSeed(int) = 0;
};

class Level0 : public Levels
{
    int index;
    std::vector<char> sequence;

public:
    Level0(bool, std::string, std::string);
    Blocks *generateNewBlock() override;
    void setSeed(int) override;
};

class Level1 : public Levels
{
    char generateRandom();
    int seed;

public:
    Level1();
    Blocks *generateNewBlock() override;
    void setSeed(int) override;
};

class Level2 : public Levels
{
    char generateRandom();
    int seed;

public:
    Level2();
    Blocks *generateNewBlock() override;
    void setSeed(int) override;
};


class Level3 : public Levels
{
    bool useSequence;
    int index;
    std::vector<char> sequence;
    int seed;
    char generateRandom();

public:
    Level3();
    Blocks *generateNewBlock() override;
    void norandom(std::string) override;
    void random() override;
    void setSeed(int) override;
};

class Level4 : public Levels
{
    bool useSequence;
    int index;
    std::vector<char> sequence;
    int seed;
    char generateRandom();

public:
    Level4();
    Blocks *generateNewBlock() override;
    void norandom(std::string) override;
    void random() override;
    void setSeed(int) override;
};

#endif 
