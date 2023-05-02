/*

Title:          YAHTZEE
Author:         Diana Roar

TO DO:
    -refine error handling
    -yahtzee banner/anim when yahtzee is scored
    -implement cursor
    -enable viewing scorecard manually when selecting from score menu

TO FIX/FEEDBACK:
    -reinforce entering one number at a time at selection menu?
    
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <algorithm>
#include "Dice.h"
#include "Scorecard.h"

void setTextColor(int color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

// re-center screen for readability
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// sort and print current roll combo
void printRollCombo(std::vector<int> rollCombo) {
    setTextColor(14);
    std::cout << "\nSAVED DICE:\t";
    if (rollCombo.empty()) {
        std::cout << "[NONE]";
    }
    else {
        std::sort(rollCombo.begin(), rollCombo.end());
        for (auto i = rollCombo.begin(); i < rollCombo.end(); i++) {
            std::cout << *i << " ";
        }
    }
    setTextColor(7);
}

// selection menu
void printSelectMenu() {
    std::cout << "\n\n ---------------------------------------------------------------------------------------------------------------------------";
    std::cout << "\n| 1. Keep D1\t2. Keep D2\t3.Keep D3\t4. Keep D4\t5. Keep D5\t6. Keep ALL\t7. DESELECT\t8. CONTINUE |";
    std::cout << "\n ---------------------------------------------------------------------------------------------------------------------------\n\n";
}

// deselection menu
void printDeselectMenu() {
    std::cout << "\n\n ---------------------------------------------------------------------------------------------------------";
    std::cout << "\n| 1. Drop D1\t2. Drop D2\t3.Drop D3\t4. Drop D4\t5. Drop D5\t6. Drop ALL\t7. RETURN |";
    std::cout << "\n ---------------------------------------------------------------------------------------------------------\n\n";
}

// auto-select dice on last roll
void autoSelectDice(Dice d1, Dice d2, Dice d3, Dice d4, Dice d5, std::vector<int>& rollCombo) {
    if (rollCombo.empty()) {
        rollCombo.push_back(d1.dieRoll);
        rollCombo.push_back(d2.dieRoll);
        rollCombo.push_back(d3.dieRoll);
        rollCombo.push_back(d4.dieRoll);
        rollCombo.push_back(d5.dieRoll);
    }
    else if (rollCombo.size() == 1) {
        rollCombo.push_back(d2.dieRoll);
        rollCombo.push_back(d3.dieRoll);
        rollCombo.push_back(d4.dieRoll);
        rollCombo.push_back(d5.dieRoll);
    }
    else if (rollCombo.size() == 2) {
        rollCombo.push_back(d3.dieRoll);
        rollCombo.push_back(d4.dieRoll);
        rollCombo.push_back(d5.dieRoll);
    }
    else if (rollCombo.size() == 3) {
        rollCombo.push_back(d4.dieRoll);
        rollCombo.push_back(d5.dieRoll);
    }
    else if (rollCombo.size() == 4) {
        rollCombo.push_back(d5.dieRoll);
    }
}

// deselect kept die rolls
void deselectDice(std::vector<int>& rollCombo) {
    int deselect = 0;
    std::vector<int> deselectCombo;
    
    if (!deselectCombo.empty())
        deselectCombo.clear();
    for (int i : rollCombo) {
        deselectCombo.push_back(i);
    }
    printRollCombo(rollCombo);
    setTextColor(8);
    printDeselectMenu();
    do {
        std::cout << "ENTER 1, 2, 3, 4, 5, 6, OR 7:\t";
        std::cin >> deselect;

        switch (deselect) {
        case 1:
            deselectCombo.at(0) = 0;
            break;
        case 2:
            deselectCombo.at(1) = 0;
            break;
        case 3:
            deselectCombo.at(2) = 0;
            break;
        case 4:
            deselectCombo.at(3) = 0;
            break;
        case 5:
            deselectCombo.at(4) = 0;
            break;
        case 6:
            // deselect all
            rollCombo.clear();
            setTextColor(7);
            printRollCombo(rollCombo);
            printSelectMenu();
            break;
        case 7:
            // print revised roll combo and return to main
            rollCombo.clear();
            for (int j : deselectCombo) {
                if (j != 0)
                    rollCombo.push_back(j);
            }
            setTextColor(7);
            printRollCombo(rollCombo);
            printSelectMenu();
            break;
        default:
            //
            break;
        }
    } while (deselect != 6 && deselect != 7);
}

// roll available dice
void rollDice(Dice& d1, Dice& d2, Dice& d3, Dice& d4, Dice& d5, std::vector<int> rollCombo) {
    srand(time(0));
    setTextColor(12);
    std::cout << "\n\nROLLING DICE...\n" << std::endl;
    std::cout << "D1\tD2\tD3\tD4\tD5" << std::endl;
    std::cout << "----|-------|-------|-------|------" << std::endl;

    if (rollCombo.empty()) {
        d1.setDieRoll();
        d2.setDieRoll();
        d3.setDieRoll();
        d4.setDieRoll();
        d5.setDieRoll();
    }
    else if (rollCombo.size() == 1) {
        setTextColor(8);
        std::cout << "X\t";
        setTextColor(12);
        d2.setDieRoll();
        d3.setDieRoll();
        d4.setDieRoll();
        d5.setDieRoll();
    }
    else if (rollCombo.size() == 2) {
        setTextColor(8);
        std::cout << "X\t";
        std::cout << "X\t";
        setTextColor(12);
        d3.setDieRoll();
        d4.setDieRoll();
        d5.setDieRoll();
    }
    else if (rollCombo.size() == 3) {
        setTextColor(8);
        std::cout << "X\t";
        std::cout << "X\t";
        std::cout << "X\t";
        setTextColor(12);
        d4.setDieRoll();
        d5.setDieRoll();
    }
    else if (rollCombo.size() == 4) {
        setTextColor(8);
        std::cout << "X\t";
        std::cout << "X\t";
        std::cout << "X\t";
        std::cout << "X\t";
        setTextColor(12);
        d5.setDieRoll();
    }
    setTextColor(7);
}

// choose which dice to save
void selectDice(Dice d1, Dice d2, Dice d3, Dice d4, Dice d5, std::vector<int>& rollCombo, int& turnCounter) {
    int rollSelect = 0;
    std::string pInput = "";
    bool inputValid = true;
    do {
        std::cout << "ENTER 1, 2, 3, 4, 5, 6, 7 OR 8:\t";
        std::cin >> rollSelect;

        switch (rollSelect) {
        case 1:
            rollCombo.push_back(d1.dieRoll);
            break;
        case 2:
            rollCombo.push_back(d2.dieRoll);
            break;
        case 3:
            rollCombo.push_back(d3.dieRoll);
            break;
        case 4:
            rollCombo.push_back(d4.dieRoll);
            break;
        case 5:
            rollCombo.push_back(d5.dieRoll);
            break;
        case 6:
            // keep all & skip remaining rolls
            setTextColor(14);
            std::cout << "\nARE YOU SURE YOU WANT TO KEEP ALL? Y/N:\t";
            std::cin >> pInput;
            setTextColor(7);
            if (pInput == "Y" || pInput == "y") {
                autoSelectDice(d1, d2, d3, d4, d5, rollCombo);
                turnCounter = 2;
                break;
            }
            else
                break;
        case 7:
            // deselect kept dice to include in next roll
            deselectDice(rollCombo);
            break;
        case 8:
            // continue to next roll
            clearScreen();
            printRollCombo(rollCombo);
            break;
        default:
            std::cout << "\nERROR: INVALID INPUT" << std::endl;
            break;
        }
    } while (rollSelect != 6 && rollSelect != 8);
}

// player turn
std::vector<int> playerTurn(Scorecard player, Dice d1, Dice d2, Dice d3, Dice d4, Dice d5, std::vector<int> rollCombo) {
    // 3 rolls per turn
    for (int i = 0; i < 3; i++) {
        if (rollCombo.size() == 5)
            i = 2;
        else
            rollDice(d1, d2, d3, d4, d5, rollCombo);
        // User chooses which dice to keep
        if (i < 2) {
            printSelectMenu();
            selectDice(d1, d2, d3, d4, d5, rollCombo, i);
        }
        else {
            // automatically keep all dice on 3rd roll
            autoSelectDice(d1, d2, d3, d4, d5, rollCombo);
        }
    }
    return rollCombo;
}

int main()
{
    bool gameOver = false;
    bool playAgain = false;
    // bool lastRoll = false;
    std::string input = "";
    std::vector<int> rollCombo;

    Scorecard player1(1);
    Scorecard player2(2);
    Dice die1;
    Dice die2;
    Dice die3;
    Dice die4;
    Dice die5;

    // game intro
    std::cout << "WELCOME TO..." << std::endl;
    setTextColor(12);
    std::cout << "__    __   _       _   _   _______   _____   _____   _____" << std::endl;
    std::cout << "\\ \\  / /  / \\     | | | | |__   __| |___  | |  ___| |  ___|" << std::endl;
    std::cout << " \\ \\/ /  / _ \\    | |_| |    | |       / /  | |___  | |___" << std::endl;
    std::cout << "  \\  /  / /_\\ \\   |  _  |    | |      / /   |  ___| |  ___|" << std::endl;
    std::cout << "  / /  /  ___  \\  | | | |    | |     / /__  | |___  | |___" << std::endl;
    std::cout << " / /  /_/     \\_\\ |_| |_|    |_|    /_____| |_____| |_____|" << std::endl;
    std::cout << "/_/\n" << std::endl;
    
    setTextColor(7);
    system("pause");

    do {
        clearScreen();
        setTextColor(12);
        std::cout << "\nSTARTING NEW GAME...\n" << std::endl;
        setTextColor(7);
        // alternate turns until all score slots are used for each player
        do {
            // player 1
            if (player1.playerHasTurn() == true) {
                player1.turnBanner();
                player1.printBoard(7);
                system("pause");
                clearScreen();
                rollCombo = playerTurn(player1, die1, die2, die3, die4, die5, rollCombo);
                clearScreen();
                printRollCombo(rollCombo);
                player1.chooseScore(rollCombo);
                player1.printLastScore(player1.scoreType, player1.turnScore);
                player1.updateTotals();
                std::cout << "\n";
                rollCombo.clear();
                clearScreen();
            }
            // player 2
            if (player2.playerHasTurn() == true) {
                player2.turnBanner();
                player2.printBoard(7);
                system("pause");
                clearScreen();
                rollCombo = playerTurn(player2, die1, die2, die3, die4, die5, rollCombo);
                clearScreen();
                printRollCombo(rollCombo);
                player2.chooseScore(rollCombo);
                player2.printLastScore(player2.scoreType, player2.turnScore);
                player2.updateTotals();
                std::cout << "\n";
                rollCombo.clear();
                clearScreen();
            }
            // check if more turns exist
            if (player1.playerHasTurn() == false && player2.playerHasTurn() == false) {
                gameOver = true;
            }
        } while (!gameOver);

        // print game results
        setTextColor(12);
        std::cout << "\nGAME OVER\n" << std::endl; 
        setTextColor(7);
        std::cout << "PLAYER 1 FINAL SCORE: \t" << player1.grandTotal << std::endl;
        std::cout << "PLAYER 2 FINAL SCORE: \t" << player2.grandTotal << "\n" << std::endl;

        // choose a winner
        setTextColor(14);
        if (player1.grandTotal > player2.grandTotal)
            std::cout << "PLAYER 1 WINS" << std::endl;
        else if (player1.grandTotal < player2.grandTotal)
            std::cout << "PLAYER 2 WINS" << std::endl;
        else
            std::cout << "NOBODY WINS" << std::endl;
        
        // reset game or end program
        setTextColor(7);
        std::cout << "\nDO YOU WANT TO PLAY AGAIN? Y/N:\t";
        std::cin >> input;
        if (input == "Y" || input == "y") {
            playAgain = true;
            player1.clearScores();
            player2.clearScores();
            std::cout << "\n";
        }
        else
            playAgain = false;
    } while (playAgain);
    return 0;
}
