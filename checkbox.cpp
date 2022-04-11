#include "checkbox.hpp"
#include "graphics.hpp"
#include <cmath>
using namespace genv;

CheckBox::CheckBox(Window* parent, int x, int y, int w, int h)
    : Widget(parent, x, y, w, h), _checked(false)
{
}

void CheckBox::draw()
{
    gout << color(255, 255, 255);
    gout << move_to(_x, _y) << box(_w, _h);
    gout << color(0, 0, 0);
    if (_checked)
        gout << color(127, 127, 127);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4, _h - 4);
    if(_checked) {
        //gout << color(255, 255, 255);
        //gout << move_to(_x - 2 + _x / 4, _y - 2 + _y / 4) << line_to(_x + _w / 2, _y + _h / 2);
        //gout << line_to(_x + _w - 2, _y + 2);
    }
}

void CheckBox::handle(event ev)
{
    if (ev.type == ev_key && (ev.keycode == key_enter || ev.keycode == ' ')) {
            _checked = !_checked;
    }
    if (ev.type == ev_mouse && is_selected(ev) && ev.button==btn_left) {
        _checked = !_checked;
    }
}
