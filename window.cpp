#include "window.hpp"

using namespace std;
using namespace genv;

Window::Window(int width, int height) : Container(), _w(width), _h(height) {
    gout.open(_w, _h);
    gout.load_font("LiberationSans-Regular.ttf");
}

int Window::event_loop() {
    event ev;
    gin.timer(500);
    while(gin >> ev ) {
        handle_children_events(ev);
        event_handler(ev);
        draw();
    }
    return 0;
}

void Window::draw() const {
    gout << color(0, 0, 0) << move_to(0, 0) << box(_w, _h);
    draw_children();
    gout << refresh;
}

