#include <algorithm>
#include <exception>
#include <iostream>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "Field.hh"
#include "GameBoard.hh"


_FieldVector::_FieldVector(dimension_t width, dimension_t height) : width_(width), height_(height), fields_(width*height, std::make_shared<FieldEmpty>()){};

FieldP  _FieldVector::getField(dimension_t x, dimension_t y) {
    if(x > width_) throw std::out_of_range(
        fmt::format("Maximum width is {}, got {}.", width_, x));

    return fields_[y % height_ + x];
};

unsigned int  _FieldVector::size() { return width_ * height_; }

void  _FieldVector::populate(unsigned int mineCount) {
    if(mineCount > size()) throw std::out_of_range(
        fmt::format("Maximum mine count is {}, got {}.", size(), mineCount));

    for(auto it = fields_.begin(); it != fields_.begin()+mineCount; ++it){
        *it = std::make_shared<FieldMine>();
    }


    std::random_shuffle(fields_.begin(), fields_.end());
}

void  _FieldVector::print() {
    for(unsigned int i = 0; i < fields_.size(); ++i) {
        if ((i%width_) || !i)
            std::cout << fields_[i]->charRepresentation();

        else
            std::cout << "\n";
    }
}
