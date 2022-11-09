#include <iostream>
#include "GameBoard.hh"

int main() {
    _FieldVector board(4, 3);
    board.populate(5);
    board.print();

    return 0;
}