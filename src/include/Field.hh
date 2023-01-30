#pragma once

/**
 * @brief Represents a single field on the gameboard
 *
 */
class Field {
    bool isMine_;
    bool isRevealed_;
    bool isMarked_;
    unsigned short mineCount_;

  public:
    Field();
    ~Field();

    bool isMine();
    bool isRevealed();
    bool isMarked();

    /**
     * @brief Sets internal variable whether the field is marked
     *
     * @param mark true if marked, else false
     */
    void mark(bool mark);

    /**
     * @brief Sets internal variable signalling that the field is revealed
     */
    void reveal();

    /**
     * @brief Char representation of a field from a POV of a player
     *
     * @return char representation of the field
     */
    char charRepresentation();

    /**
     * @brief Increments local variable representing the number of neighbouring
     * mines
     */
    void incrementMineCount();
    /**
     * @brief Sets internal variable signalling that the field contains a mine
     */
    void setMine();
    
    /**
     * @brief Returns a number of neighbouring mines
     */
    unsigned short getMineCount();
};