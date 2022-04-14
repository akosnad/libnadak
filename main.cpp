#include "graphics.hpp"
#include "window.hpp"
#include "widgets.hpp"
#include "checkbox.hpp"
#include "inputtextbox.hpp"
#include "button.hpp"
#include "numberinput.hpp"
#include "dropdown.hpp"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace genv;


class MainWindow : public Window {
protected:
    CheckBox *c1;
    CheckBox *c2;
    TextBox *t1;
    InputTextBox *t2;
    InputTextBox *t3;
    Button *b1;
    Button *b2;
    NumberInput *n1;
    NumberInput *n2;
    Dropdown *d1;
    Dropdown *d2;

public:
    MainWindow() : Window(800, 600) {
        c1 = new CheckBox(this, 10, 10, 24, 24);
        c2 = new CheckBox(this, 10, 50, 48, 48);
        t1 = new TextBox(this, 60, 20, 180, "hello textbox");
        t2 = new InputTextBox(this, 180, 20, 180, "hello world!");
        t3 = new InputTextBox(this, 180, 80, 240);
        b1 = new Button(this, 60, 120, 120, 60, "big button");
        b2 = new Button(this, 240, 120, 150, 24, "small button");
        n1 = new NumberInput(this, 20, 200, 80, 40, 0);
        n2 = new NumberInput(this, 150, 200, 64, 24, 50, 0, 100);
        d2 = new Dropdown(this, 400, 52, 240, 24, {"no default here", "hello asd", "world 234", "abc"});
        d1 = new Dropdown(this, 400, 24, 240, 24, {"hello", "im a default value", "world", "abc"}, 1);
    }

    virtual void event_handler(event ev) {
        if(ev.type == ev_key && ev.keycode == key_escape) {
            //exit(0);
        }
        if(ev.type == ev_mouse && ev.button == -btn_left) {
            if(b1->is_selected(ev)) {
                cout << "big" << endl;
            } else if(b2->is_selected(ev)) {
                cout << "small" << endl;
            } else if(c1->is_selected(ev)) {
                cout << "checkbox 1: " << c1->is_checked() << endl;
            } else if(d1->is_selected(ev)) {
                cout << "dropdown: " << d1->value() << endl;
            }
        }
    }
};

int main()
{
    MainWindow w;
    return w.event_loop();
}
