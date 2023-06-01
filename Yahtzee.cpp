/*

Title:          YAHTZEE
Author:         Diana Roar
    
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#undef max
#include <vector>
#include <algorithm>
#include <limits>
#include "Dice.h"
#include "Scorecard.h"

// function declarations
void setTextColor(int color);
void clearScreen();
void rollDice(std::vector<Dice>& diePool);
void sortDiceByValue(std::vector<Dice>& dice);
void printDiceHeader();
void printRolledDice(std::vector<Dice> diePool);
void printSavedDice(std::vector<Dice> savedDice);
void printSelectMenu();
void selectDice(Scorecard player, std::vector<Dice>& diePool, std::vector<Dice>& savedDice, int& turnCounter);
void printDeselectMenu();
void deselectDie(std::vector<Dice>& diePool, std::vector<Dice>& savedDice, int i, int deselect);
void deselectDice(Scorecard player, std::vector<Dice>& diePool, std::vector<Dice>& savedDice);
void autoSelectDice(std::vector<Dice>& diePool, std::vector<Dice>& savedDice);
void resetDice(std::vector<Dice>& diePool);
std::vector<Dice> playerTurn(Scorecard player, std::vector<Dice> diePool, std::vector<Dice> savedDice);

int main()
{
    bool gameOver = false;
    bool playAgain = false;
    std::string input = "";

    std::vector<Dice> diePool = { (1), (2), (3), (4), (5) };
    std::vector<Dice> savedDice;
    Scorecard player1(1);
    Scorecard player2(2);

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
                player1.printBoard();
                system("pause");
                clearScreen();

                savedDice = playerTurn(player1, diePool, savedDice);
                clearScreen();

                sortDiceByValue(savedDice);
                printSavedDice(savedDice);
                player1.chooseScore(savedDice);
                player1.printLastScore(player1.scoreType, player1.turnScore);
                player1.updateTotals();
                std::cout << "\n";
                savedDice.clear();
                //resetDice(diePool);
                clearScreen();
            }
            // player 2
            if (player2.playerHasTurn() == true) {
                player2.turnBanner();
                player2.printBoard();
                system("pause");
                clearScreen();

                savedDice = playerTurn(player2, diePool, savedDice);
                clearScreen();

                sortDiceByValue(savedDice);
                printSavedDice(savedDice);
                player2.chooseScore(savedDice);
                player2.printLastScore(player2.scoreType, player2.turnScore);
                player2.updateTotals();
                std::cout << "\n";
                savedDice.clear();
                //resetDice(diePool);
                clearScreen();
            }
            // check if more turns exist
            if (player1.playerHasTurn() == false && player2.playerHasTurn() == false) {
                gameOver = true;
            }
        } while (!gameOver);

        // print game results
        setTextColor(12);
        std::cout << "\n\033[7mGAME OVER\033[0m\n" << std::endl; 
        setTextColor(7);
        std::cout << "PLAYER 1 FINAL SCORE: \t" << player1.grandTotal << std::endl;
        std::cout << "PLAYER 2 FINAL SCORE: \t" << player2.grandTotal << "\n" << std::endl;

        // choose a winner
        setTextColor(14);
        if (player1.grandTotal > player2.grandTotal)
            std::cout << "PLAYER 1 WINS!" << std::endl;
        else if (player1.grandTotal < player2.grandTotal)
            std::cout << "PLAYER 2 WINS!" << std::endl;
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
            gameOver = false;
            std::cout << "\n";
        }
        else {
            playAgain = false;
            setTextColor(12);
            std::cout << "\nTHANK YOU FOR PLAYING!\n" << std::endl;
            setTextColor(7);
        }
    } while (playAgain);
    return 0;
}

// set console text color
void setTextColor(int color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

// re-center screen for readability
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// roll available dice
void rollDice(std::vector<Dice>& diePool) {
    srand(time(0));
    setTextColor(12);
    std::cout << "\n\nROLLING DICE...\n" << std::endl;

    // set dice with random numbers between 1-6
    for (int i = 0; i < 5; i++) {
        if (diePool[i].dieUsed == false)
            diePool[i].setDieRoll();
    }
}

// sort dice by die value
void sortDiceByValue(std::vector<Dice>& dice) {
    std::sort(dice.begin(), dice.end());
}

// header for d1 - d5
void printDiceHeader() {
    std::cout << "D1\tD2\tD3\tD4\tD5" << std::endl;
    std::cout << "----|-------|-------|-------|------" << std::endl;
}

// print rolled dice
void printRolledDice(std::vector<Dice> diePool) {
    for (int i = 0; i < 5; i++) {
        if (diePool[i].dieUsed == false) {
            setTextColor(12);
            diePool[i].printDieRoll();
        }
        else
            diePool[i].printEmptyRoll();
    }
}

// sort and print player's current saved dice
void printSavedDice(std::vector<Dice> savedDice) {
    setTextColor(14);
    std::cout << "\n\nSAVED DICE:\t";
    if (savedDice.empty()) {
        std::cout << "[NONE]";
    }
    else {
        for (int i = 0; i < savedDice.size(); i++) {
            savedDice[i].printDieRoll();
        }
    }
    setTextColor(7);
}

// selection menu
void printSelectMenu() {
    setTextColor(7);
    std::cout << "\n\n ";
    for (int i = 0; i < 147; i++) {
        std::cout << "-";
    }
    std::cout << "\n| 1. Keep D1\t2. Keep D2\t3.Keep D3\t4. Keep D4\t5. Keep D5\t";
    std::cout << "6. Keep ALL\t7. VIEW SCORECARD\t8. DESELECT\t\033[93;4m9. CONTINUE\033[0m | \n ";
    for (int i = 0; i < 147; i++) {
        std::cout << "-";
    }
    std::cout << "\n" << std::endl;
}

// choose which dice to save
void selectDice(Scorecard player, std::vector<Dice>& diePool, std::vector<Dice>& savedDice, int& turnCounter) {
    int dieSelect = 0;
    std::string pInput = "";
    bool inputValid = true;

    do {
        std::cout << "ENTER A NUMBER:\t";
        std::cin >> dieSelect;

        // validate user input is an integer
        while (1) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                setTextColor(12);
                std::cout << "\nERROR: INVALID INPUT\n" << std::endl;
                setTextColor(7);
                std::cout << "ENTER A NUMBER:\t";
                std::cin >> dieSelect;
            }
            if (!std::cin.fail())
                break;
        }

        switch (dieSelect) {
        case 1:
            savedDice.push_back(diePool[0]);
            diePool[0].dieUsed = true;
            break;
        case 2:
            savedDice.push_back(diePool[1]);
            diePool[1].dieUsed = true;
            break;
        case 3:
            savedDice.push_back(diePool[2]);
            diePool[2].dieUsed = true;
            break;
        case 4:
            savedDice.push_back(diePool[3]);
            diePool[3].dieUsed = true;
            break;
        case 5:
            savedDice.push_back(diePool[4]);
            diePool[4].dieUsed = true;
            break;
        case 6:
            // keep all & skip remaining rolls
            setTextColor(14);
            std::cout << "\nARE YOU SURE YOU WANT TO KEEP ALL? Y/N:\t";
            std::cin >> pInput;
            setTextColor(7);
            if (pInput == "Y" || pInput == "y") {
                autoSelectDice(diePool, savedDice);
                turnCounter = 2;
                break;
            }
            else
                break;
        case 7:
            // view scorecard
            clearScreen();
            player.printBoard();
            system("pause");
            clearScreen();
            printSavedDice(savedDice);
            std::cout << "\n\n";
            setTextColor(12);
            printDiceHeader();
            printRolledDice(diePool);
            printSelectMenu();
            break;
        case 8:
            // deselect kept dice to include in next roll
            deselectDice(player, diePool, savedDice);
            clearScreen();
            sortDiceByValue(savedDice);
            printSavedDice(savedDice);
            setTextColor(12);
            std::cout << "\n\n";
            printDiceHeader();
            printRolledDice(diePool);
            printSelectMenu();
            break;
        case 9:
            // continue to next roll
            clearScreen();
            sortDiceByValue(savedDice);
            printSavedDice(savedDice);
            break;
        default:
            setTextColor(12);
            std::cout << "\nERROR: INVALID INPUT\n" << std::endl;
            setTextColor(7);
            break;
        }
    } while (dieSelect != 6 && dieSelect != 9);
}

// deselection menu
void printDeselectMenu() {
    setTextColor(8);
    std::cout << "\n\n ";
    for (int i = 0; i < 129; i++) {
        std::cout << "-";
    }
    std::cout << "\n| 1. Drop D1\t2. Drop D2\t3.Drop D3\t4. Drop D4\t5. Drop D5\t6. Drop ALL\t7. VIEW SCORECARD\t8. RETURN |\n ";
    for (int i = 0; i < 129; i++) {
        std::cout << "-";
    }
    std::cout << "\n" << std::endl;
}

// deselect saved dice
void deselectDie(std::vector<Dice>& diePool, std::vector<Dice>& savedDice, int i, int deselect) {
    int dieIdNum = savedDice[i].dieId;
    for (int j = 0; j < 5; j++) {
        if (diePool[j].dieId == dieIdNum)
            diePool[j].dieUsed = false;
    }
    savedDice.erase(savedDice.begin() + i);
}

// deselect kept die rolls
void deselectDice(Scorecard player, std::vector<Dice>& diePool, std::vector<Dice>& savedDice) {
    int deselect = 0;
    int xCounter;

    do {
        clearScreen();

        // if there are no saved dice, return to main menu
        if (savedDice.empty()) {
            setTextColor(12);
            std::cout << "\n\nTHERE ARE NO MORE SAVED DICE TO DESELECT!\n\nRETURNING TO MAIN MENU...\n" << std::endl;
            setTextColor(7);
            system("pause");
            deselect = 8;
            break;
        }

        // print current saved dice that player can deselect
        xCounter = 0;
        sortDiceByValue(savedDice);
        setTextColor(14);
        std::cout << "\n\nSAVED DICE:\n" << std::endl;
        printDiceHeader();
        for (int i = 0; i < savedDice.size(); i++) {
            savedDice[i].printDieRoll();
            ++xCounter;
        }
        setTextColor(8);
        for (int j = xCounter; j < savedDice.size(); j++) {
            std::cout << "X\t";
        }

        printDeselectMenu();

        std::cout << "ENTER A NUMBER:\t";
        std::cin >> deselect;

        // validate user input is an integer
        while (1) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                setTextColor(12);
                std::cout << "\nERROR: INVALID INPUT\n" << std::endl;
                setTextColor(7);
                std::cout << "ENTER A NUMBER:\t";
                std::cin >> deselect;
            }
            if (!std::cin.fail())
                break;
        }

        switch (deselect) {
        case 1:
            deselectDie(diePool, savedDice, 0, deselect);
            break;
        case 2:
            deselectDie(diePool, savedDice, 1, deselect);
            break;
        case 3:
            deselectDie(diePool, savedDice, 2, deselect);
            break;
        case 4:
            deselectDie(diePool, savedDice, 3, deselect);
            break;
        case 5:
            deselectDie(diePool, savedDice, 4, deselect);
            break;
        case 6:
            // deselect all
            savedDice.clear();
            resetDice(diePool);
            setTextColor(7);
            break;
        case 7:
            // view scorecard
            clearScreen();
            setTextColor(7);
            player.printBoard();
            system("pause");
            clearScreen();
            printSavedDice(savedDice);
            printDeselectMenu();
            break;
        case 8:
            // return to main
            setTextColor(7);
            break;
        default:
            setTextColor(12);
            std::cout << "\nERROR: INVALID INPUT\n" << std::endl;
            setTextColor(7);
            break;
        }
    } while (deselect != 6 && deselect != 8);
}

// auto-select dice on last roll
void autoSelectDice(std::vector<Dice>& diePool, std::vector<Dice>& savedDice) {
    // automatically add unused dice into saved dice pool 
    for (int i = 0; i < 5; i++) {
        if (diePool[i].dieUsed == false) {
            savedDice.push_back(diePool[i]);
            diePool[i].dieUsed = true;
        }
    }
}

// reset dice
void resetDice(std::vector<Dice>& diePool) {
    for (int i = 0; i < 5; i++)
        diePool[i].dieUsed = false;
}

// player turn
std::vector<Dice> playerTurn(Scorecard player, std::vector<Dice> diePool, std::vector<Dice> savedDice) {
    // 3 rolls per turn
    for (int i = 0; i < 3; i++) {
        if (savedDice.size() == 5)
            i = 2;
        else {
            rollDice(diePool);
            printDiceHeader();
            printRolledDice(diePool);
        }

        // User chooses which dice to keep
        if (i < 2) {
            printSelectMenu();
            selectDice(player, diePool, savedDice, i);
        }
        else {
            // automatically keep all dice on 3rd roll
            autoSelectDice(diePool, savedDice);
        }
    }
    return savedDice;
}
