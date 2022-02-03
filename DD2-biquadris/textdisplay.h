#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "displayobserver.h"

class TextDisplay : public DisplayObserver
{
public:
    TextDisplay(Controller *);
    ~TextDisplay() override;
    void displayBoard() override;
};

#endif 
