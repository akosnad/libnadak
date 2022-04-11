#ifndef INPUTTEXTBOX_H
#define INPUTTEXTBOX_H

#include "textbox.hpp"

class InputTextBox : public TextBox {
protected:
    bool _input_focus, _cursor_flash;
    bool fits_in_box(std::string to_fit);
public:
    InputTextBox(Window* parent, int x, int y, int w, std::string placeholder);
    InputTextBox(Window* parent, int x, int y, int w);
    virtual void draw();
    virtual void handle(genv::event ev);
    virtual void unfocus();
};

#endif
