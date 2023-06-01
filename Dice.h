#pragma once

void setTextColor(int color);

// class to generate dice
class Dice {
public:
    int dieRoll = 0;
    bool dieUsed = false;

    bool operator< (const Dice& other) const {
        return dieRoll < other.dieRoll;
    }

    // constructor for die id
    int dieId = 0;
    Dice(int id = 0) : dieId(id) {}

    // set die roll with random number from 1-6
    void setDieRoll() {
        if (dieUsed == false)
            dieRoll = 1 + rand() % 6;
        else
            return;
    }

    // print die roll value if unused
    void printDieRoll() {
        std::cout << dieRoll << "\t";
    }

    // print Xs instead of die values
    void printEmptyRoll() {
        setTextColor(8);
        std::cout << "X\t";
    }
};