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
    Field() : isMine_(false), isRevealed_(false), isMarked_(false),  mineCount_(0){}
    ~Field(){};

    bool isMine(){ return isMine_; }
    bool isRevealed() { return isRevealed_; }
    bool isMarked() { return isMarked_; }
    
    void mark(bool mark) {
        isMarked_ = mark;
    }

    /**
     * @brief Sets internal variable signalling that the field is revealed
     * 
     */
    void reveal() {
        isRevealed_ = true;
        isMarked_ = false;
    }
    
    char charRepresentation() {
        if(!isRevealed_) {
            return '@';
        }
        else {
            return isMine_ ? '*' : (mineCount_ + '0');
        }
    }

    
    /**
     * @brief Increments local variable representing the number of neighbouring mines
     * 
     */
    void incrementMineCount() { ++mineCount_; }
    
    /**
     * @brief Sets internal variable signalling that the field contains a mine
     * 
     */
    void setMine() { isMine_ = true; }
    
    /**
     * @brief Returns a number of neighbouring mines
     * 
     */
    unsigned short getMineCount() { return mineCount_; }
};