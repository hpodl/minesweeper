#include <catch2/catch_all.hpp>
#include "GameBoard.hh"

class FieldVecTestable : public _FieldVector {
    void populate(Points mines) {
        for(auto point : mines) {
            getField(point).setMine();
        }
        calculateFields();
    }
};

TEST_CASE("Sanity check.") {
    REQUIRE(0 == 0);
}

TEST_CASE("GameBoard initializes with correct size.", "[GameBoard, size, initialization]") {
    unsigned int width(12), height(14);
    REQUIRE(GameBoard(width, height, 30).size() == width*height);
}
