#include <iostream>
#include <fstream>

using namespace std;

// Constant that sets row and column length of the array
const int MAXSIZE = 4;

void createDefaultBoard(int myArray[MAXSIZE][MAXSIZE]);
void loadBoard(int myArray[MAXSIZE][MAXSIZE]);
bool selectTile(int myArray[MAXSIZE][MAXSIZE], int, int);
void swapTile(int myArray[MAXSIZE][MAXSIZE], int, int);
bool checkWinner();
void printBoard(int myArray[MAXSIZE][MAXSIZE]);



int main() {

    // User's answer to any question
    int response, column, row;
    bool inGame = true;

    // Create an empty Array populated with 0's
    int myArray[MAXSIZE][MAXSIZE] = {0};

    // Print Greeting
    cout << "Welcome to the Fifteen Game" << '\n';

    // cin.clear();
    // cin.ignore(256,'\n');
    // cin >> response;

    // Asks user if they want a default board or to load a board
    do {

        cout << "Would you like to load a board?" << '\n';
        cout << "1. Yes" << '\n' << "2. No" << '\n';

        //cin.clear();
        //cin.ignore(256,'\n');
        cin >> response;

    } while (response != 2 and response != 1);


    // If response == 1, then load a board from a file
    if (response == 1)
        loadBoard(myArray);

    // else make a default board
    else
        createDefaultBoard(myArray);

    printBoard(myArray);

    // While user has not solved the game, keep running the game
    do {

        cout << '\n' << "What is the row (left) and column (top) to slide?" << endl;
        cin >> row;
        cin >> column;

        cout << myArray[row-1][column-1] << '\n';

        // Check to see if tile is moveable
        // If it is swap it, print board, check if user won
        if (selectTile(myArray, row - 1, column - 1)) {

            cout << "We have moved your piece!" << endl;

            swapTile(myArray, row - 1, column - 1);

            printBoard(myArray);
        }

    } while (inGame);

    return 0;
}

// Function creates a default board
void createDefaultBoard(int myArray[MAXSIZE][MAXSIZE]) {

    // Counter needed to populate array for numbers 1-15
    int counter = 1;

    // Nested for loop populates the whole array execpt for the last line
    for (int i = 0; i < MAXSIZE - 1; i++){

        for (int x = 0; x < MAXSIZE; x++){
            myArray[i][x] = counter;
            counter++;
        }
    }

    // Populates the last line of the array up until the last two elements
    for (int i = 0; i < MAXSIZE - 2; i++){
        myArray[MAXSIZE-1][i] = counter;
        counter++;
    }

    // Populates the very last element
    myArray[MAXSIZE-1][MAXSIZE-1] = counter;

}

// Loads board from file
void loadBoard(int myArray[MAXSIZE][MAXSIZE]) {

}

// Returns true if the tile selected has an empty slot adjacent to it
bool selectTile(int myArray[MAXSIZE][MAXSIZE], int row, int column) {

    bool freeSpace = false;

    if (row != 0)
        if (myArray[column][row - 1] == 0)
            return !freeSpace;

    if (column != 0)
        if (myArray[column - 1][row] == 0)
            return !freeSpace;

    if (row != MAXSIZE)
        if (myArray[column][row + 1] == 0)
            return !freeSpace;

    if (column != MAXSIZE)
        if (myArray[column + 1][row] == 0)
            return !freeSpace;

    cout << "Cannot move that space" << endl;
    return freeSpace;
}

// Moves piece to open tile, function only triggers if selectTile() is True
void swapTile(int myArray[MAXSIZE][MAXSIZE], int row, int column) {

    cout << myArray[row][column] << "swaptile" << endl;

    if (row != 0)
        if (myArray[row - 1][column] == 0) {

            myArray[row - 1][column] = myArray[row][column];
            myArray[row][column] = 0;
            return;
        }

    if (column != 0)
        if (myArray[row][column - 1] == 0) {

            myArray[row][column - 1] = myArray[row][column];
            myArray[row][column] = 0;
            return;
        }


    if (row != MAXSIZE)
        if (myArray[row + 1][column] == 0) {

            myArray[row + 1][column] = myArray[row][column];
            myArray[row][column] = 0;
            return;
        }


    if (column != MAXSIZE)
        if (myArray[row][column + 1] == 0) {

            myArray[row][column + 1] = myArray[row][column];
            myArray[row][column] = 0;
            return;
        }


}

// Checks to see if array is in order
bool checkWinner() {

}

// Prints array to screen for user to see board
void printBoard(int myArray[MAXSIZE][MAXSIZE]) {

    //Code need to print first line of the board
    cout << "       ";
    for (int i = 1; i < MAXSIZE + 1; i++){
        cout << i << "     ";
    }

    // Prints the rest of the board
    // This for loop prints the row indicator
    for (int i = 0; i < MAXSIZE; i++){

        cout << '\n' << "   " << i + 1 << "|";

        // This for loop prints the numbers on the board
        for (int x = 0; x < MAXSIZE; x++){
            cout << "   " << myArray[i][x] << "|";
        }
    }

}




