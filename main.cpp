#include "graphics.hpp"
#include "window.hpp"
#include "widgets.hpp"
#include "checkbox.hpp"
#include "inputtextbox.hpp"
#include "button.hpp"
#include "numberinput.hpp"
#include "dropdown.hpp"
#include "box.hpp"

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace genv;


static const int window_width = 800;
static const int window_height = 600;

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
    Box *box1;
    vector<Button*> btn_list;

    TextBox *t_save_description;
    InputTextBox *t_filename;
    Button *b_save;

    void save_states(string fname) {
        cout << "Saving widgets states to " << fname << endl;
        ofstream f(fname);
        f << "c1:" << c1->is_checked() << endl;
        f << "c2:" << c2->is_checked() << endl;
        f << "t2:" << t2->get_text() << endl;
        f << "t3:" << t3->get_text() << endl;
        f << "n1:" << n1->value() << endl;
        f << "n2:" << n2->value() << endl;
        f << "d1:" << d1->value() << endl;
        f << "d2:" << d2->value() << endl;
        f.close();
    }

public:
    MainWindow() : Window(window_width, window_height) {
        box1 = new Box(this, 236, 12, 400, 400);
        c1 = new CheckBox(this, 10, 10, 24, 24);
        c2 = new CheckBox(this, 10, 50, 48, 48);
        t1 = new TextBox(this, 60, 20, 180, "hello textbox");
        t2 = new InputTextBox(this, 180, 20, 180, "hello world!");
        t3 = new InputTextBox(this, 180, 80, 240);
        b1 = new Button(this, 60, 120, 120, 60, "big button", [this]() {
                if(btn_list.size() <= 0) return;
                Button* b = btn_list[btn_list.size() - 1];
                btn_list.pop_back();
                delete b;
        });
        b2 = new Button(this, 240, 120, 150, 24, "small button", [this](){
                btn_list.push_back(new Button(this, 240, 120 + (24 * (btn_list.size() + 1)), 150, 24, to_string(btn_list.size())));
        });
        n1 = new NumberInput(this, 20, 200, 80, 40, 0);
        n2 = new NumberInput(this, 150, 200, 64, 28, 50, 0, 100);
        d2 = new Dropdown(box1, 400, 52, 240, 24, 3, {"no default here", "hello asd", "world 234", "abc"});
        d1 = new Dropdown(box1, 400, 24, 240, 24, 2, {"hello", "im a default value", "world", "abc"}, 1);

        // Saving section
        const int filename_w = 120;
        const int h = gout.cascent() + gout.cdescent() + 15;
        const string save_description = "Filename to save widget states:";
        t_save_description = new TextBox(this, window_width - gout.twidth(save_description) - 15, window_height - h * 3, gout.twidth(save_description), save_description);
        t_filename = new InputTextBox(this, window_width - filename_w - 15, window_height - h * 2, filename_w, "data.txt");
        b_save = new Button(this, window_width - 56 - 15, window_height - h, 56, 24, "Save");
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
            } else if(b_save->is_selected(ev)) {
                save_states(t_filename->get_text());
            }
        }
    }
};

int main()
{
    MainWindow w;
    return w.event_loop();
}
