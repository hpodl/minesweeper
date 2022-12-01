#include <FL/Fl.H>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

struct FieldPos {
    int x,y;
};


class MinefieldUI : Fl_Group {
    // Fl_Button button;
    Fl_Box box;

public:
    MinefieldUI(int x, int y, int w, int h) :
        Fl_Group(x,y,w,h),
        box(20,40,260,100,"Hello, W!")
    {        
        box.box(FL_UP_BOX);
        box.labelsize(36);
        box.labelfont(FL_BOLD+FL_ITALIC);
        box.labeltype(FL_SHADOW_LABEL);
        end();
    }
};

class Field : Fl_Button {
    FieldPos pos;
    Field(int x, int y, int w, int h, FieldPos pos, const char * L = 0) :
        Fl_Button(x, y, w, h, L),
        pos(pos)
    {}

}



int main(int argc, char **argv) {
    Fl_Double_Window wind(640,480);
    wind.begin();

    MinefieldUI field(640,480, 0, 0);
    
    wind.end();
    wind.show();

    return Fl::run();
}