#include "sprite.hpp"
#include "bmp.hpp"
#include <map>
#include <iostream>

using namespace std;
using namespace genv;

static map<string, canvas> bitmap_cache = {};

Sprite::Sprite(Container* parent, int x, int y, int w, int h)
    : Widget(parent, x, y, w, h) {
    _canvas = genv::canvas(w, h);
}

Sprite::Sprite(Container* parent, int x, int y, int w, int h, string bitmap_path)
    : Sprite(parent, x, y, w, h) {
    load_from_bitmap(bitmap_path);
}

void Sprite::load_from_bitmap(string path) {
    auto it = bitmap_cache.find(path);
    if(it != bitmap_cache.end()) {
        cout << "using cache for " << path << endl;
        _canvas = it->second;
        return;
    }

    cout << "no cache for " << path << ", loading from file" << endl;
    BMP bmp(path);
    _canvas = bmp.to_canvas();
    bitmap_cache[path] = _canvas;
}

void Sprite::move(int x, int y) {
    _x = x;
    _y = y;
}

void Sprite::draw() {
    gout << stamp(_canvas, 0, 0, _w, _h, _x, _y);
}
