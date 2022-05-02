#include "container.hpp"

using namespace std;
using namespace genv;

Container::Container()
    : _focus(-1) {
}

Container::Container(vector<Widget*> children)
    : _children(children) {
}

void Container::handle_children_events(event ev) {
    int old_focus = _focus;
    if (ev.type == ev_mouse && ev.button == btn_left) {
        _focus = -1;
        for (size_t i = 0; i < _children.size(); i++) {
            if (_children[i]->is_selected(ev)) {
                    _focus = i;
            }
        }
    }

    if(old_focus != _focus && old_focus != -1)
        _children[old_focus]->unfocus();
    if(_focus != -1)
        _children[_focus]->handle(ev);
}

void Container::draw_children() const {
    for(Widget* w: _children)
        w->draw();
}
