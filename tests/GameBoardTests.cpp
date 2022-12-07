#include <catch2/catch_all.hpp>
#include "GameBoard.hh"

#include <algorithm>

bool operator==(const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

class FieldVecTestable : public _FieldVector {
    void populate(Points mines) {
        for(auto point : mines) {
            getField(point).setMine();
        }
        recalculateNeighbours();
    }
};

TEST_CASE("Sanity check.") {
    REQUIRE(0 == 0);
}

TEST_CASE("GameBoard initializes with correct size.", "[GameBoard, size, initialization]") {
    unsigned int width(12), height(14);
    REQUIRE(GameBoard(width, height, 30).size() == width*height);
}

TEST_CASE("GameBoard height and width are set correctly", "[GameBoard, width, height]") {
    unsigned int width(12), height(14);
    auto board = GameBoard(width, height, 30);
    
    REQUIRE(board.width() == width);
    REQUIRE(board.height() == height);
}

TEST_CASE("GameBoard correctly reveals recursively.", "[GameBoard, reveal, recursive]") {
    unsigned int width(12), height(14);
    REQUIRE(GameBoard(width, height, 30).size() == width*height);
}



TEST_CASE("neighbourCoords return valid coordinates", "[FieldVector, neighbourCoords]") {
    auto fields = _FieldVector(20,20,0);
    Point point(2,2);
    Points actualCoords {
        {1,1}, {1,2}, {1,3},
        {2,1}, {2,2}, {2,3},
        {3,1}, {3,2}, {3,3}
    };

    Points calculated = fields.neighbourCoords(point);

    REQUIRE(std::is_permutation(actualCoords.begin(), actualCoords.end(), calculated.begin()) == true);
}

TEST_CASE("neighbourCoords return valid coordinates on the upper edge", "[FieldVector, neighbourCoords]") {
    auto fields = _FieldVector(20,20,0);
    Point point(0,2);
    Points actualCoords {
        {0,1}, {0,2}, {0,3},
        {1,1}, {1,2}, {1,3}
    };

    Points calculated = fields.neighbourCoords(point);


    REQUIRE(std::is_permutation(actualCoords.begin(), actualCoords.end(), calculated.begin()) == true);
}


TEST_CASE("neighbourCoords return valid coordinates in the upper-left corner", "[FieldVector, neighbourCoords]") {
    auto fields = _FieldVector(20,20,0);
    Point point(0,0);
    Points actualCoords {
        {0,0}, {0,1},
        {1,0}, {1,1}
    };

    Points calculated = fields.neighbourCoords(point);

    REQUIRE(std::is_permutation(actualCoords.begin(), actualCoords.end(), calculated.begin()) == true);
}

TEST_CASE("neighbourCoords return valid coordinates in the lower-right corner", "[FieldVector, neighbourCoords]") {
    auto fields = _FieldVector(10, 12, 0);
    Point point(9,11);
    Points actualCoords {
        {8, 10}, {9, 10},
        {8, 11}, {9, 11}
    };

    Points calculated = fields.neighbourCoords(point);

    REQUIRE(std::is_permutation(actualCoords.begin(), actualCoords.end(), calculated.begin()) == true);
}

