#ifndef _SPRITE_H
#define _SPRITE_H

#include "widgets.hpp"

class Sprite : public Widget {
    genv::canvas _canvas;
public:
    Sprite(Container* parent, int x, int y, int w, int h);
    Sprite(Container* parent, int x, int y, int w, int h, std::string bitmap_path);
    void load_from_bitmap(std::string path);

    virtual void handle(genv::event) {}
    virtual void draw();
};

#endif
