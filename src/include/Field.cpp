#include "Field.hh"

/**
 * @brief Represents a single field on the gameboard
 *
 */

Field::Field()
    : isMine_(false), isRevealed_(false), isMarked_(false), mineCount_(0) {}
Field::~Field(){};

bool Field::isMine() { return isMine_; }
bool Field::isRevealed() { return isRevealed_; }
bool Field::isMarked() { return isMarked_; }

void Field::setMarked(bool mark) { isMarked_ = mark; }

void Field::reveal() {
    isRevealed_ = true;
    isMarked_ = false;
}

char Field::charRepresentation() {
    if (!isRevealed_) {
        return '@';
    }
    if (isMarked_) {
        return 'M';
    }

    else {
        return isMine_ ? '*' : (mineCount_ + '0');
    }
}

void Field::incrementMineCount() { ++mineCount_; }

void Field::setMine() { isMine_ = true; }

unsigned short Field::getMineCount() { return mineCount_; }
