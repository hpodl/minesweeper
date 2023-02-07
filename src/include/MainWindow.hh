#include <FL/Fl_Double_Window.H>

class Fl_Menu_Bar;
class MinefieldUI;
class Fl_Int_Input;
class Fl_Button;

class MainWindow : public Fl_Double_Window {
    Fl_Menu_Bar *menu_;
    MinefieldUI *minefield_;

  public:
    MainWindow(int width, int height);
    static void restartCallback(Fl_Widget*, void *data);
};

class BoardConfigWindow : public Fl_Double_Window {
  Fl_Int_Input* widthInput_;
  Fl_Int_Input* heightInput_;
  Fl_Int_Input* mineCountInput_;
  Fl_Button* confirmButton_;
  public:
    BoardConfigWindow(int width, int height);
};