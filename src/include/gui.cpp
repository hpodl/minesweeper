#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>

#include <memory>
#include <vector>
#include <iostream>

#include "gui.hh"

using PField = std::unique_ptr<Field>;

Field::Field(int x, int y, int w, int h, FieldPos pos, const char * L = 0) :
            Fl_Button(x, y, w, h, L),
            pos(pos) {}

int Field::handle(int event) {
    switch (event) {
        case FL_PUSH:
            std::cout << pos.x_ << ", " << pos.y_ << "\n";
            color(FL_CYAN);

            // Must be a child of MinefieldUI or this is undefined behavior
            MinefieldUI::static_callback(this, parent());
        break;

        default:
            return 0;
    }
    
            
        return 1;
}

std::unique_ptr<Field>& MinefieldUI::getField(int x, int y) {
    return fields_[y*w() + x];
}

void MinefieldUI::real_callback(Fl_Widget* w) {
    w->color(FL_BLACK);
    w->redraw();
}

void MinefieldUI::static_callback(Fl_Widget* w, void* data) {
    ((MinefieldUI*)data)->real_callback(w);
}

MinefieldUI::MinefieldUI(int x, int y, int w, int h) :
        Fl_Group(x,y,w,h) {}   


/**
 * @brief Renders an width by height board of fields
 * 
 * @param width horizontal fields
 * @param height vertical fields
*/
void MinefieldUI::render_minefield(int width, int height) {
    fields_.reserve(width*height);
    
    int sideLen = w()/width > h()/height ? h()/height : w()/width;

    
    begin();
    for (int xc = 0; xc < width; ++xc) 
        for(int yc = 0; yc < height; ++yc){
            std::unique_ptr<Field> button = std::make_unique<Field>(this->x() + xc*sideLen, this->y() + yc*sideLen, sideLen, sideLen, FieldPos{xc, yc});
            button->box(FL_UP_BOX);
            fields_.push_back(std::move(button));
        }
    end();

    redraw();
}

    // void redraw() {
    //     for (auto &field : fields) 
    //         field->redraw();
    // }




int main(int argc, char **argv) {
    Fl_Double_Window wind(640,480);
    
    MinefieldUI field(20, 10, 600, 460);
    field.render_minefield(15, 15);
    wind.show();

    return Fl::run();
}