#include "box.hpp"

using namespace std;
using namespace genv;

Box::Box(Container* parent, int x, int y, int w, int h)
    : Container(), Widget(parent, x, y, w, h) {
}

Box::Box(Container* parent, int x, int y, int w, int h, vector<Widget*> children)
    : Container(children), Widget(parent, x, y, w, h) {
}

void Box::draw() {
    gout << color(16, 16, 16) << move_to(_x, _y) << box(_w, _h);
    draw_children();
}

void Box::handle(event ev) {
    handle_children_events(ev);
}
