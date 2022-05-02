#ifndef _BOX_H
#define _BOX_H

#include <vector>
#include "widgets.hpp"
#include "container.hpp"

class Box : public Container, public Widget {
public:
    Box(Container* parent, int, int, int, int);
    Box(Container* parent, int, int, int, int, std::vector<Widget*> children);
    virtual void draw();
    virtual void handle(genv::event ev);
};

#endif
