#include <iostream>
#include "GameBoard.hh"

int main() {
    _FieldVector board(15, 12, 15*12/3);
    board.print();

    return 0;
}