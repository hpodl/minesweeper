#include <algorithm>
#include <exception>
#include <iostream>
#include <random>
#include <chrono>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "Field.hh"
#include "GameBoard.hh"

_FieldVector::_FieldVector(dimension_t x, dimension_t y, area_t mineCount) : width_(x), height_(y), mineCount_(mineCount), fields_(x * y, Field()) { this->populate(mineCount);};

Field &_FieldVector::getField(Point point) {
    if (point.x >= width_ )
        throw std::out_of_range(
            fmt::format("Maximum width is {}, got {}.", width_, point.x));
    
    else if (point.y >= height_) 
        throw std::out_of_range(
            fmt::format("Maximum width is {}, got {}.", width_, point.x));

    return fields_[point.y * width_ + point.x];
};

area_t _FieldVector::size() { return width_ * height_; }

void _FieldVector::populate(area_t mineCount) {
    static int seed = 4;//std::chrono::system_clock::now().time_since_epoch().count();
    if (mineCount > size())
        throw std::out_of_range(
            fmt::format("Maximum mine count is {}, got {}.", size(), mineCount));

    std::for_each(fields_.begin(), (fields_.begin() + mineCount), [](auto &field)
            { field.setMine(); });

    std::shuffle(fields_.begin(), fields_.end(), std::default_random_engine(seed));
    calculateFields();
}

void _FieldVector::print() {
    for (area_t i = 0; i < fields_.size(); ++i) {
        if (!(i % width_))
            std::cout << "\n";

        std::cout << fields_[i].charRepresentation() << " ";

    }
    std::cout << '\n';
}


std::vector<Point> _FieldVector::neighbourCoords(Point point) {
    // signed so it can be negative, int so it can store (max unsigned short) + 1
    std::vector<int> neighb_x{point.x - 1, point.x, point.x + 1};
    std::vector<int> neighb_y{point.y - 1, point.y, point.y + 1};

    std::vector<Point> neighbours;
    for (auto y : neighb_y) {
        if (y < 0 || y >= height_)
            continue;

        for (auto x : neighb_x) {
            if (x < 0 || x >= width_)
                continue;
            // this cast is safe, since we made sure the number is positive and within dimension_t bounds
            neighbours.push_back(Point{static_cast<dimension_t>(x), static_cast<dimension_t>(y)});
        }
    }

    return neighbours;
}


void _FieldVector::_updateNeighbours(Point point) {
    if (!getField(point).isMine()) {
        return;
    }

    auto neighbours = neighbourCoords(point);
    std::for_each(neighbours.begin(), neighbours.end(), [this](auto point) {
        this->getField(point).incrementMineCount();
    });
}

void _FieldVector::calculateFields() {
    for (dimension_t y = 0; y < height_; ++y) {
        for (dimension_t x = 0; x < width_; ++x) {
            _updateNeighbours(Point{x, y});
        }
    }
}

std::optional<Points> GameBoard::reveal(Point point) {
    Field& field = board_.getField(point);
    
    Points revealed;
    field.reveal();
    
    if(field.isMine())
        return std::nullopt;

    if(field.getMineCount() == 0) {
        revealed = _reveal_empty(point);
    }

    revealed.push_back(point);
    return revealed;
}

Points GameBoard::_reveal_empty(Point point) {
    board_.getField(point).reveal();
    
    Points neighbours = board_.neighbourCoords(point);
    Points revealed;

    for(Point neighbourCoords : neighbours) {
        Field& field = board_.getField(neighbourCoords);
        if(!field.isRevealed()) {
            revealed.push_back(neighbourCoords);
            field.reveal();
            
            if(field.getMineCount() == 0) {
                Points thisIteration = _reveal_empty(neighbourCoords);
                revealed.insert(revealed.end(), thisIteration.begin(), thisIteration.end());
            }            
        }
    }   
    return revealed;
}