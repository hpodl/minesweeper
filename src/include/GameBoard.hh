#pragma once

#include <vector>
#include "Field.hh"

using dimension_t = unsigned short;
// needs to fit dimension_t*dimension_t result
using area_t = unsigned int;

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

    area_t size();

    /**
     * @brief 
     * Fills the board with mineCount mines and assigns correct numbers to non-mine fields
     * 
     * @param mineCount 
     * Number of mines to be placed on the field
     */
    void populate(area_t mineCount);

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

    area_t size() { return board_.size(); }
};

