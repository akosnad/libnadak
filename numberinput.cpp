#include "numberinput.hpp"

using namespace std;
using namespace genv;

NumberInput::NumberInput(Window* parent, int x, int y, int w, int h, int n)
    : Widget(parent, x, y, w, h), _n(n) {
}

void NumberInput::handle(event ev) {
}

void NumberInput::draw() {
    gout << color(255, 255, 255);
    gout << move_to(_x, _y) << box(_w, _h);
    gout << color(0, 0, 0);
    gout << move_to(_x + 2, _y + 2) << box(_w - 4 - 30, _h - 4);

    // increment, decrement buttons
    gout << move_to(_x + _w - 2, _y + 2) << box(_w - 4 - 30, _h - 4);
}
