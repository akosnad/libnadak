#include "dropdown.hpp"
#include <iostream>

using namespace std;
using namespace genv;

static const int DROPDOWN_BUTTON_W = 15;

Dropdown::Dropdown(Window* parent, int x, int y, int w, int h, std::vector<std::string> choices)
    : Widget(parent, x, y, w, h), _choices(choices), _selected_i(-1), _closed_h(h), _dropdown_highlighted_i(-1), _dropdown_pressed(false), _dropdown_open(false) {
}

Dropdown::Dropdown(Window* parent, int x, int y, int w, int h, std::vector<std::string> choices, int default_index)
    : Widget(parent, x, y, w, h), _choices(choices), _selected_i(-1), _closed_h(h), _dropdown_highlighted_i(-1), _dropdown_pressed(false), _dropdown_open(false) {
        if(default_index >= 0 && default_index < (int)_choices.size()) {
            _selected_i = default_index;
            _dropdown_highlighted_i = default_index;
        }
}

string Dropdown::value() {
    if(_selected_i < 0 || _selected_i >= (int)_choices.size())
        return "";

    return _choices[_selected_i];
}

void Dropdown::set_height() {
    if(_dropdown_open)
        _h = _closed_h + _choices.size() * (gout.cascent() + gout.cdescent() + 4);
    else _h = _closed_h;
}

void Dropdown::handle(event ev) {
    if(ev.type == ev_key && (ev.keycode == key_escape || ev.keycode == key_enter) && _dropdown_open) {
        unfocus();
    }
    if(ev.type == ev_mouse) {
        if(_dropdown_open && ev.pos_y > _y + _closed_h) {
            // inside dropdown
            if(ev.button == btn_left) {
                int ch = gout.cascent() + gout.cdescent() + 4;
                int i = (ev.pos_y - (_y + _closed_h)) / ch;
                _dropdown_highlighted_i = i;
            } else if(ev.button == -btn_left) {
                _selected_i = _dropdown_highlighted_i;
                _dropdown_open = false;
                set_height();
                // gout.movemouse(ev.pos_x, _y + _h / 2);
            }
        } else if(ev.button == btn_left) {
            _dropdown_pressed = true;
        } else if(ev.button == -btn_left) {
            _dropdown_pressed = false;
            _dropdown_open = !_dropdown_open;
            set_height();
        }
    }
}

void Dropdown::draw() {
    gout << color(255, 255, 255) << move_to(_x, _y) << box(_w, _closed_h);

    if(_dropdown_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + 2, _y + 2) << box(_w - 8 - DROPDOWN_BUTTON_W, _closed_h - 4);

    if(_selected_i >= 0 && _selected_i < (int)_choices.size())
        gout << color(255, 255, 255) << move_to(_x + 4, _y + 2 + gout.cascent()) << text(_choices[_selected_i]);

    // dropdown button
    if(_dropdown_open || _dropdown_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + (_w - 4 - DROPDOWN_BUTTON_W), _y + 2) << box_to(_x + _w - 3, _y + _closed_h - 3);

    gout << color(255, 255, 255) << move_to(_x + _w - 4 - (DROPDOWN_BUTTON_W / 2) - gout.twidth("v") / 2, _y + 2 + gout.cascent()) << text("v");

    // dropdown
    if(_dropdown_open) {
        int ch = gout.cascent() + gout.cdescent() + 4;
        int dh = _choices.size() * ch;
        gout << color(255, 255, 255) << move_to(_x, _y + _closed_h) << box(_w, dh);

        for(size_t i = 0; i < _choices.size(); i++) {
            if(_dropdown_highlighted_i == (int)i)
                gout << color(127, 127, 127);
            else
                gout << color(0, 0, 0);

            gout << move_to(_x + 2, _y + 4 + (i + 1) * ch) << box(_w - 4, ch - 2);
            gout << color(255, 255, 255) << move_to(_x + 4, _y + 4 + (i + 1) * ch + gout.cascent()) << text(_choices[i]);
        }
    }
}

void Dropdown::unfocus() {
    _dropdown_open = false;
    _dropdown_pressed = false;
    set_height();
}
