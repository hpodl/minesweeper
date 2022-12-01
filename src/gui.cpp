#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

#include <memory>
#include <vector>
#include <iostream>

struct FieldPos {
    int x,y;
};

class Field : public Fl_Button {
    public:
        FieldPos pos;
        Field(int x, int y, int w, int h, FieldPos pos, const char * L = 0) :
            Fl_Button(x, y, w, h, L),
            pos(pos) {}

};

using PField = std::unique_ptr<Field>;

class MinefieldUI : public Fl_Group {
    Fl_Box someBox;
    std::vector<PField> fields;

    PField& getField(int x, int y) {
        return fields[y*w() + x];
    }

public:
    MinefieldUI(int x, int y, int w, int h) :
        Fl_Group(x,y,w,h),
        someBox(20,40,260,100,"Hello, W!")
    {   
        box(FL_UP_BOX);
        someBox.box(FL_UP_BOX);
        someBox.labelsize(36);
        someBox.labelfont(FL_BOLD+FL_ITALIC);
        someBox.labeltype(FL_SHADOW_LABEL);
        end();
    }



    /**
     * @brief Renders an width by height board of fields
     * 
     * @param width horizontal fields
     * @param height vertical fields
     */
    void render_minefield(int width, int height) {
        fields.reserve(width*height);
        
        int sideLen = w()/width > h()/height ? h()/height : w()/width;

        
        begin();
        for (int xc = 0; xc < width; ++xc) 
            for(int yc = 0; yc < height; ++yc){
                PField button = std::make_unique<Field>(this->x() + xc*sideLen, this->y() + yc*sideLen, sideLen, sideLen, FieldPos{xc, yc});
                button->box(FL_UP_BOX);
                fields.push_back(std::move(button));
            }
        end();

        redraw();
    }

    void redraw() {
        for (auto &field : fields) 
            field->redraw();
    }


};




int main(int argc, char **argv) {
    Fl_Double_Window wind(640,480);
    
    MinefieldUI field(20, 10, 600, 460);
    field.render_minefield(15, 15);
    wind.show();

    return Fl::run();
}