#include "widgets.hpp"
#include "container.hpp"
#include "graphics.hpp"

using namespace genv;

Widget::Widget(Container* parent, int x, int y, int w, int h) : _parent(parent), _x(x), _y(y), _w(w), _h(h)
{
    _parent->add_child(this);
}

Widget::~Widget() {
    _parent->erase_child(this);
}

bool Widget::is_selected(event ev)
{
    return ev.pos_x > _x && ev.pos_x < _x + _w &&
        ev.pos_y > _y && ev.pos_y < _y + _h;
}

