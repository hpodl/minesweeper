#include "MinefieldUI.hh"
#include "MainWindow.hh"


// int main() {
//     Fl_Double_Window wind(640,480);
    
//     MinefieldUI field(20, 20, 600, 460);
//     field.create_minefield(15, 15, 30);
    
    
//     // Size ranging from field size
//     wind.size_range(field.w(), field.h(), 0, 0);
//     wind.show();

//     return Fl::run();
// }

int main() {
    MainWindow wind(640, 640);
    wind.show();

    return Fl::run();
}