#include <iostream>
#include "GameBoard.hh"

int main() {
    _FieldVector board(12, 14);
    board.populate(50);
    board.print();

    return 0;
}