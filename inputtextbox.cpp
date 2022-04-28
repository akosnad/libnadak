#include "inputtextbox.hpp"
#include <iostream>

using namespace std;
using namespace genv;

InputTextBox::InputTextBox(Window* parent, int x, int y, int w, string placeholder)
    : TextBox(parent, x, y, w, placeholder), _input_focus(false), _cursor_flash(true) {
        if(!fits_in_box("")) {
            cout << "Placeholder text doesn't fit in InputTextBox" << endl;
            exit(1);
        }
}

InputTextBox::InputTextBox(Window* parent, int x, int y, int w)
    : InputTextBox(parent, x, y, w, "") {
}

void InputTextBox::draw() {
    int tw = gout.twidth(_text);

    // box
    gout << color(255, 255, 255);
    gout << move_to(_x  - 2, _y - 2) << box_to(_x + _w + 2, _y + _h + 2);
    gout << color(0, 0, 0);
    if(_input_focus)
        gout << color(127, 127, 127);
    gout << move_to(_x, _y) << box_to(_x + _w, _y + _h);

    // text
    gout << move_to(_x, _y + gout.cascent() + 2) << color(255, 255, 255);
    gout << text(_text);

    if(_input_focus && _cursor_flash) {
        gout << move_to(_x + tw, _y + _h);
        gout << line_to(_x + tw, _y);
    }
}

bool InputTextBox::fits_in_box(string to_fit) {
    string ns = _text + to_fit;
    return gout.twidth(ns) <= _w;
}

void InputTextBox::handle(event ev) {
    if(ev.type == ev_mouse && ev.button == btn_left) {
        _input_focus = is_selected(ev);
    } else if(ev.type == ev_key && _input_focus) {
        if(ev.keycode == key_backspace) {
            if(_text.length() >= 1)
                _text.pop_back();
        } else if(ev.keycode == key_escape || ev.keycode == key_enter) {
            _input_focus = false;
        } else if(fits_in_box(ev.keyutf8)) {
            _text += ev.keyutf8;
        }
    } else if (ev.type == ev_timer) {
        _cursor_flash = !_cursor_flash;
    }
}

void InputTextBox::unfocus() {
    _input_focus = false;
}
