#include "sprite.hpp"
#include "bmp.hpp"

using namespace std;
using namespace genv;

Sprite::Sprite(Container* parent, int x, int y, int w, int h)
    : Widget(parent, x, y, w, h) {
    _canvas = genv::canvas(w, h);
}

Sprite::Sprite(Container* parent, int x, int y, int w, int h, string bitmap_path)
    : Sprite(parent, x, y, w, h) {
    load_from_bitmap(bitmap_path);
}

void Sprite::load_from_bitmap(string path) {
    BMP bmp(path);
    _canvas = bmp.to_canvas();
}

void Sprite::draw() {
    gout << stamp(_canvas, 0, 0, _w, _h, _x, _y);
}
