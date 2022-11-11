#include <iostream>
#include <fmt/format.h>
#include "GameBoard.hh"

int main() {
    GameBoard board(10, 10, 15);
    board.print();

    for(;;) {
        Point toReveal;
        std::cin >> toReveal.x >> toReveal.y;
        std::cout << '\n';

        if (board.reveal(toReveal).has_value()) {
            board.print();
        }
        else {
            std::cout << "Hit a mine!\n";
        }
    }

    
    return 0;
}