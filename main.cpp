#include "graphics.hpp"

using namespace genv;

#define X 800
#define Y 800

void clear() {
    gout << color(0, 0, 0)
         << move_to(0, 0)
         << box(X, Y);
}

int main() {
    gout.open(X, Y);

    event ev;
    gin >> ev;
    while(gin >> ev) {
        if(ev.type == ev_key && ev.keycode == key_escape)
            return 0;
        else if(ev.type == ev_timer) {
        }

        clear();

        

        gout << refresh;
    }
    return 0;
}
