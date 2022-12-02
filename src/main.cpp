#include <iostream>
#include <fmt/format.h>
#include "GameBoard.hh"
#include <vector>
#include <optional>

using Points = std::vector<Point>;

int main() {
    GameBoard board(10, 10, 0);
    board.print();

    for(;;) {
        Point toReveal;
        std::cin >> toReveal.x >> toReveal.y;
        std::cout << '\n';

        if (1/*board.reveal(toReveal).has_value()*/) {
        for(auto revealed : board.reveal(toReveal)) 
            std::cout << revealed.x << "," << revealed.y << "\n";
        board.print();
        }
        else {
            std::cout << "Hit a mine!\n";
        }
    }
    
    return 0;
}