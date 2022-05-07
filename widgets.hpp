#ifndef _WIDGETS_H
#define _WIDGETS_H

#include "graphics.hpp"

class Container;

class Widget {
protected:
    Container* _parent;
    int _x, _y, _w, _h;
    bool _focus_on_hover;
public:
    Widget(Container* parent, int x, int y, int w, int h);
    virtual ~Widget();
    virtual bool is_selected(genv::event);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    virtual void unfocus() {};
    bool is_focus_on_hover() { return _focus_on_hover; }
};

#endif
