#include <algorithm>
#include <exception>
#include <iostream>
#include <random>
#include <chrono>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "Field.hh"
#include "GameBoard.hh"

_FieldVector::_FieldVector(dimension_t width, dimension_t height) : width_(width), height_(height), fields_(width * height, Field()) {};

Field &_FieldVector::getField(dimension_t x, dimension_t y) {
    if (x >= width_ )
        throw std::out_of_range(
            fmt::format("Maximum width is {}, got {}.", width_, x));

    return fields_[y * width_ + x];
};

unsigned int _FieldVector::size() { return width_ * height_; }

void _FieldVector::populate(unsigned int mineCount) {
    static int seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (mineCount > size())
        throw std::out_of_range(
            fmt::format("Maximum mine count is {}, got {}.", size(), mineCount));

    std::for_each(fields_.begin(), (fields_.begin() + mineCount), [](auto &field)
            { field.setMine(); });

    std::shuffle(fields_.begin(), fields_.end(), std::default_random_engine(seed));
    _setFields();
}

void _FieldVector::print() {
    for (unsigned int i = 0; i < fields_.size(); ++i) {
        if (!(i % width_))
            std::cout << "\n";

        std::cout << fields_[i].charRepresentation() << " ";

    }
}

void _FieldVector::_updateNeighbours(dimension_t x, dimension_t y) {
    std::vector<long> neighb_x{x - 1, x, x + 1};
    std::vector<long> neighb_y{y - 1, y, y + 1};

    if (!getField(x, y).isMine())
    {
        return;
    }

    for (auto y : neighb_y)
    {
        if (y < 0 || y >= height_)
            continue;

        for (auto x : neighb_x) {
            if (x < 0 || x >= width_)
                continue;
            getField(x, y).incrementMineCount();
        }
    }
}

void _FieldVector::_setFields() {
    for (dimension_t y = 0; y < height_; ++y) {
        for (dimension_t x = 0; x < width_; ++x) {
            _updateNeighbours(x, y);
        }
    }
}
