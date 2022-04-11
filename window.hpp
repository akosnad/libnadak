#ifndef _WINDOW_H
#define _WINDOW_H

#include <vector>
#include "widgets.hpp"
#include "graphics.hpp"

class Window {
protected:
    std::vector<Widget*> _widgets;
    int _w, _h;

    void draw() const;
public:
    Window(int width, int height);
    int event_loop();
    void add_widget(Widget* w) { _widgets.push_back(w); };
    virtual void event_handler(genv::event) = 0;
};

#endif
