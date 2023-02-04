#include "MainWindow.hh"
#include "MinefieldUI.hh"

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

MainWindow::MainWindow(int width, int height)
    : Fl_Double_Window(width, height, " Minesweeper") {
    const int menu_h = 25;
    const int minefield_padding = 10;

    // clang-format off
    Fl_Menu_Item menu_items[] = {
        {"File", 0, 0, 0, FL_SUBMENU},              // Submenu
            {"Start", 0, 0, 0, FL_MENU_DIVIDER},    //
            {0},                                    // ends submenu

        {"Edit", 0, 0, 0, FL_SUBMENU},                // Submenu
            {"Difficulty", 0, 0, 0, FL_MENU_DIVIDER}, //
            {"Config", 0, 0, 0, FL_MENU_DIVIDER},     //
            {0},                                      // ends submenu
        {0}                                           // ends menu
    };
    // clang-format on

    menu_ = new Fl_Menu_Bar(0, 0, w(), menu_h);
    menu_->copy(menu_items);

    // short form for readability
    const int mp = minefield_padding;
    minefield_ = new MinefieldUI(0 + mp, 0 + mp + menu_h, w(), h() - mp);
    minefield_->create_minefield(20, 20, 50);

    // resizes the window to account for actual minefield size
    const int minefieldSize = minefield_->getSideLen();
    resize(0, 0, minefieldSize + 2 * mp, minefieldSize + menu_h + 2 * mp);
};