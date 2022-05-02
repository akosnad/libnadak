#ifndef _NUMBER_INPUT_H
#define _NUMBER_INPUT_H

#include "widgets.hpp"

class Window;

class NumberInput : public Widget {
protected:
    int _n, _max, _min;
    bool _inc_pressed, _dec_pressed, _input_focus;
    std::string _text;
    void increment(int amount);
    void decrement(int amount);
    void limit();
public:
    NumberInput(Container*, int x, int y, int w, int h, int n, int min, int max);
    NumberInput(Container*, int x, int y, int w, int h, int n);
    virtual void handle(genv::event);
    virtual void draw();
    virtual void unfocus();
    int value() { return _n; }
};

#endif
