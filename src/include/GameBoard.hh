#pragma once

#include <vector>
#include <memory>


class Field;

using dimension_t = unsigned short;
using FieldP = std::shared_ptr<Field>;

class _FieldVector {
    dimension_t width_, height_;
    std::vector<FieldP> fields_;
public:
    _FieldVector(dimension_t width, dimension_t height);

    FieldP getField(dimension_t x, dimension_t y);

    // Type is "unsigned int" as multiplication of 2 unsigned shorts can give an unsigned int
    unsigned int size();

    // Populates 
    void populate(unsigned int mineCount);

    void print();
};


class GameBoard {
    _FieldVector board_;

public:
    GameBoard(dimension_t width, dimension_t height) : board_(_FieldVector(width, height)){}

    unsigned int size() { return board_.size(); }

    void populate(unsigned int mineCount) {
        board_.populate(mineCount);
    }

    void reveal(dimension_t width, dimension_t height);
};

