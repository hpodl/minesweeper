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

using PField = std::unique_ptr<FieldButton>;

FieldButton::FieldButton(int x, int y, int w, int h, Point pos, const char * L = 0) :
            Fl_Button(x, y, w, h, L),
            pos(pos) {}

int FieldButton::handle(int event) {
    switch (event) {
        case FL_PUSH:
            std::cout << pos.x << ", " << pos.y << "\n";

            // Must be a child of MinefieldUI or this is undefined behavior
            MinefieldUI::static_callback(this, parent());
        break;

        default:
            return 0;
    }
    
        return 1;
}

std::unique_ptr<FieldButton>& MinefieldUI::getField(Point point) {
    return fields_[point.y*board.width() + point.x];
}

void MinefieldUI::real_callback(FieldButton* w) {
    reveal(w->pos);
    redraw();

}

void MinefieldUI::static_callback(FieldButton* w, void* data) {
    ((MinefieldUI*)data)->real_callback(w);
}

MinefieldUI::MinefieldUI(int x, int y, int w, int h) :
        Fl_Group(x,y,w,h),
        board(0,0,0)
        {}

/**
 * @brief Renders an width by height board of fields
 * 
 * @param width horizontal fields
 * @param height vertical fields
*/
void MinefieldUI::create_minefield(dimension_t width, dimension_t height, area_t mineCount) {
    fields_.reserve(width*height);
    board.generate(width, height, mineCount);
    
    int sideLen = w()/width > h()/height ? h()/height : w()/width;

    
    begin();
    for(dimension_t yc = 0; yc < height; ++yc)
        for (dimension_t xc = 0; xc < width; ++xc) {
            std::unique_ptr<FieldButton> button = std::make_unique<FieldButton>(
                this->x() + xc*sideLen, this->y() + yc*sideLen, sideLen, sideLen, Point{xc, yc});
            button->box(FL_UP_BOX);
            fields_.push_back(std::move(button));
        }
    end();

    redraw();
}

void MinefieldUI::reveal(Point point) {
    std::cout << point.x << "," << point.y << "\n";
    Points revealed =  board.reveal(point);
    for(auto revealedPoint : revealed) {
        Field revealedField = board.getField(revealedPoint);
        auto &revealedUI = getField(revealedPoint);

        revealedUI->box(FL_FLAT_BOX);
        if(revealedField.isMine()) {
            revealedUI->color(FL_RED);
        }

        const char lab[] = {revealedField.charRepresentation(), '\0'};     
        revealedUI->copy_label(lab);

    }
    board.print();

}



int main(int argc, char **argv) {
    Fl_Double_Window wind(640,480);
    
    MinefieldUI field(20, 10, 600, 460);
    field.create_minefield(15, 15, 30);
    wind.show();

    return Fl::run();
}