#include "textbox.hpp"

using namespace std;
using namespace genv;

TextBox::TextBox(Container* parent, int x, int y, int w, string text)
    : Widget(parent, x, y, w, gout.cascent() + gout.cdescent() + 4), _text(text) {
}

void TextBox::draw() {
    gout << move_to(_x,_y + gout.cdescent()) << color(255, 255, 255);
    gout << text(_text);
}

void TextBox::handle(event ev) {
}
