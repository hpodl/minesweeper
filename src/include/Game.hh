#pragma once
#include "GameBoard.hh"

enum GameState {
    Playing,
    GameOver,
};

class Game {
    GameBoard gameBoard;
    GameState state;
public:
    Game(dimension_t, dimension_t, unsigned int);
    
    /**
     * @brief Starts the game loop
     * 
     * @return true if the game was won
     * @return false if the game was lost
     */
    bool start();
};