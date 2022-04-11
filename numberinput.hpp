#ifndef _NUMBER_INPUT_H
#define _NUMBER_INPUT_H

#include "widgets.hpp"

class Window;

class NumberInput : public Widget {
protected:
    int _n;
public:
    NumberInput(Window*, int x, int y, int w, int h, int n);
    virtual void handle(genv::event);
    virtual void draw();
};

#endif
