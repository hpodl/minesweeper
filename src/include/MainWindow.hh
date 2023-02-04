#include <FL/Fl_Double_Window.H>

class Fl_Menu_Bar;
class MinefieldUI;

class MainWindow : public Fl_Double_Window {
    Fl_Menu_Bar *menu_;
    MinefieldUI *minefield_;
    
  public:
    MainWindow(int width, int height);
    static void restart_callback();
};