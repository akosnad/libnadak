#ifndef _WIDGETS_H
#define _WIDGETS_H

#include "graphics.hpp"

class Container;

class Widget {
protected:
    Container* _parent;
    int _x, _y, _w, _h;
public:
    Widget(Container*, int, int, int, int);
    virtual bool is_selected(genv::event);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    virtual void unfocus() {};
};

#endif
