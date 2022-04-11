#include "numberinput.hpp"

using namespace std;
using namespace genv;

const int INC_DEC_BUTTON_W = 15;

NumberInput::NumberInput(Window* parent, int x, int y, int w, int h, int n, int min, int max)
    : Widget(parent, x, y, w, h), _n(n), _max(max), _min(min), _inc_pressed(false), _dec_pressed(false), _limited(true) {
}

NumberInput::NumberInput(Window* parent, int x, int y, int w, int h, int n)
    : NumberInput(parent, x, y, w, h, n, 0, 0) {
        _limited = false;
}

void NumberInput::limit() {
    if(!_limited)
        return;

    if(_n > _max)
        _n = _max;
    else if(_n < _min)
        _n = _min;
}

void NumberInput::increment(int amount) {
    _n += amount;
    limit();
}

void NumberInput::decrement(int amount) {
    _n -= amount;
    limit();
}

void NumberInput::handle(event ev) {
    if(ev.type == ev_mouse) {
        if(ev.button == btn_left) {
            if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y && ev.pos_y < _y + _h / 2) {
                _inc_pressed = true;
            } else if(ev.pos_x > _x + _w - INC_DEC_BUTTON_W && ev.pos_x < _x + _w
                && ev.pos_y > _y + _h / 2 && ev.pos_y < _y + _h) {
                _dec_pressed = true;
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

    gout << color(255, 255, 255);
    gout << move_to(_x, _y) << box(_w, _h);
    gout << color(0, 0, 0);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4 - INC_DEC_BUTTON_W - 2, _h - 4);

    // text
    string t = to_string(_n);
    int tx = _x + (_w - INC_DEC_BUTTON_W) / 2 - gout.twidth(t) / 2;
    int ty = _y + _h / 2 + gout.cdescent();
    gout << color(255, 255, 255) << move_to(tx, ty) << text(t);

    // increment button
    if(_inc_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + _w - 2 - INC_DEC_BUTTON_W, _y + 2) << box_to(_x + _w - 3, _y + (_h - 3) / 2);

    // decrement button
    if(_dec_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + _w - 2 - INC_DEC_BUTTON_W, _y + 2 + (_h - 3) / 2) << box_to(_x + _w - 3, _y + _h - 3);
}

void NumberInput::unfocus() {
    _inc_pressed = false;
    _dec_pressed = false;
}
