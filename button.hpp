#ifndef _BUTTON_H
#define _BUTTON_H

#include <functional>
#include "textbox.hpp"

class Button : public Widget {
protected:
    bool _pressed;
    std::string _text;
    std::function<void()> _on_pressed;
public:
    Button(Container* parent, int x, int y, int w, int h, std::string text);
    Button(Container* parent, int x, int y, int w, int h, std::string text, std::function<void()> on_pressed);
    virtual void draw();
    virtual void handle(genv::event);
};

#endif
