#pragma once

class Field {
    bool isMine_;
    bool isRevealed_;
    bool isMarked_;
    unsigned short mineCount_;
public:
    Field() : isMine_(false), isRevealed_(false), isMarked_(false),  mineCount_(0){}
    ~Field(){};
    bool isMine(){ return isMine_; }
    bool isRevealed() {return isRevealed_;}


    void reveal() {
        isRevealed_ = true;
    }
    
    char charRepresentation() {
        if(!isRevealed_) {
            return '@';
        }
        else {
            return isMine_ ? '*' : (mineCount_ + '0');
        }
    }
    void incrementMineCount() { ++mineCount_; }
    void setMine() { isMine_ = true; }
    unsigned short getMineCount() { return mineCount_; }
};