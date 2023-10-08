#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Window.H>

#include <iostream>
#include <memory>
#include <vector>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "MinefieldUI.hh"

using PField = std::unique_ptr<FieldButton>;

FieldButton::FieldButton(int x, int y, int w, int h, const char *L = 0)
    : Fl_Button(x, y, w, h, L) {}

void FieldButton::setRevealedStyle(const char *representation) {
    box(FL_FLAT_BOX);
    if (*representation == '0')
        label(" ");
    else
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
    : Fl_Group(x, y, w, h), board_(0, 0, 0) {
    gameLabel_ = new Fl_Box(0, 0, w, 25, "Welcome to Minesweeper");
    gameLabel_->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
}

void MinefieldUI::createMinefield(
    dimension_t width, dimension_t height, area_t mineCount) {
    fields_.reserve(width * height);
    board_.generate(width, height, mineCount);

    int sideLen =
        (w() / width) > (h() / height) ? (h() / height) : (w() / width);
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

    _updateMinesLeftLabel(mineCount);
    redraw();
}

int MinefieldUI::getSideLen() const { return buttonSize_ * board_.height(); }

void MinefieldUI::reveal(Point point) {
    std::vector<Point> revealed = board_.reveal(point);
    for (auto revealedPoint : revealed) {
        Field revealedField = board_.getField(revealedPoint);
        auto &revealedButton = _getButton(revealedPoint);

        if (revealedField.isMine()) {
            isLost_ = true;
            revealedButton->color(FL_RED);
        }

        const char newLabel[] = {revealedField.charRepresentation(), '\0'};
        revealedButton->setRevealedStyle(newLabel);
    }
}

int MinefieldUI::handle(int event) {
    switch (event) {
    case FL_PUSH:
        if (!isLost_ && !board_.isWon())
            _handleMouseClick();
        break;
    case FL_KEYUP:
        if (*Fl::event_text() == 'r' || *Fl::event_text() == 'R') {
            reset(board_.width(), board_.height(), board_.mineCount());
        } else if (*Fl::event_text() == 'q' || *Fl::event_text() == 'Q') {
            parent()->hide();
        }
        break;
    }

    return -1;
}

void MinefieldUI::reset(
    dimension_t newWidth, dimension_t newHeight, area_t mineCount) {
    fields_.clear();

    board_ = GameBoard(newWidth, newHeight, mineCount);
    createMinefield(newWidth, newHeight, mineCount);
    _updateMinesLeftLabel(mineCount);

    isLost_ = false;
}

void MinefieldUI::reset() {
    int width = board_.width();
    int height = board_.height();
    int mineCount = board_.mineCount();

    reset(width, height, mineCount);
}

void MinefieldUI::_handleMouseClick() {
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

    switch (mouseButton) {
    case (FL_LEFT_MOUSE):
        if (!clickedField.isMarked() && !clickedField.isRevealed()) {
            reveal(clickedPos);
        }
        break;

    case (FL_RIGHT_MOUSE):
        if (!clickedField.isRevealed()) {
            board_.toggleMark(clickedPos);
            _updateMinesLeftLabel(board_.mineCount() - board_.markCount());

            if (board_.getField(clickedPos).isMarked())
                clickedButton->setMarkedStyle();

            else
                clickedButton->setDefaultStyle();
        }
        break;

    case (FL_MIDDLE_MOUSE):
        if (clickedField.isMarked())
            break;
        for (auto revealedPoint : board_.chord(clickedPos)) {
            reveal(revealedPoint);
        }

        break;
    }

    // hacky
    if (board_.isWon() && !isLost_) {
        gameLabel_->copy_label("Win!");
    } else if (isLost_) {
        gameLabel_->copy_label("Lost!");
    }
    redraw(); // otherwise won't show if there's no other reason to redraw
}

void MinefieldUI::_updateMinesLeftLabel(const int minesLeft) {
    const auto lbl = fmt::format("Mines left: {}", minesLeft).c_str();
    gameLabel_->copy_label(lbl);
}