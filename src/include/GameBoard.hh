#pragma once

#include <vector>
#include "Field.hh"
#include <set>
#include <optional>

using dimension_t = unsigned short;
// needs to fit dimension_t*dimension_t result
using area_t = unsigned int;

/**
 * @brief 
 * Newtype used to make the code more readable
 */
struct Point {
    dimension_t x;
    dimension_t y;
};

using Points = std::vector<Point>;

/**
 * @brief 
 * Handles the basic functionality of creating a matrix of Fields and filling it with mines
 */
class _FieldVector {
    dimension_t width_, height_;
    area_t mineCount_;
    std::vector<Field> fields_;

    void _updateNeighbours(Point);
public:
    _FieldVector(dimension_t, dimension_t, area_t);

    Field &getField(Point);

    Point shape() {
        return {width_, height_};
    }

    area_t mineCount() {
        return mineCount_;
    }

    area_t size();
    
    void recalculateNeighbours();

    /**
     * @brief 
     * Fills the board with mineCount mines and assigns correct numbers to non-mine fields
     * 
     * @param mineCount 
     * Number of mines to be placed on the field
     */
    void populate(area_t mineCount);

    /**
     * @brief Utility/debugging method displaying the board with fields represented by their char representation 
     * 
     */
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

/**
 * @brief 
 * Stores a minesweeper board and handles basic game logic such as revealing or flagging Fields
 */
class GameBoard {
    _FieldVector board_;

    Points _reveal_empty(Point point);
public:
    GameBoard(dimension_t width, dimension_t height, area_t mineCount) : board_(width, height, mineCount){}
    GameBoard(_FieldVector board) : board_(board){}
    GameBoard() : board_(0,0,0) {};

    /**
     * @brief Reveals fields recursively. Returns a vector of revealed fields' coordinates. 
     * On mine hit, returns std::nullopt
     * @details 
     * @param point - coordinates of field to be revealed
     * @return boost::optional<Points>
     */
    Points reveal(Point point);
    void mark(Point point);


    /**
     * @brief Handles chording logic
     * 
     * @param point coordinates of chording origin
     * @return Points points revealed via chording
     */
    Points chord(Point point);

    /**
     * @brief Creates a new minefield and fills it with mines
     * 
     * @param width
     * @param height 
     * @param mineCount 
     */
    void generate(dimension_t width, dimension_t height, area_t mineCount);
    
    dimension_t width()  { return board_.shape().x; };
    dimension_t height() { return board_.shape().y; };
    area_t mineCount() { return board_.mineCount(); };

    area_t size() { return board_.size(); }

    void print() { board_.print(); };

    Field& getField(Point point) { return board_.getField(point); }
};