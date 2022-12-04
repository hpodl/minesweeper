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



void FieldButton::onRevealStyle(const char* representation) {
    copy_label(representation);
    labelcolor(FL_BLACK);
}

void FieldButton::onMarkStyle() {
    label("@4search");
    labelcolor(FL_RED);
}

void FieldButton::defaultStyle() {
    color(FL_GRAY);
    label(" ");
}



std::unique_ptr<FieldButton>& MinefieldUI::_getButton(Point point) {
    return _fields[point.y*_board.width() + point.x];
}

MinefieldUI::MinefieldUI(int x, int y, int w, int h) :
        Fl_Group(x,y,w,h),
        _board(0,0,0)
        {}

/**
 * @brief Renders an width by height board of fields
 * 
 * @param width horizontal fields
 * @param height vertical fields
*/
void MinefieldUI::create_minefield(dimension_t width, dimension_t height, area_t mineCount) {
    _fields.reserve(width*height);
    _board.generate(width, height, mineCount);
    
    int sideLen = w()/width > h()/height ? h()/height : w()/width;
    _buttonSize = sideLen;

    
    begin();
    for(dimension_t yc = 0; yc < height; ++yc)
        for (dimension_t xc = 0; xc < width; ++xc) {
            std::unique_ptr<FieldButton> button = std::make_unique<FieldButton>(
                this->x() + xc*sideLen, this->y() + yc*sideLen, sideLen, sideLen, Point{xc, yc});
            button->box(FL_UP_BOX);
            _fields.push_back(std::move(button));
        }
    end();

    redraw();
}

void MinefieldUI::reveal(Point point) {
    Points revealed =  _board.reveal(point);
    for(auto revealedPoint : revealed) {
        Field revealedField = _board.getField(revealedPoint);
        auto &revealedButton = _getButton(revealedPoint);

        revealedButton->box(FL_FLAT_BOX);
        if(revealedField.isMine()) {
            revealedButton->color(FL_RED);
        }

        const char newLabel[] = { revealedField.charRepresentation(), '\0' };
        revealedButton->onRevealStyle(newLabel);     

    }
}


int MinefieldUI::handle(int event) {
    switch(event) {
        case FL_PUSH:
            _handle_mouse_click();
        break;

        case FL_KEYUP:
            if(*Fl::event_text() == 'r') {
                reset(_board.width(), _board.height(), _board.mineCount());
            }
        break;

    }

    return -1;
}

void MinefieldUI::reset(dimension_t newWidth, dimension_t newHeight, area_t mineCount) {
    _board = GameBoard(newWidth, newHeight, mineCount);
    _fields.clear();  
    create_minefield(newWidth, newHeight, mineCount);      
}


void MinefieldUI::_handle_mouse_click() {
    int mouseButton = Fl::event_button();
    int clickedX = (Fl::event_x() - x())/_buttonSize;
    int clickedY = (Fl::event_y() - y())/_buttonSize;

    if(clickedX >= _board.width() || clickedY >= _board.height() ) {
        return;
    }

    Point clickedPos = Point{static_cast<dimension_t>(clickedX), static_cast<dimension_t>(clickedY)};

    PField &clickedButton = _getButton(clickedPos);
    auto &clickedField = _board.getField(clickedPos);

    std::cout << Fl::event_x() - x() << ", " << Fl::event_y() - y() << "\n";
    std::cout << clickedX << ", " << clickedY << "\n";

    switch(mouseButton) {
        case(FL_LEFT_MOUSE):
            if(!clickedField.isMarked() && !clickedField.isRevealed()) {
                reveal(clickedPos);
            }
        break;
       
        case(FL_RIGHT_MOUSE):
            if(!clickedField.isRevealed()) {
                if (!clickedField.isMarked()){
                    clickedField.mark(true);
                    clickedButton->onMarkStyle();
                }
        
                else {
                    clickedField.mark(false);
                    clickedButton->defaultStyle();
                }
            }

        break;

        case(FL_MIDDLE_MOUSE):
            for(auto revealedPoint : _board.chord(clickedPos)) {
                reveal(revealedPoint);
            }

        break;
    }

}