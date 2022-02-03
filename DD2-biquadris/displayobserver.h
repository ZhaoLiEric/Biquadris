#ifndef DISPLAYOBSERVER_H
#define DISPLAYOBSERVER_H

class Controller;

class DisplayObserver
{
protected:
    Controller *controller;

public:
    virtual void displayBoard() = 0;
    virtual ~DisplayObserver() = 0;
};

#endif 
