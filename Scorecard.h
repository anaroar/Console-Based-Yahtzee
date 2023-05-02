#pragma once

void setTextColor(int color);

// class to hold player scores
class Scorecard {
public:
    // set player scores
    int scores[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    //                 1s,2s,3s,4s,5s,6s,3k,4k,fh,sm,lg,ch,yh

    // track when score slots are used
    bool scoreUsed[13] = { false, false, false, false, false, false, false, false, false, false, false, false, false };

    // construct player id
    int playerId = 0;
    Scorecard(int id = 0) : playerId(id) {}

    int turnCounter = 0;
    int turnScore = 0;
    std::string scoreType = "";
    int scoreSelect = 0;
    int upperTotal = 0;
    int bonus = 0;
    int yahtzeeBonus = 0;
    int lowerTotal = 0;
    int grandTotal = 0;
    int rollSum = 0;
    int bonusCounter = 63;

    // check if player has turn
    bool playerHasTurn() {
        for (int i = 0; i < 13; i++) {
            if (scoreUsed[i] == false)
                return true;
        }
        return false;
    }

    // clear scores
    void clearScores() {
        for (int i = 0; i < 13;) {
            scores[i] = 0;
            i++;
        }
        for (int j = 0; j < 13;) {
            scoreUsed[j] = false;
            j++;
        }
        upperTotal = 0;
        bonus = 0;
        yahtzeeBonus = 0;
        lowerTotal = 0;
        grandTotal = 0;
        rollSum = 0;
        bonusCounter = 63;
    }

    // print turn banner
    void turnBanner() {
        std::cout << " -------------------" << std::endl;
        std::cout << "|  PLAYER " << playerId << "'s TURN  |" << std::endl;
        std::cout << " -------------------" << std::endl;
    }

    // print scoreboard
    void printBoard(int color) {
        setTextColor(color);
        std::cout << "\n\t~PLAYER " << playerId << " SCORECARD~\n" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "|\t1s (Ones)\t|\t" << scores[0] << "\t|" << std::endl;
        std::cout << "|\t2s (Twos)\t|\t" << scores[1] << "\t|" << std::endl;
        std::cout << "|\t3s (Threes)\t|\t" << scores[2] << "\t|" << std::endl;
        std::cout << "|\t4s (Fours)\t|\t" << scores[3] << "\t|" << std::endl;
        std::cout << "|\t5s (Fives)\t|\t" << scores[4] << "\t|" << std::endl;
        std::cout << "|\t6s (Sixes)\t|\t" << scores[5] << "\t|" << std::endl;
        std::cout << "|---------------------------------------|" << std::endl;
        std::cout << "|\tBonus (" << bonusCounter << " more pts)\t" << bonus << "\t|" << std::endl;
        std::cout << "|---------------------------------------|" << std::endl;
        std::cout << "|\tUPPER TOTAL\t|\t" << upperTotal << "\t|" << std::endl;
        std::cout << "|---------------------------------------|" << std::endl;
        std::cout << "|\t3 of a Kind\t|\t" << scores[6] << "\t|" << std::endl;
        std::cout << "|\t4 of a Kind\t|\t" << scores[7] << "\t|" << std::endl;
        std::cout << "|\tFull House\t|\t" << scores[8] << "\t|" << std::endl;
        std::cout << "|\tSm. Straight\t|\t" << scores[9] << "\t|" << std::endl;
        std::cout << "|\tLg. Straight\t|\t" << scores[10] << "\t|" << std::endl;
        std::cout << "|\tChance\t\t|\t" << scores[11] << "\t|" << std::endl;
        std::cout << "|\tYahtzee\t\t|\t" << scores[12] << "\t|" << std::endl;
        std::cout << "|\tYahtzee Bonus\t|\t" << yahtzeeBonus << "\t|" << std::endl;
        std::cout << "|---------------------------------------|" << std::endl;
        std::cout << "|\tLOWER TOTAL\t|\t" << lowerTotal << "\t|" << std::endl;
        std::cout << "|---------------------------------------|" << std::endl;
        std::cout << "|\tGRAND TOTAL\t|\t" << grandTotal << "\t|" << std::endl;
        std::cout << "-----------------------------------------\n" << std::endl;
        setTextColor(7);
    }

    // print back what player scored each turn
    void printLastScore(std::string score, int value) {
        setTextColor(12);
        std::cout << "\nPLAYER " << playerId << " SCORED " << value << " POINTS FOR " << score << "\n" << std::endl;
        setTextColor(7);
        system("pause");
    }

    // calculate sum of one type of number (upper section: 1-6)
    int sumOfOne(std::vector<int> rollCombo) {
        int scoreSum = 0;
        for (int i = 0; i < 5; i++) {
            if (rollCombo.at(i) == scoreSelect)
                scoreSum = scoreSum + scoreSelect;
        }
        return scoreSum;
    }

    // calculate sum of all dice (3k, 4k, ch)
    int sumOfAll(std::vector<int> rollCombo) {
        int scoreSum = 0;
        for (int i = 0; i < 5; i++) {
            scoreSum = scoreSum + rollCombo.at(i);
        }
        return scoreSum;
    }

    // check if score condition is met
    bool validateScore(int scoreType, std::vector<int> rollCombo) {
        int conditionCounter = 0;

        if (scoreType == 7) {
            // check for 3 of a kind
            for (int i = 1; i < 7; i++) {
                for (int j : rollCombo) {
                    if (j == i)
                        ++conditionCounter;
                }
                if (conditionCounter > 2)
                    break;
                else
                    conditionCounter = 0;
            }
            if (conditionCounter > 2)
                return true;
            else
                return false;
        }
        else if (scoreType == 8) {
            // check for 4 of a kind
            for (int i = 1; i < 7; i++) {
                for (int j : rollCombo) {
                    if (j == i)
                        ++conditionCounter;
                }
                if (conditionCounter > 3)
                    break;
                else
                    conditionCounter = 0;
            }
            if (conditionCounter > 3)
                return true;
            else
                return false;
        }
        else if (scoreType == 9) {
            // check for full house
            int firstValue = rollCombo.at(0);
            int secondValue = 0;
            int condCounter = 0;

            // look for second pair value
            for (int i = 0; i < rollCombo.size(); i++) {
                if (rollCombo.at(0) != rollCombo.at(i)) {
                    secondValue = rollCombo.at(i);
                    break;
                }
            }
            // check that pair values are sets of 2 and 3
            for (int j = 0; j < rollCombo.size(); j++) {
                if (firstValue == rollCombo.at(j))
                    ++conditionCounter;
                if (secondValue == rollCombo.at(j))
                    ++condCounter;
            }
            if ((conditionCounter == 2 && condCounter == 3) || (conditionCounter == 3 && condCounter == 2))
                return true;
            else
                return false;
        }
        else if (scoreType == 10) {
            // check for small straight
            std::sort(rollCombo.begin(), rollCombo.end());
            for (int i = 1; i < rollCombo.size(); i++) {
                int j = i - 1;
                if (rollCombo.at(i) == rollCombo.at(j) + 1)
                    ++conditionCounter;
            }
            if (conditionCounter < 3)
                return false;
            else
                return true;
        }
        else if (scoreType == 11) {
            // check for large straight
            std::sort(rollCombo.begin(), rollCombo.end());
            for (int i = 1; i < rollCombo.size(); i++) {
                int j = i - 1;
                if (rollCombo.at(i) != rollCombo.at(j) + 1)
                    return false;
            }
            return true;
        }
        else if (scoreType == 13) {
            // check for yahtzee
            for (int i = 1; i < rollCombo.size(); i++) {
                if (rollCombo.at(0) != rollCombo.at(i))
                    return false;
            }
            return true;
        }
        else
            std::cout << "ERROR, INVALID SCORE.";
        return false;
    }

    // check if score selection is valid
    bool validateSelection(int selection) {
        --selection;
        if (scoreUsed[selection] == true) {
            setTextColor(12);
            std::cout << "\nERROR: INVALID SELECTION";
            setTextColor(7);
            return false;
        }
        else
            return true;
    }

    // re-open yahtzee score slot if bonus is scored
    void checkYahtzeeBonus(std::vector<int> rollCombo) {
        for (int i = 1; i < rollCombo.size(); i++) {
            if (rollCombo.at(0) != rollCombo.at(i))
                return;
        }
        if (scoreUsed[12] != true)
            return;
        else 
            scoreUsed[12] = false;
    }

    // choose score from available score slots
    void chooseScore(std::vector<int> rollCombo) {
        bool scoreConditionMet = true;
        bool selectionValid = true;
        std::string scoreMenu[13] = {
            "\n1.  Ones",
            "\n2.  Twos",
            "\n3.  Threes",
            "\n4.  Fours",
            "\n5.  Fives",
            "\n6.  Sixes",
            "\n7.  3 of a Kind",
            "\n8.  4 of a Kind",
            "\n9.  Full House",
            "\n10. Sm Straight",
            "\n11. Lg Straight",
            "\n12. Chance",
            "\n13. Yahtzee"
        };

        // if another yahtzee is scored, yahtzee is available again to select
        checkYahtzeeBonus(rollCombo);

        // print available score slots
        std::cout << "\n\nCHOOSE A SCORE:\n";
        for (int i = 0; i < 13; i++) {
            if (scoreUsed[i] == false) {
                std::cout << scoreMenu[i];
            }
        }

        // player chooses a score
        do {
            std::cout << "\n\nENTER A NUMBER:\t";
            std::cin >> scoreSelect;
            selectionValid = validateSelection(scoreSelect);
        } while (!selectionValid);

        // insert selected score into player scorecard
        switch (scoreSelect) {
        case 1:
            scoreType = "ONES";
            rollSum = sumOfOne(rollCombo);
            scores[0] = rollSum;
            turnScore = scores[0];
            scoreUsed[0] = true;
            break;
        case 2:
            scoreType = "TWOS";
            rollSum = sumOfOne(rollCombo);
            scores[1] = rollSum;
            turnScore = scores[1];
            scoreUsed[1] = true;
            break;
        case 3:
            scoreType = "THREES";
            rollSum = sumOfOne(rollCombo);
            scores[2] = rollSum;
            turnScore = scores[2];
            scoreUsed[2] = true;
            break;
        case 4:
            scoreType = "FOURS";
            rollSum = sumOfOne(rollCombo);
            scores[3] = rollSum;
            turnScore = scores[3];
            scoreUsed[3] = true;
            break;
        case 5:
            scoreType = "FIVES";
            rollSum = sumOfOne(rollCombo);
            scores[4] = rollSum;
            turnScore = scores[4];
            scoreUsed[4] = true;
            break;
        case 6:
            scoreType = "SIXES";
            rollSum = sumOfOne(rollCombo);
            scores[5] = rollSum;
            turnScore = scores[5];
            scoreUsed[5] = true;
            break;
        case 7:
            scoreType = "3 OF A KIND";
            scoreConditionMet = validateScore(7, rollCombo);
            if (scoreConditionMet == true) {
                rollSum = sumOfAll(rollCombo);
                scores[6] = rollSum;
            }
            else
                scores[6] = 0;
            turnScore = scores[6];
            scoreUsed[6] = true;
            break;
        case 8:
            scoreType = "4 OF A KIND";
            scoreConditionMet = validateScore(8, rollCombo);
            if (scoreConditionMet == true) {
                rollSum = sumOfAll(rollCombo);
                scores[7] = rollSum;
            }
            else
                scores[7] = 0;
            turnScore = scores[7];
            scoreUsed[7] = true;
            break;
        case 9:
            scoreType = "FULL HOUSE";
            scoreConditionMet = validateScore(9, rollCombo);
            if (scoreConditionMet == true) {
                scores[8] = 25;
            }
            else
                scores[8] = 0;
            turnScore = scores[8];
            scoreUsed[8] = true;
            break;
        case 10:
            scoreType = "SMALL STRAIGHT";
            scoreConditionMet = validateScore(10, rollCombo);
            if (scoreConditionMet == true) {
                scores[9] = 30;
            }
            else
                scores[9] = 0;
            turnScore = scores[9];
            scoreUsed[9] = true;
            break;
        case 11:
            scoreType = "LARGE STRAIGHT";
            scoreConditionMet = validateScore(11, rollCombo);
            if (scoreConditionMet == true) {
                scores[10] = 40;
            }
            else
                scores[10] = 0;
            turnScore = scores[10];
            scoreUsed[10] = true;
            break;
        case 12:
            scoreType = "CHANCE";
            rollSum = sumOfAll(rollCombo);
            scores[11] = rollSum;
            turnScore = scores[11];
            scoreUsed[11] = true;
            break;
        case 13:
            scoreType = "YAHTZEE";
            scoreConditionMet = validateScore(13, rollCombo);
            if (scoreConditionMet == true) {
                if (scores[12] == 0)
                    scores[12] = 50;
                else
                    yahtzeeBonus = yahtzeeBonus + 100;
            }
            else
                scores[12] = 0;
            turnScore = scores[12];
            scoreUsed[12] = true;
            break;
        default:
            // error message
            break;
        }
    }

    // Update score totals
    void updateTotals() {
        int lowerSum = 0;
        int upperSum = 0;

        for (int i = 0; i < 6; i++) {
            upperSum = upperSum + scores[i];
        }
        upperTotal = upperSum;
        bonusCounter = 63 - upperSum;

        if (upperTotal >= 63) {
            bonus = 35;
            upperTotal = upperTotal + bonus;
        }

        for (int j = 6; j < 13; j++) {
            lowerSum = lowerSum + scores[j];
        }
        lowerTotal = lowerSum + yahtzeeBonus;

        grandTotal = upperTotal + lowerTotal;
    }
};