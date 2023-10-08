#include "Field.hh"

/**
 * @brief Represents a single field on the gameboard
 *
 */

Field::Field()
    : isMine_(false), isRevealed_(false), isMarked_(false), mineCount_(0) {}
Field::~Field(){};

bool Field::isMine() const { return isMine_; }
bool Field::isRevealed() const { return isRevealed_; }
bool Field::isMarked() const { return isMarked_; }

void Field::setMarked(bool mark) { isMarked_ = mark; }

bool Field::reveal() {
    bool wasRevealed = !isRevealed_;
    isRevealed_ = true;
    isMarked_ = false;

    return wasRevealed;
}

char Field::charRepresentation() const {
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

unsigned short Field::getMineCount() const { return mineCount_; }
