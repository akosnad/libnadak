#ifndef _WINDOW_H
#define _WINDOW_H

#include <vector>
#include "widgets.hpp"
#include "graphics.hpp"
#include "container.hpp"

class Window : public Container {
protected:
    int _w, _h;

    void draw() const;
public:
    Window(int width, int height);
    int event_loop();
    virtual void event_handler(genv::event) {};
};

#endif
