#include "MinefieldUI.hh"
#include "MainWindow.hh"

int main() {
    MainWindow wind(640, 640);
    wind.show();

    return Fl::run();
}