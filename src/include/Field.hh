#pragma once
// Abstract class for fields
class Field {
    bool isRevealed_;
    bool isMarked_;
public:
    Field() : isRevealed_(false), isMarked_(false){}
    virtual ~Field(){};
    virtual bool isMine(){ return false; }

    virtual char charRepresentation() {return 'f';};
};

class FieldMine : public Field {
public:
    ~FieldMine(){};
    virtual bool isMine() override{ return true; }
    virtual char charRepresentation() override { return '*'; }
};

class FieldEmpty : public Field {
    unsigned short mineCount_;
public:

    FieldEmpty() : mineCount_(0){}
    ~FieldEmpty(){};
    virtual char charRepresentation() override { return ' '; }
    virtual bool isMine() override {return false;}
};