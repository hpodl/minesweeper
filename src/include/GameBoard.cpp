#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <random>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "Field.hh"
#include "GameBoard.hh"

_FieldMatrix::_FieldMatrix(dimension_t x, dimension_t y, area_t mineCount)
    : width_(x), height_(y), mineCount_(mineCount), fields_(x * y, Field()) {
    this->populate(mineCount);
};

Field &_FieldMatrix::getField(Point point) {
    if (point.x >= width_)
        throw std::out_of_range(
            fmt::format("Maximum width is {}, got {}.", width_, point.x));

    else if (point.y >= height_)
        throw std::out_of_range(
            fmt::format("Maximum width is {}, got {}.", width_, point.x));

    return fields_[point.y * width_ + point.x];
};

area_t _FieldMatrix::size() const { return width_ * height_; }

void _FieldMatrix::populate(area_t mineCount) {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();

    if (mineCount > size())
        throw std::out_of_range(fmt::format(
            "Maximum mine count is {}, got {}.", size(), mineCount));

    std::for_each(fields_.begin(), (fields_.begin() + mineCount),
        [](auto &field) { field.setMine(); });

    std::shuffle(
        fields_.begin(), fields_.end(), std::default_random_engine(seed));
    recalculateNeighbours();
}

void _FieldMatrix::print() const {
    for (area_t i = 0; i < fields_.size(); ++i) {
        if (!(i % width_))
            std::cout << "\n";

        std::cout << fields_[i].charRepresentation() << " ";
    }
    std::cout << '\n';
}

std::vector<Point> _FieldMatrix::neighbourCoords(Point point) {
    // signed so it can be negative, int so it can store (max unsigned short)+1
    std::vector<int> neighb_x{point.x - 1, point.x, point.x + 1};
    std::vector<int> neighb_y{point.y - 1, point.y, point.y + 1};

    std::vector<Point> neighbours;
    for (auto y : neighb_y) {
        if (y < 0 || y >= height_)
            continue;

        for (auto x : neighb_x) {
            if (x < 0 || x >= width_)
                continue;
            // this cast is safe, since we made sure the number is positive and
            // within dimension_t bounds
            neighbours.push_back(Point{
                static_cast<dimension_t>(x), static_cast<dimension_t>(y)});
        }
    }

    return neighbours;
}

void _FieldMatrix::_updateNeighbours(Point point) {
    if (!getField(point).isMine()) {
        return;
    }

    auto neighbours = neighbourCoords(point);
    std::for_each(neighbours.begin(), neighbours.end(),
        [this](auto point) { this->getField(point).incrementMineCount(); });
}

void _FieldMatrix::recalculateNeighbours() {
    for (dimension_t y = 0; y < height_; ++y)
        for (dimension_t x = 0; x < width_; ++x)
            _updateNeighbours(Point{x, y});
}

GameBoard::GameBoard(dimension_t width, dimension_t height, area_t mineCount)
    : board_(width, height, mineCount) {}
GameBoard::GameBoard(_FieldMatrix board) : board_(board) {}
GameBoard::GameBoard() : board_(0, 0, 0){};

std::vector<Point> GameBoard::reveal(Point point) {
    Field &field = board_.getField(point);

    std::vector<Point> revealed;
    revealedCount_ += field.reveal();

    if (field.getMineCount() == 0) {
        revealed = _revealEmpty(point);
    }

    revealed.push_back(point);
    return revealed;
}

std::vector<Point> GameBoard::_revealEmpty(Point point) {
    std::vector<Point> revealed;
    revealed.push_back(point);
    auto field = board_.getField(point);
    revealedCount_ += field.reveal();

    if (field.isMine()) {
        mineHit_ = true;
        return revealed;
    }
    std::vector<Point> neighbours = board_.neighbourCoords(point);

    for (Point neighbourCoords : neighbours) {
        Field &field = board_.getField(neighbourCoords);
        if (!field.isRevealed() & !field.isMarked()) {
            revealed.push_back(neighbourCoords);
            revealedCount_ += field.reveal();
            if (field.isMine()) {
                mineHit_ = true;
            }

            if (field.getMineCount() == 0 && !field.isMarked()) {
                std::vector<Point> thisIteration =
                    _revealEmpty(neighbourCoords);
                revealed.insert(
                    revealed.end(), thisIteration.begin(), thisIteration.end());
            }
        }
    }
    return revealed;
}

std::vector<Point> GameBoard::chord(Point point) {
    short minesAround = getField(point).getMineCount();
    auto neighb_coords = board_.neighbourCoords(point);

    short marksAround = std::accumulate(neighb_coords.begin(),
        neighb_coords.end(), 0, [this](short sum, Point point) {
            return sum + this->getField(point).isMarked();
        });

    std::vector<Point> revealed;
    if (marksAround >= minesAround) {
        for (Point neighbourCoord : board_.neighbourCoords(point)) {
            auto &field = getField(neighbourCoord);
            if (!field.isMarked()) {
                revealedCount_ += field.reveal();
                revealed.push_back(neighbourCoord);
            }
        }
    }
    return revealed;
}

void GameBoard::generate(
    dimension_t width, dimension_t height, area_t mineCount) {
    board_ = _FieldMatrix(width, height, mineCount);
}

void GameBoard::toggleMark(Point coordinates) {
    auto &field = getField(coordinates);
    field.setMarked(!field.isMarked());

    field.isMarked() ? ++markCount_ : --markCount_;
};

bool GameBoard::isWon() const {
    return revealedCount_ + markCount_ == size() && !mineHit_;
}
bool GameBoard::isLost() const { return mineHit_; }
dimension_t GameBoard::width() const { return board_.shape().x; };
dimension_t GameBoard::height() const { return board_.shape().y; };
area_t GameBoard::mineCount() const { return board_.mineCount(); };
area_t GameBoard::markCount() const { return markCount_; };
area_t GameBoard::size() const { return board_.size(); }
void GameBoard::print() const { board_.print(); };
Field &GameBoard::getField(Point point) { return board_.getField(point); }