#include <iostream>
#include "GameBoard.hh"

int main() {
    _FieldVector board(15, 12);
    board.populate(40);
    board.print();

    return 0;
}