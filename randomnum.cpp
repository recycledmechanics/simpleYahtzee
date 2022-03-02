//****************************************************************************
//Programmer's Name: recylcedmechanics
// Date: February 5, 2022
// Program Name: Yahtzee Score Calculator
// Program Description: This program should be able to calculate 
// the total score of a yahtzee game using the scores stored inside 
// of a 2D array. Each "turn" of the game much be subjected to specific
// requirements in order to determine if points are obtained. The program 
// should also be able to allow the user to roll a set of die for each turn
// and use those die roll to calculate their score at the end of the game.
//*****************************************************************************

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

//prototypes
int yahtzeeScoreCalc(int arr[][5]);
int countOccurences(int arr[], int x);
void arraySort(int arr[]);
bool yahtzee(int arr[][5]);
int userRoll();



int main() {
    userRoll();
    return 0;
}

int userRoll() {
    const int rowNum = 13; //number of rows for array
    const int colNum = 5; //number of columns for array
    
    int arr[rowNum][colNum]; //allows us to go row by row and save our rand vals to 2D array

    int userEntry = 0, dieRoll = 0;
    int rollsPerTurn = 3, rollAgain;
    int twoArr[13][5];
    srand(time(0));

    cout << "***********************************************************************************************************" << endl;
    cout << "                                 Welcome to the game of Yahtzee!" << endl << endl;
    cout << "           You will be prompted to roll the die for 13 turns. You get to roll for each" << endl;
    cout << "       turn exactly 3 times as per the official rules of the game. If you choose to accept" << endl;
    cout << "   a roll before using all of your rerolls, the remaining rerolls are forfeited. If all 3 turns are used, " << endl;
    cout << "                               the last roll will be saved for scoring." << endl << endl;
    cout << "                                The game will now begin with Turn #1: " << endl << endl;
    cout << "***********************************************************************************************************" << endl << endl;

    while (dieRoll < rowNum) {
        cout << "Turn #" << dieRoll + 1 << endl;
        cout << "   > 1: Roll the die" << endl;
        cout << "   > 2: Quit" << endl;
        cout << ">> ";
        cin >> userEntry;

        //evaluates user input
        while ((userEntry >= 3 || userEntry == 0) || !cin) {
            cin.clear();
            cin.ignore();
            cout << "Your input is incorrect. Try again:" << endl;
            cout << "   > ";
            cin >> userEntry;
        }

        if (userEntry == 1) {
            cout << "Dice rolled for Turn #" << dieRoll + 1 << ": ";
            for (int i = 0; i < colNum; i++) {
                //create array that takes rand 1-6 and saves
                //each value to array row
                arr[dieRoll][i] = (rand() % 6) + 1;
                cout << arr[dieRoll][i] << ' ';
            }
            cout << endl << endl;
            rollsPerTurn--;
            while (rollsPerTurn > 0) {//if there are more turns left (user starts with 3)
                cout << "You have " << rollsPerTurn << " rolls left. Would you like to (1) try again or (2) save your current roll?" << endl;
                cout << ">> ";
                cin >> rollAgain;

                while ((rollAgain >= 3 || rollAgain == 0) || !cin) {
                    cin.clear();
                    cin.ignore();
                    cout << "Your input is incorrect. Try again:" << endl;
                    cout << "   > ";
                    cin >> rollAgain;
                }

                if (rollAgain == 1) {//user rolls again
                    rollsPerTurn--;
                    cout << "Dice rolled for Turn #" << dieRoll + 1 << ": ";
                    for (int j = 0; j < colNum; j++) {//newly random nums & overwrite original ran nums
                        arr[dieRoll][j] = (rand() % 6) + 1;
                        cout << arr[dieRoll][j] << ' ';
                    }
                    cout << endl << endl;
                }
                if (rollAgain == 2) {//saves current roll
                    rollsPerTurn = 0;//no rerolls for this turn after accepted
                    cout << endl << endl;
                    break;
                }
            }
            dieRoll += 1;
            rollsPerTurn = 3;
        }
        if (userEntry == 2) {
            cout << "Goodbye!" << endl;
            /*secret comment...*/
            return 0;
        }

    }
    //display 2d array (just for test purposes)
    cout << "Dice rolls for all turns: " << endl << endl;
    for (int i = 0; i < rowNum; i++) {

        cout << "Turn #" << (i + 1) << ": ";
        for (int j = 0; j < colNum; j++) {
            twoArr[i][j] = arr[i][j];//copies these vals into 2D array for input into yahtzeeScoreCalc func
            cout << twoArr[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
    yahtzeeScoreCalc(twoArr);
    return 0;

}

int yahtzeeScoreCalc(int arr[][5]) {
    int bonusPoints = 0, totalScore = 0, firstSix = 0;
    int aceSum = 0, twoSum = 0, threeSum = 0, fourSum = 0, fiveSum = 0, sixSum = 0;
    int threeOfAKindSum = 0, fourOfAKindSum = 0, fullHouseSum = 0, lowerStraightSum = 0, higherStraightSum = 0, yahtzeeSum = 0, chanceSum = 0;
    for (int i = 0; i < 13; i++) {//i = row of 2D array
        if (i == 0) {
            for (int i = 0; i < 5; i++) {
                if (arr[0][i] == 1) {//searches for only 1
                    aceSum = aceSum + 1;
                }
            }
        }
        if (i == 1) {//twos code
            for (int i = 0; i < 5; i++) {
                if (arr[1][i] == 2) //searches for only 2
                    twoSum = twoSum + 2;
            }
        }
        if (i == 2) {//three code
            for (int i = 0; i < 5; i++) {
                if (arr[2][i] == 3) //searches for 3
                    threeSum = threeSum + 3;
            }
        }
        if (i == 3) {//four code
            for (int i = 0; i < 5; i++) {
                if (arr[3][i] == 4) //searches for 4
                    fourSum = fourSum + 4;
            }
        }
        if (i == 4) {//five code
            for (int i = 0; i < 5; i++) {
                if (arr[4][i] == 5) //searches for 5
                    fiveSum = fiveSum + 5;
            }
        }
        if (i == 5) {//six code
            for (int i = 0; i < 5; i++) {
                if (arr[5][i] == 6) //searches for 6
                    sixSum = sixSum + 6;
            }
        }
        if (i == 6) {//three of a kind code
            int tempArr[5];
            for (int i = 0; i < 5; i++) {
                tempArr[i] = arr[6][i];
            }
            for (int x = 1; x <= 6; x++) {
                if (countOccurences(tempArr, x) >= 3) {//if an number shows up at least 3 times
                    for (int j = 0; j < 5; j++) {
                        threeOfAKindSum += arr[6][j];
                    }
                }
            }
        }
        if (i == 7) {//four of a kind code
            int tempArr[5];
            //make 1D array
            for (int i = 0; i < 5; i++) {
                tempArr[i] = arr[7][i];
            }
            for (int x = 1; x <= 6; x++) {
                if (countOccurences(tempArr, x) >= 4) {//if a number shows up at least 4 times
                    for (int j = 0; j < 5; j++) {
                        fourOfAKindSum += arr[7][j];
                    }
                }
            }
        }
        if (i == 8) {//full house code
            int tempArr[5];
            //make 1D array
            for (int i = 0; i < 5; i++) {
                tempArr[i] = arr[8][i];
            }
            for (int x = 1; x <= 6; x++) {
                for (int j = 1; j <= 6; j++) {
                    if (countOccurences(tempArr, x) == 3) {//if a number shows up exactly 3 times
                        if (countOccurences(tempArr, j) == 2) {//if a different number shows up exactly 2 times
                            fullHouseSum = 25;
                        }
                    }
                }
            }
        }
        if (i == 9) {//lower straight code
            int tempArr[5]; //making a 1D array for test purposes
            int count = 1;//count starts with the first num (so not 0)
            for (int i = 0; i < 5; i++) {
                tempArr[i] = arr[9][i]; //copies elements from subarray to tempArr
            }
            arraySort(tempArr);
            for (int i = 0; i < 5; i++) {
                if (tempArr[i + 1] == tempArr[i] + 1) {
                    count++; //increment count by 1 if the next num is 1 greater
                }
            }
            if (count >= 4) {//if there are 4+ conseq elements
                lowerStraightSum = 30;
            };
        }
        if (i == 10) {//higher straight code
            int tempArr[5];
            int count = 1;
            for (int i = 0; i < 5; i++) {
                tempArr[i] = arr[10][i];
            }
            arraySort(tempArr);
            for (int i = 0; i < 5; i++) {
                if (tempArr[i + 1] == tempArr[i] + 1) {
                    count++;
                }
            }
            if (count >= 5) {//if there are 5+ conseq elements
                higherStraightSum = 40;
            }
        }
        if (i == 11) {//yahtzee code
            if (yahtzee(arr)) {//uses func to determine if all numbers are the same
                for (int i = 0; i < 5; i++) {
                    yahtzeeSum = 50;
                }
            }
        }
        if (i == 12) {//chance code
            for (int i = 0; i < 5; i++) {//adds all numbers in this turn together
                chanceSum += arr[12][i];
            }
        }
    }
    firstSix = (aceSum + twoSum + threeSum + fourSum + fiveSum + sixSum); //adds first six rounds together
    if (firstSix >= 63) {
        bonusPoints = 35;
    }

    //totalScore uses all previous sums to find total
    totalScore = firstSix + bonusPoints + (threeOfAKindSum + fourOfAKindSum + fullHouseSum + lowerStraightSum + higherStraightSum + yahtzeeSum + chanceSum);
    cout << "Total Score: " << totalScore;


    return totalScore;
}

//extra functions to get certain parts of the program to operate as expected

int countOccurences(int arr[], int x) {//checks for highest occurence of an element for 9th turn
    int countResult = 0;
    for (int i = 0; i < 5; i++) {
        if (x == arr[i]) {//iterates through x to find how many times that value occurs in certain subarray
            countResult++;
        }
    }
    return countResult;
}

void arraySort(int arr[]) { //sorts array values in increasing order
    sort(arr, arr + 5);
}

bool yahtzee(int arr[][5]) {
    int first = arr[11][0];
    for (int i = 0; i < 5; i++) {
        if (arr[11][i] != first) {//checks if all following elements are equal to the first
            return false;
        }
    }
    return true;
}
