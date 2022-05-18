#include "dropdown.hpp"
#include <iostream>

using namespace std;
using namespace genv;

static const int DROPDOWN_BUTTON_W = 15;
static const int CH = gout.cascent() + gout.cdescent();
static const int DH = CH + 4;

Dropdown::Dropdown(Container* parent, int x, int y, int w, int h, int n_to_show, std::vector<std::string> choices)
    : Dropdown(parent, x, y, w, h, n_to_show, choices, -1) {
}

Dropdown::Dropdown(Container* parent, int x, int y, int w, int h, int n_to_show, std::vector<std::string> choices, int default_index)
    : Widget(parent, x, y, w, h), _choices(choices), _selected_i(-1), _closed_h(h), _dropdown_highlighted_i(-1), _n_to_show(n_to_show), _scroll_i(0), _dropdown_pressed(false), _dropdown_open(false) {
        if(default_index >= 0 && default_index < (int)_choices.size()) {
            _selected_i = default_index;
            _dropdown_highlighted_i = default_index;
            _scroll_i = default_index;
        }
}

string Dropdown::value() {
    if(_selected_i < 0 || _selected_i >= (int)_choices.size() || _choices.size() == 0)
        return "";

    return _choices[_selected_i];
}

void Dropdown::set_height() {
    if(_dropdown_open) {
        if((int)_choices.size() < _n_to_show)
            _h = _closed_h + _choices.size() * DH;
        else
            _h = _closed_h + _n_to_show * DH;
    } else
        _h = _closed_h;
}

void Dropdown::scroll_down() {
    _dropdown_highlighted_i++;

    if(_dropdown_highlighted_i > (int)_choices.size() - 1)
        _dropdown_highlighted_i = (int)_choices.size() - 1;

    if(_dropdown_highlighted_i >= _scroll_i + _n_to_show)
        _scroll_i++;

    if(!_dropdown_open)
        _selected_i = _dropdown_highlighted_i;
}

void Dropdown::scroll_up() {
    _dropdown_highlighted_i--;

    if(_dropdown_highlighted_i < 0)
        _dropdown_highlighted_i = 0;

    if(_dropdown_highlighted_i < _scroll_i)
        _scroll_i--;

    if(!_dropdown_open)
        _selected_i = _dropdown_highlighted_i;
}

void Dropdown::handle(event ev) {
    if(ev.type == ev_key) {
        if(ev.keycode == key_escape && _dropdown_open) {
            unfocus();
        } else if(ev.keycode == key_enter && _dropdown_open) {
            _selected_i = _dropdown_highlighted_i;
            unfocus();
        } else if(ev.keycode == key_down) {
            scroll_down();
        } else if(ev.keycode == key_up) {
            scroll_up();
        }
    } else if(ev.type == ev_mouse) {
        if(ev.button == btn_wheeldown) {
            scroll_down();
        } else if(ev.button == btn_wheelup) {
            scroll_up();
        } else if(_dropdown_open && ev.pos_y > _y + _closed_h) {
            // inside dropdown
            if(ev.button == btn_left) {
                int ch = gout.cascent() + gout.cdescent() + 4;
                int i = (ev.pos_y - (_y + _closed_h)) / ch;
                _dropdown_highlighted_i = i + _scroll_i;
            } else if(ev.button == -btn_left) {
                _selected_i = _dropdown_highlighted_i;
                _dropdown_open = false;
                set_height();
            }
        } else if(ev.button == btn_left) {
            _dropdown_pressed = true;
        } else if(ev.button == -btn_left) {
            _dropdown_pressed = false;
            _dropdown_open = !_dropdown_open;
            set_height();
        }
    }
}

string Dropdown::remove_selected() {
    if(_choices.size() == 0)
        return "";

    string s = _choices[_selected_i];
    _choices.erase(_choices.begin() + _selected_i);

    if(_selected_i >= (int)_choices.size())
        _selected_i = (int)_choices.size() - 1;

    if(_dropdown_highlighted_i >= (int)_choices.size())
        _dropdown_highlighted_i = (int)_choices.size() - 1;
    return s;
}

void Dropdown::push(string s) {
    _choices.push_back(s);
}

void Dropdown::set(vector<string> choices) {
    _choices = choices;

    if(_selected_i >= (int)_choices.size())
        _selected_i = (int)_choices.size() - 1;

    if(_dropdown_highlighted_i >= (int)_choices.size())
        _dropdown_highlighted_i = (int)_choices.size() - 1;
}

void Dropdown::draw() {
    gout << color(255, 255, 255) << move_to(_x, _y) << box(_w, _closed_h);

    if(_dropdown_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + 2, _y + 2) << box(_w - 8 - DROPDOWN_BUTTON_W, _closed_h - 4);

    if(_selected_i >= 0 && _selected_i < (int)_choices.size())
        gout << color(255, 255, 255) << move_to(_x + 4, _y + 2 + gout.cascent()) << text(_choices[_selected_i]);

    // dropdown button
    if(_dropdown_open || _dropdown_pressed)
        gout << color(127, 127, 127);
    else
        gout << color(0, 0, 0);
    gout << move_to(_x + (_w - 4 - DROPDOWN_BUTTON_W), _y + 2) << box_to(_x + _w - 3, _y + _closed_h - 3);

    gout << color(255, 255, 255) << move_to(_x + _w - 4 - (DROPDOWN_BUTTON_W / 2) - gout.twidth("v") / 2, _y + 2 + gout.cascent()) << text("v");

    // dropdown
    if(_dropdown_open) {
        int n = _n_to_show;
        if(n > (int)_choices.size())
            n = _choices.size();

        int dh = n * DH;
        gout << color(255, 255, 255) << move_to(_x, _y + _closed_h) << box(_w, dh);

        for(int i = 0; i < n; i++) {
            if(_dropdown_highlighted_i == i + _scroll_i)
                gout << color(127, 127, 127);
            else
                gout << color(0, 0, 0);

            gout << move_to(_x + 2, _y + 4 + (i + 1) * DH) << box(_w - 4, DH - 2);
            if(i +_scroll_i < (int)_choices.size())
                gout << color(255, 255, 255) << move_to(_x + 4, _y + 4 + (i + 1) * DH + gout.cascent()) << text(_choices[i + _scroll_i]);
        }
    }
}

void Dropdown::unfocus() {
    _dropdown_open = false;
    _dropdown_pressed = false;
    set_height();
}
