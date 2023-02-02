#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <memory>
#include <vector>

#include "gui.hh"

using PField = std::unique_ptr<FieldButton>;

FieldButton::FieldButton(int x, int y, int w, int h, const char *L = 0)
    : Fl_Button(x, y, w, h, L) {}

void FieldButton::setRevealedStyle(const char *representation) {
    box(FL_FLAT_BOX);
    copy_label(representation);
    labelcolor(FL_BLACK);
}

void FieldButton::setMarkedStyle() {
    label("@4search"); // kind of looks like a bomb
    labelcolor(FL_RED);
}

void FieldButton::setDefaultStyle() {
    color(FL_GRAY);
    label(" ");
}

std::unique_ptr<FieldButton> &MinefieldUI::_getButton(Point point) {
    return fields_[point.y * board_.width() + point.x];
}

MinefieldUI::MinefieldUI(int x, int y, int w, int h)
    : Fl_Group(x, y, w, h), board_(0, 0, 0) {}

void MinefieldUI::create_minefield(
    dimension_t width, dimension_t height, area_t mineCount) {
    fields_.reserve(width * height);
    board_.generate(width, height, mineCount);

    int sideLen = w() / width > h() / height ? h() / height : w() / width;
    buttonSize_ = sideLen;

    begin();
    for (dimension_t yc = 0; yc < height; ++yc)
        for (dimension_t xc = 0; xc < width; ++xc) {
            std::unique_ptr<FieldButton> button =
                std::make_unique<FieldButton>(this->x() + xc * sideLen,
                    this->y() + yc * sideLen, sideLen, sideLen);
            button->box(FL_UP_BOX);
            fields_.push_back(std::move(button));
        }
    end();

    redraw();
}

void MinefieldUI::reveal(Point point) {
    std::vector<Point> revealed = board_.reveal(point);
    for (auto revealedPoint : revealed) {
        Field revealedField = board_.getField(revealedPoint);
        auto &revealedButton = _getButton(revealedPoint);

        if (revealedField.isMine()) {
            revealedButton->color(FL_RED);
        }

        const char newLabel[] = {revealedField.charRepresentation(), '\0'};
        revealedButton->setRevealedStyle(newLabel);
    }
}

int MinefieldUI::handle(int event) {
    switch (event) {
    case FL_PUSH:
        _handle_mouse_click();
        break;

    case FL_KEYUP:
        if (*Fl::event_text() == 'r') {
            reset(board_.width(), board_.height(), board_.mineCount());
        }
        break;
    }

    return -1;
}

void MinefieldUI::reset(
    dimension_t newWidth, dimension_t newHeight, area_t mineCount) {
    board_ = GameBoard(newWidth, newHeight, mineCount);
    fields_.clear();
    create_minefield(newWidth, newHeight, mineCount);
}

void MinefieldUI::_handle_mouse_click() {
    int mouseButton = Fl::event_button();
    int clickedX = (Fl::event_x() - x()) / buttonSize_;
    int clickedY = (Fl::event_y() - y()) / buttonSize_;

    if (clickedX >= board_.width() || clickedY >= board_.height()) {
        return;
    }

    Point clickedPos = Point{
        static_cast<dimension_t>(clickedX), static_cast<dimension_t>(clickedY)};

    PField &clickedButton = _getButton(clickedPos);
    auto &clickedField = board_.getField(clickedPos);

    std::cout << Fl::event_x() - x() << ", " << Fl::event_y() - y() << "\n";
    std::cout << clickedX << ", " << clickedY << "\n";

    switch (mouseButton) {
    case (FL_LEFT_MOUSE):
        if (!clickedField.isMarked() && !clickedField.isRevealed()) {
            reveal(clickedPos);
        }
        break;

    case (FL_RIGHT_MOUSE):
        if (!clickedField.isRevealed()) {
            if (!clickedField.isMarked()) {
                clickedField.setMarked(true);
                clickedButton->setMarkedStyle();
            }

            else {
                clickedField.setMarked(false);
                clickedButton->setDefaultStyle();
            }
        }

        break;

    case (FL_MIDDLE_MOUSE):
        for (auto revealedPoint : board_.chord(clickedPos)) {
            reveal(revealedPoint);
        }

        break;
    }
}