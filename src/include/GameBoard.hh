#pragma once

#include <vector>
#include <memory>
#include "Field.hh"

using dimension_t = unsigned short;

class _FieldVector {
    dimension_t width_, height_;
    std::vector<Field> fields_;

    void _updateNeighbours(dimension_t x, dimension_t y);
    void _setFields();
public:
    _FieldVector(dimension_t width, dimension_t height);

    Field &getField(dimension_t x, dimension_t y);

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

