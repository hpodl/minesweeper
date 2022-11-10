#pragma once

#include <vector>
#include "Field.hh"

using dimension_t = unsigned short;

struct Point {
    dimension_t x;
    dimension_t y;
};

class _FieldVector {
    dimension_t width_, height_;
    std::vector<Field> fields_;

    void _updateNeighbours(Point);
    void _setFields();
public:
    _FieldVector(dimension_t, dimension_t);

    Field &getField(Point);

    // "unsigned int" as multiplication of 2 unsigned shorts can give an unsigned int
    unsigned int size();

    /**
     * @brief 
     * Fills the board with mineCount mines and assigns correct numbers to non-mine fields
     * 
     * @param mineCount 
     * Number of mines to be placed on the field
     */
    void populate(unsigned int mineCount);

    // Mostly for debugging
    void print();

    /**
     * @brief 
     * Vector of points representing the coordinates of 
     * 
     * @param point
     * point to get the neighbours of
     * 
     * @return std::vector<Point> 
     */
    std::vector<Point> neighbourCoords(Point point);
};


class GameBoard {
    _FieldVector board_;
    std::vector<Field*> revealed;

public:
    GameBoard(dimension_t width, dimension_t height) : board_(width, height){}

    unsigned int size() { return board_.size(); }
};

