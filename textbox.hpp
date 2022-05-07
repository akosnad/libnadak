#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include "graphics.hpp"
#include "widgets.hpp"

class TextBox : public Widget {
protected:
    std::string _text;
public:
    TextBox(Container* parent, int x, int y, int w, std::string);
    virtual void draw();
    virtual void handle(genv::event ev);
    std::string get_text() { return _text; };
    void set_text(std::string s) { _text = s; };
};

#endif
