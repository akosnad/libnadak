#ifndef _CHECKBOX_H
#define _CHECKBOX_H

#include "graphics.hpp"
#include "widgets.hpp"
#include "window.hpp"

class CheckBox : public Widget {
protected:
    bool _checked;
public:
    CheckBox(Window*, int, int, int, int);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual bool is_checked() { return _checked; };
};


#endif
