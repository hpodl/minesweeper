#include "gui.hh"



int main() {
    Fl_Double_Window wind(640,480);
    
    MinefieldUI field(20, 10, 600, 460);
    field.create_minefield(15, 15, 30);
    wind.show();

    return Fl::run();
}