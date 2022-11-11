#pragma once

#include <vector>
#include "Field.hh"

#include <boost/optional.hpp>

using dimension_t = unsigned short;
// needs to fit dimension_t*dimension_t result
using area_t = unsigned int;

struct Point {
    dimension_t x;
    dimension_t y;
};

using Points = std::vector<Point>;

class _FieldVector {
    dimension_t width_, height_;
    area_t mineCount_;
    std::vector<Field> fields_;

    void _updateNeighbours(Point);
    void _setFields();
public:
    _FieldVector(dimension_t, dimension_t, area_t);

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
    GameBoard(dimension_t width, dimension_t height, area_t mineCount) : board_(width, height, mineCount){}

    /**
     * @brief Reveals fields recursively. Returns a vector of revealed fields' coordinates. 
     * On mine hit, return empty optional value. Return type is also aliased as "Revealed"
     * @details 
     * @param point - coordinates of field to be revealed
     * @return boost::optional<std::vector<Field*>>
     */
    boost::optional<Points> reveal(Point point);

    Points _reveal_internal(Point point);
    
    area_t size() { return board_.size(); }
};

