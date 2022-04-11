#include "widgets.hpp"
#include "window.hpp"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(Window* parent, int x, int y, int w, int h) : _parent(parent), _x(x), _y(y), _w(w), _h(h)
{
    _parent->add_widget(this);
}

bool Widget::is_selected(event ev)
{
    return ev.pos_x > _x && ev.pos_x < _x + _w &&
        ev.pos_y > _y && ev.pos_y < _y + _h;
}

