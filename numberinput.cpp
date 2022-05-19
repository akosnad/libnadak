#include "numberinput.hpp"
#include <iostream>

using namespace std;
using namespace genv;

static const int INC_DEC_BUTTON_W = 16;

NumberInput::NumberInput(Container* parent, int x, int y, int w, int h, int n, int min, int max)
    : Widget(parent, x, y, w, h), _n(n), _max(max), _min(min), _inc_pressed(false), _dec_pressed(false), _input_focus(false), _text(to_string(_n)) {
}

NumberInput::NumberInput(Container* parent, int x, int y, int w, int h, int n)
    : NumberInput(parent, x, y, w, h, n, INT32_MIN, INT32_MAX) {
}

void NumberInput::limit() {
    if(_n > _max)
        _n = _max;
    else if(_n < _min)
        _n = _min;

    _text = to_string(_n);
}

inline void NumberInput::increment(int amount) {
    _n += amount;
    limit();
}

inline void NumberInput::decrement(int amount) {
    _n -= amount;
    limit();
}

void NumberInput::handle(event ev) {
    if(ev.type == ev_key) {
        if(ev.keycode == key_pgup) {
            increment(10);
        } else if(ev.keycode == key_pgdn) {
            decrement(10);
        } else if(ev.keycode == key_up) {
            increment(1);
        } else if(ev.keycode == key_down) {
            decrement(1);
        } else if(ev.keycode == key_escape || ev.keycode == key_enter) {
            unfocus();
        } else if(_input_focus) {
            if(ev.keycode == key_backspace && _text.length() > 0) {
                _text.pop_back();
            } else if(ev.keycode >= 48 && ev.keycode <= 57 && _text.length() < 9) {
                _text += to_string(ev.keycode - 48);
                _n = stoi(_text);
            } else if(ev.keycode == 45 && _text.length() == 0) {
                _text += "-";
            }
        }

    }
    if(ev.type == ev_mouse) {
        if(ev.button == btn_left) {
            if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y && ev.pos_y < _y + _h / 2) {
                _inc_pressed = true;
                _input_focus = false;
            } else if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y + _h / 2 && ev.pos_y < _y + _h) {
                _dec_pressed = true;
                _input_focus = false;
            } else {
                _input_focus = true;
            }
        } else if(ev.button == -btn_left) {
            if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y && ev.pos_y < _y + _h / 2) {
                increment(1);
                _inc_pressed = false;
            } else if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y + _h / 2 && ev.pos_y < _y + _h) {
                decrement(1);
                _dec_pressed = false;
            }
        }
    }
}

void NumberInput::draw() {
    int tw = gout.twidth(_text);

    gout << color(255, 255, 255);
    gout << move_to(_x, _y) << box(_w, _h);
    if(_input_focus)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4 - INC_DEC_BUTTON_W - 2, _h - 4);

    // text
    int tx = _x + (_w - INC_DEC_BUTTON_W) / 2 - tw / 2;
    int ty = _y + _h / 2 - gout.cascent() + gout.cdescent() + 2;
    gout << color(255, 255, 255) << move_to(tx, ty) << text(_text);

    // cursor
    if(_input_focus) {
        gout << move_to(tx + tw, ty);
        gout << line_to(tx + tw, ty + gout.cascent());
    }

    // increment button
    if(_inc_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + _w - 2 - INC_DEC_BUTTON_W, _y + 2) << box_to(_x + _w - 3, _y + (_h - 3) / 2);
    gout << color(255, 255, 255) << move_to(_x + _w - INC_DEC_BUTTON_W / 2 - 5, (_y + _h / 2) - gout.cascent()) << text("+");

    // decrement button
    if(_dec_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + _w - 2 - INC_DEC_BUTTON_W, _y + 2 + (_h - 3) / 2) << box_to(_x + _w - 3, _y + _h - 3);
    gout << color(255, 255, 255) << move_to(_x + _w - INC_DEC_BUTTON_W / 2 - 5, _y + _h - gout.cascent() - 2) << text("-");
}

void NumberInput::unfocus() {
    _inc_pressed = false;
    _dec_pressed = false;
    _input_focus = false;
    limit();
}
