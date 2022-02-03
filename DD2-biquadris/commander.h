#ifndef COMMANDER_H
#define COMMANDER_H

#include <string>
#include <map>

// Forward Declaration
class Controller;

class Commander
{
private:
    enum Command
    {
        noCommand,
        up,
        left,
        right,
        down,
        clockwise,
        counterclockwise,
        drop,
        levelup,
        leveldown,
        norandom,
        random,
        sequence,
        I,
        J,
        L,
        O,
        S,
        T,
        Z,
        restart,
        rename,
        useMultipleSpecialActions
    };
    std::map<std::string, Commander::Command> commandMap;
    Controller *controller;

    void runLeft(int);
    void runRight(int);
    void runDown(int);
    void runClockwise(int);
    void runCounterclockwise(int);
    void promptSpecialAction();
    void runDrop(int);
    void operateLevelUp(int);
    void operateLevelDown(int);
    void runUp(int);

public:
    Commander(Controller *);
    void parseCommand(std::string);
};

#endif
