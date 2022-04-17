#ifndef _DROPDOWN_H
#define _DROPDOWN_H

#include "widgets.hpp"
#include <vector>

class Window;

class Dropdown : public Widget {
protected:
    std::vector<std::string> _choices;
    int _selected_i, _closed_h, _dropdown_highlighted_i, _n_to_show, _scroll_i;
    bool _dropdown_pressed, _dropdown_open;
    void set_height();
    void scroll_down();
    void scroll_up();
public:
    Dropdown(Window* parent, int x, int y, int w, int h, int n_to_show, std::vector<std::string> choices);
    Dropdown(Window* parent, int x, int y, int w, int h, int n_to_show, std::vector<std::string> choices, int default_index);
    virtual void draw();
    virtual void handle(genv::event);
    virtual void unfocus();
    std::string value();
};

#endif
