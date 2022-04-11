#include "button.hpp"

using namespace std;
using namespace genv;

Button::Button(Window* parent, int x, int y, int w, int h, string text)
    : Widget(parent, x, y, w, h), _pressed(false), _text(text) {
}

void Button::draw() {
    gout << color(255, 255, 255);
    gout << move_to(_x, _y) << box(_w, _h);
    gout << color(0, 0, 0);
    if(_pressed)
        gout << color(127, 127, 127);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4, _h - 4);

    int tx = _x + _w / 2 - gout.twidth(_text) / 2;
    int ty = _y + _h / 2 + gout.cdescent();
    gout << color(255, 255, 255) << move_to(tx, ty) << text(_text);
}

void Button::handle(event ev) {
    if(ev.type == ev_mouse) {
        if(ev.button == btn_left)
            _pressed = true;
        else if(ev.button == -btn_left)
            _pressed = false;
    }
}
