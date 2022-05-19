#ifndef _NUMBER_INPUT_H
#define _NUMBER_INPUT_H

#include "widgets.hpp"
#include <functional>

class Window;

class NumberInput : public Widget {
protected:
    int _n, _max, _min;
    bool _inc_pressed, _dec_pressed, _input_focus;
    std::string _text;
    std::function<void(int)> _on_changed;
    void increment(int amount);
    void decrement(int amount);
    void limit();
public:
    NumberInput(Container*, int x, int y, int w, int h, int n, int min, int max);
    NumberInput(Container*, int x, int y, int w, int h, int n, int min, int max, std::function<void(int)> on_changed);
    NumberInput(Container*, int x, int y, int w, int h, int n);
    NumberInput(Container*, int x, int y, int w, int h, int n, std::function<void(int)> on_changed);
    virtual void handle(genv::event);
    virtual void draw();
    virtual void unfocus();
    int value() { return _n; }
    void set_limits(int min, int max);
};

#endif
