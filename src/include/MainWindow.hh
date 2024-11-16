#pragma once
#include <FL/Fl_Double_Window.H>

class MinefieldUI;
class BoardConfigWindow;

class Fl_Menu_Bar;
class Fl_Int_Input;
class Fl_Button;

class MainWindow : public Fl_Double_Window {
    Fl_Menu_Bar *menu_;
    MinefieldUI *minefield_;
    BoardConfigWindow *configWindow_;

  public:
    MainWindow(int width, int height);
    static void quitCallback(Fl_Widget *, void *data);
    static void restartCallback(Fl_Widget *, void *data);
    static void configCallback(Fl_Widget *, void *data);
    static void borderCallback(Fl_Widget *, void *data);
    void resetBoard(int width, int height, int mineCount);
    void resetBoard();
};

class BoardConfigWindow : public Fl_Double_Window {
    Fl_Int_Input *widthInput_;
    Fl_Int_Input *heightInput_;
    Fl_Int_Input *mineCountInput_;

    Fl_Button *confirmButton_;
    Fl_Button *cancelButton_;

    MainWindow *parentWindow_;

  public:
    BoardConfigWindow(int width, int height, MainWindow *parent);
};