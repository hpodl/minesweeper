#include <functional>
#include <utility>

#include "MainWindow.hh"
#include "MinefieldUI.hh"

#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

MainWindow::MainWindow(int width, int height)
    : Fl_Double_Window(width, height, " Minesweeper"), configWindow_(nullptr) {
    const int menu_h = 25;
    const int minefield_padding = 10;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
    // clang-format off
    Fl_Menu_Item menu_items[] = {
        {"File", 0, 0, 0, FL_SUBMENU}, // Submenu
            {"Restart", 0, (Fl_Callback *)restartCallback, this, 0},
            {"Quit", 0, (Fl_Callback *)quitCallback, this, 0},
        {0}, // ends submenu
        
        {"Edit", 0, 0, 0, FL_SUBMENU}, // Submenu
            {"Config", 0, (Fl_Callback *)&configCallback, this, FL_MENU_DIVIDER},
            {"Difficulty", 0, 0, 0, FL_SUBMENU}, // Sub-submenu
                {"Beginner", 0,
                    [](Fl_Widget *, void *p) {
                        auto *mainWindow = static_cast<MainWindow *>(p);
                        mainWindow->resetBoard(8, 8, 10);
                    },
                    this, FL_MENU_DIVIDER},
                {"Intermediate", 0,
                    [](Fl_Widget *, void *p) {
                        auto *mainWindow = static_cast<MainWindow *>(p);
                        mainWindow->resetBoard(16, 16, 40);
                    },
                    this, FL_MENU_DIVIDER},
                {"Expert", 0,
                    [](Fl_Widget *, void *p) {
                        auto *mainWindow = static_cast<MainWindow *>(p);
                        mainWindow->resetBoard(30, 16, 99);
                    },
                    this, FL_MENU_DIVIDER},
                {"Custom", 0, configCallback, this, 0},
            {0}, // ends sub-submenu
        {0}, // ends submenu

        {"View", 0, 0, 0, FL_SUBMENU}, // Submenu
            {"Remove border", 0, (Fl_Callback *)borderCallback, this, 0},
        {0}, // ends submenu
    {0}  // ends menu
    };
    // clang-format on
#pragma GCC diagnostic pop

    menu_ = new Fl_Menu_Bar(0, 0, w(), menu_h);
    menu_->copy(menu_items);

    // short form for readability
    const int mp = minefield_padding;
    minefield_ = new MinefieldUI(0 + mp, 0 + mp + menu_h, w() - 2*mp, h() - 2*mp);
    minefield_->createMinefield(20, 20, 50);

    // resizes the window to account for actual minefield size
    const int minefieldSize = minefield_->getSideLen();
    resize(0, 0, minefieldSize + 2 * mp, minefieldSize + menu_h + 2 * mp);
};

void MainWindow::quitCallback(Fl_Widget *, void *data) {
    auto window = static_cast<MainWindow *>(data);
    window->hide();
}

void MainWindow::restartCallback(Fl_Widget *, void *data) {
    auto window = static_cast<MainWindow *>(data);
    window->resetBoard();
}

void MainWindow::resetBoard(int width, int height, int mineCount) {
    minefield_->reset(width, height, mineCount);
}

void MainWindow::resetBoard() { minefield_->reset(); }

void MainWindow::borderCallback(Fl_Widget *, void *data) {
    static_cast<MainWindow *>(data)->border(0);
}

BoardConfigWindow::BoardConfigWindow(int x, int y, MainWindow *parent)
    : Fl_Double_Window(x, y, 240, 160, "Minefield Settings"),
      parentWindow_(parent) {
    const int inputW(75), inputH(30);
    const int buttW(90), buttH(40);

    int nWidget = 0;
    auto input_x = []() { return 60; };
    auto input_y = [&nWidget]() { return 10 + inputH * (nWidget++); };

    // clang-format off
    widthInput_     = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Width: ");
    heightInput_    = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Height: ");
    mineCountInput_ = new Fl_Int_Input(input_x(), input_y(), inputW, inputH, "Mines: ");
    // clang-format on

    Fl_Button *confirmButton_ =
        new Fl_Button(20, 10 + inputH * 3 + 10, buttW, buttH, "Confirm");

    Fl_Button *cancelButton_ = new Fl_Button(
        20 + buttW + 20, 10 + inputH * 3 + 10, buttW, buttH, "Cancel");

    widthInput_->value("20");
    heightInput_->value("20");
    mineCountInput_->value("50");

    confirmButton_->callback(
        [](Fl_Widget *, void *p) {
            auto *configWindow = static_cast<BoardConfigWindow *>(p);
            int width = std::stoi(configWindow->widthInput_->value());
            int height = std::stoi(configWindow->heightInput_->value());
            int mineCount = std::stoi(configWindow->mineCountInput_->value());
            configWindow->parentWindow_->resetBoard(width, height, mineCount);
            configWindow->hide();
        },
        this);

    cancelButton_->callback(
        [](Fl_Widget *, void *p) {
            auto *configWindow = static_cast<BoardConfigWindow *>(p);
            configWindow->hide();
        },
        this);
}

void MainWindow::configCallback(Fl_Widget *, void *data) {
    MainWindow *self = static_cast<MainWindow *>(data);
    if (self->configWindow_ == nullptr)
        self->configWindow_ =
            new BoardConfigWindow(self->x() + 10, self->y() + 10, self);
    self->configWindow_->show();
    self->focus(self->configWindow_);
}
