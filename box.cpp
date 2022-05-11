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
    draw_children();
}

void Box::handle(event ev) {
    handle_children_events(ev);
}
