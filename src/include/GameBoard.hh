#pragma once

#include <set>
#include <vector>

#include "Field.hh"
#include "types.hh"

/**
 * @brief
 * Handles the basic functionality of creating a matrix of Fields and filling it
 * with mines
 */
class _FieldVector {
    dimension_t width_, height_;
    area_t mineCount_;
    std::vector<Field> fields_;

    void _updateNeighbours(Point);

  public:
    _FieldVector(dimension_t, dimension_t, area_t);

    Field &getField(Point);

    Point shape() const { return {width_, height_}; }

    area_t mineCount() const { return mineCount_; }

    area_t size() const;

    void recalculateNeighbours();

    /**
     * @brief
     * Fills the board with mineCount mines and assigns correct numbers to
     * non-mine fields
     *
     * @param mineCount
     * Number of mines to be placed on the field
     */
    void populate(area_t mineCount);

    /**
     * @brief Utility/debugging method displaying the board with fields
     * using their char representation
     *
     */
    void print() const;

    /**
     * @brief
     * Returns a vector of neighbouring `Point`s
     *
     * @param point
     * Point to get the neighbours of
     *
     * @return std::vector<Point>
     */
    std::vector<Point> neighbourCoords(Point coordinates);
};

/**
 * @brief
 * Stores a minesweeper board and handles basic game logic such as revealing or
 * flagging Fields
 */
class GameBoard {
    _FieldVector board_;
    area_t markCount_ = 0;
    bool mineHit_ = false;

    std::vector<Point> _reveal_empty(Point coordinates);

  public:
    GameBoard(dimension_t width, dimension_t height, area_t mineCount);
    GameBoard(_FieldVector board);
    GameBoard();

    bool isLost() const;

    /**
     * @brief Reveals fields recursively. Returns a vector of revealed fields'
     * coordinates.
     * @details
     * @param point - coordinates of field to be revealed
     * @return std::vector<Point>
     */
    std::vector<Point> reveal(Point coordinates);

    /**
     * @brief Marks/unmarks a point at Point(x,y) location
     * @param coordinates
     */
    void toggleMark(Point coordinates);
    
    /**
     * @brief Returns a reference to a point at coordinates Point(x,y)
     * @return Field&
     */
    Field &getField(Point coordinates);

    /**
     * @brief Handles chording logic
     *
     * @param point coordinates of chording origin
     * @return std::vector<Point>; revealed via chording
     */
    std::vector<Point> chord(Point coordinates);

    /**
     * @brief Creates a new minefield and fills it with mines
     *
     * @param width
     * @param height
     * @param mineCount
     */
    void generate(dimension_t width, dimension_t height, area_t mineCount);

    /**
     * @brief Total number of mines on the board
     * @return area_t
     */
    area_t mineCount() const;
    area_t markCount() const;

    dimension_t width() const;
    dimension_t height() const;
    area_t size() const;

    /**
     * @brief Prints the ascii representation of the board; for debugging
     * purposes
     */
    void print() const;
};