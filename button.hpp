#ifndef _BUTTON_H
#define _BUTTON_H

#include "textbox.hpp"

class Button : public Widget {
protected:
    bool _pressed;
    std::string _text;
public:
    Button(Window* parent, int x, int y, int w, int h, std::string text);
    virtual void draw();
    virtual void handle(genv::event);
};

#endif
