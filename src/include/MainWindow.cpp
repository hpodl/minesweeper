#include <utility>

#include "MainWindow.hh"
#include "MinefieldUI.hh"

#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

MainWindow::MainWindow(int width, int height)
    : Fl_Double_Window(width, height, " Minesweeper") {
    const int menu_h = 25;
    const int minefield_padding = 10;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    // clang-format off
    Fl_Menu_Item menu_items[] = {
        {"File", 0, 0, 0, FL_SUBMENU},              // Submenu
            {"Restart", 0, (Fl_Callback *)restartCallback, this, FL_MENU_DIVIDER},    //
            {0},                                    // ends submenu

        {"Edit", 0, 0, 0, FL_SUBMENU},                // Submenu
            {"Difficulty", 0, 0, 0, FL_MENU_DIVIDER}, //
            {"Config", 0, 0, 0, FL_MENU_DIVIDER},     //
            {0},                                      // ends submenu
        {0}                                           // ends menu
    };
// clang-format on
#pragma GCC diagnostic pop

    menu_ = new Fl_Menu_Bar(0, 0, w(), menu_h);
    menu_->copy(menu_items);

    // short form for readability
    const int mp = minefield_padding;
    minefield_ = new MinefieldUI(0 + mp, 0 + mp + menu_h, w(), h() - mp);
    minefield_->createMinefield(20, 20, 50);

    // resizes the window to account for actual minefield size
    const int minefieldSize = minefield_->getSideLen();
    resize(0, 0, minefieldSize + 2 * mp, minefieldSize + menu_h + 2 * mp);
};

void MainWindow::restartCallback(Fl_Widget *, void *data) {
    ((MainWindow *)data)->minefield_->reset(20, 20, 50);
}

BoardConfigWindow::BoardConfigWindow(int width, int height)
    : Fl_Double_Window(240, 160, "Minefield Settings") {
    const int inputW(75), inputH(30);
    const int buttW(200), buttH(40);

    int nWidget = 0;
    auto input_x = []() { return 60; };
    auto input_y = [&nWidget]() { return 10 + inputH * (nWidget++); };

    // clang-format off
    Fl_Int_Input *widthInput_     = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Width: ");
    Fl_Int_Input *heightInput_    = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Height: ");
    Fl_Int_Input *mineCountInput_ = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Mines: ");
    // clang-format on

    Fl_Button *confirmButton_ =
        new Fl_Button(20, 10 + inputH * 3 + 10, buttW, buttH, "Confirm");

    widthInput_->value("20");
    heightInput_->value("20");
    mineCountInput_->value("50");
}