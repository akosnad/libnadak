#include "window.hpp"

using namespace std;
using namespace genv;

Window::Window(int width, int height) : _w(width), _h(height) {
    gout.open(_w, _h);
}

int Window::event_loop() {
    event ev;
    int focus = -1;
    gin.timer(500);
    while(gin >> ev ) {
        int old_focus = focus;
        if (ev.type == ev_mouse && ev.button == btn_left) {
            focus = -1;
            for (size_t i = 0; i < _widgets.size(); i++) {
                if (_widgets[i]->is_selected(ev)) {
                        focus = i;
                }
            }
        }

        if(old_focus != focus && old_focus != -1)
            _widgets[old_focus]->unfocus();
        if(focus != -1)
            _widgets[focus]->handle(ev);

        event_handler(ev);
        draw();
    }
    return 0;
}

void Window::draw() const {
    for(Widget* w : _widgets)
        w->draw();
    gout << refresh;
}

