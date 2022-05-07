#ifndef _CONTAINER_H
#define _CONTAINER_H

#include <vector>
#include "widgets.hpp"

class Container {
protected:
    std::vector<Widget*> _children;
    int _focus;
public:
    Container();
    Container(std::vector<Widget*>);
    void add_child(Widget* w) { _children.push_back(w); };
    void erase_child(Widget* w);
    void handle_children_events(genv::event);
    void draw_children() const;
    void focus_child(Widget* w);
};

#endif
