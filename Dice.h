#pragma once

// Dice class
class Dice {
public:
    int dieRoll = 1;

    // set die roll
    void setDieRoll() {
        // Random number from 1-6
        dieRoll = 1 + rand() % 6;
        std::cout << dieRoll << "\t";
    }
};