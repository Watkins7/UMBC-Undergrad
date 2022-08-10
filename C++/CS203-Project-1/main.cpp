/*******************************************
 ** File: Proj1.cpp
 ** Project: CMSC 202 Project 1, Spring 2020
 ** Author: William Atkins
 ** Date: 2/22/20
 ** Section: 55
 ** Email: watkins7@umbc.edu
 **
 ** This is project 1 where you play a Fifteen Game
 ** The fifteen (15 or 16 puzzle) is a common sliding puzzle...
 ** that you may remember from your youth.
 ** It involves a frame of numbered square tiles...
 ** in random order with one tile missing.
 ** The object of the puzzle is to place the...
 ** tiles in order by making sliding moves that use the empty space.
 ******************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


const int MAXSIZE = 4; // Constant that sets row and column length of the array
const int WIDTH = 6; // Constant that sets width for setw() in the print statement

void createDefaultBoard(int myArray[MAXSIZE][MAXSIZE]); // Function to create a default board
void loadBoard(int myArray[MAXSIZE][MAXSIZE]); // Function to load a board from a file
bool selectTile(int myArray[MAXSIZE][MAXSIZE], int, int); // Function to verify is a file can be moved
void swapTile(int myArray[MAXSIZE][MAXSIZE], int, int); // Function used to switch tiles
bool checkWinner(int myArray[MAXSIZE][MAXSIZE]); // Function used to check if the user won the game
void printBoard(int myArray[MAXSIZE][MAXSIZE]); // Function prints the array to the screen
bool playAgain(); // Function asks user if they want to play again

int main() {


    int response; // User's answer to any question
    int column, row; // Keeps track of the column and row the user wants to move
    bool repeatGame = true; // Keeps the game running on a loop, after winning
    bool inGame = true; // Keeps player selecting tiles until win conditions are met

    // Create an empty Array populated with 0's
    int myArray[MAXSIZE][MAXSIZE] = {0};

    // Print Greeting
    cout << "Welcome to the Fifteen Game" << '\n';

    // Do-While loop used to repeat game if requested
    do {

        // Do-While loop asks user if they want a default board or to load a board
        do {

            cout << "Would you like to load a board?" << '\n';
            cout << "1. Yes" << '\n' << "2. No" << '\n';
            cin >> response;

            // Input validation
            cin.clear();
            cin.ignore(256, '\n');

        } while ((response != 2 && response != 1) || cin.fail());


        // switch statement to decide if to load a file or create a defualt board
        switch (response) {

            // Case 1, load a board from a file
            case 1:
                loadBoard(myArray);
                break;

            // Case 2, make a default board
            case 2:
                createDefaultBoard(myArray);
                break;

        } // End of switch statement

        printBoard(myArray);

        // While user has not solved the game, keep running the game
        do {

            // Do-while to ask user what piece they want to move
            // Conditions will continue to run until the user enters a valid piece
            do {

                // Do-while input validation to get row and column, works 99% of the time
                do {
                    cout << '\n' << "What is the row (left) and column (top) to slide?" << endl;
                    cin >> row;
                    cin >> column;

                    cin.clear();
                    cin.ignore(256, '\n');

                } while (cin.fail());


            } while (!selectTile(myArray, row - 1, column - 1)); // End of second do-while

            // Check to see if tile is moveable
            // If it is swap it, print board, check if user won
            if (selectTile(myArray, row - 1, column - 1)) {

                swapTile(myArray, row - 1, column - 1);
                printBoard(myArray);
            }

            // Check to see if user won the game, returns false if user won the game
            inGame = checkWinner(myArray);

        } while (inGame); // End of do-while to see if user won the game

        // Run function to ask user if they want to play again
        repeatGame = playAgain();

    } while (repeatGame); // End of repeatGame do-while loop, breaks if user decides not to play

    cout << "Thank you for playing the game of fifthteen!  Goodbye!" << endl;

    return 0;

} // End of main

// Function name: playAgain
// Pre-condition: none,
// Function: To figure out if user wants to play the game
// Post-condition: Returns true or false depending if the user wants
// to play the game again
bool playAgain(){

    char response; // Variable needed for user input

    cout << "Congrats you've won!" << endl;

    //Asks user if they want to repeat the game
    do {
        cout << "Play again? ( 'y' / 'n' )" << endl;
        cin >> response;

        cin.clear();
        cin.ignore(256,'\n');

        // Check user's response and return bools as approriate to replay the game
        if (response == 'y' || response == 'Y')
            return true;
        else if (response == 'n' || response == 'N')
            return false;

    } while ( (response != 'y' && response != 'n') || cin.fail() ); // runs until users enters 'y' or 'n'

    // Extra code to avoid return errors, even though it isn't needed
    // Checks user response and returns a bool based on wether the user wants to keep playing
    if (response == 'y' || response == 'Y')
               return true;
    else
               return false;
}

// Function name: createDefaultBoard
// Pre-conditon: integer multi-dim array, myArray, that is a valid (empty) Array defined by MAXSIZE
// Post-codition:: Creates a default board to play, populates myArray with numbers
// from 1 to MAXSIZE, and makes the second to last number 0
void createDefaultBoard(int myArray[MAXSIZE][MAXSIZE]) {

    cout << "Loading default board." << endl;

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
        myArray[MAXSIZE - 1][i] = counter;
        counter++;
    }

    // Populates the very last element
    myArray[MAXSIZE - 1][MAXSIZE - 1] = counter;

    // Makes sure that the second to last element of the array is 0
    // Need for second play through
    myArray[MAXSIZE - 1][MAXSIZE - 2] = 0;
}

// Function name: loadBoard
// Pre-condtion: integer multi-dim array, myArray, that is a valid (empty) Array defined by MAXSIZE
// Post-condition: Takes numbers from a file line by line and puts them into myArray
void loadBoard(int myArray[MAXSIZE][MAXSIZE]) {

    string fileName; // Variable used to store file name

    // Asks for the file name to load the board
    cout << "What is the file name?" << endl;
    cin >> fileName;

    // Open the input file stream
    ifstream inputStream(fileName);

    // If the input stream is open, populate myArray gameboard
    if (inputStream.is_open()){

        for (int i = 0; i < MAXSIZE; i++){
            for (int x = 0; x < MAXSIZE; x++){

                // inputStream will populate the myArray
                inputStream >> myArray[i][x];
            }
        }
    }

    else {
        cout << "File not found, loading default board." << endl;
        createDefaultBoard(myArray);
    }

    // Close filestream
    inputStream.close();
}

// Function name: selectTile
// Pre-condition: multi-dim array that is populate with numbers, a row number, and a column number
// Post-condition: Returns true if the tile selected (row, column), has an empty slot adjacent to it in myArray
bool selectTile(int myArray[MAXSIZE][MAXSIZE], int row, int column) {

    // If the row or column selected is bigger than the board, then it is impossible to find that piece
    if (row > MAXSIZE or column > MAXSIZE)
        return false;

    // Below are nested if statements to check boundries of the multi-dimensional array
    // The second if statements check to see if the the tile next to the tile selected is the "0 marker"
    // If we do see the marker, we return true so that we know we can swap the tiles

    // AGAIN, WE RETURN TRUE IF WE FIND THE 0 MARKER, that means we can switch tiles

    // If we are greater than the 0 row, then we can check if the row below us has the 0 marker
    if (row > 0)
        if (myArray[row - 1][column] == 0)
            return true;

    // If we are greater than the 0 column, then we can check if the column to the left us has the 0 marker
    if (column > 0)
        if (myArray[row][column - 1] == 0)
            return true;

    // If we are less than the MAX_SIZE row, then we can check if the row above us has the 0 marker
    if (row < MAXSIZE)
        if (myArray[row + 1][column] == 0)
            return true;

    // If we are less than the MAX_SIZE column, then we can check if the column right of us has the 0 marker
    if (column < MAXSIZE)
        if (myArray[row][column + 1] == 0)
            return true;

    // Print statement for if the user chose the blank tile
    if (myArray[row][column] == 0)
        cout << "You chose the blank." << endl;

    // If no conditions are met, then that piece cannot be moved
    cout << "You cannot move that tile." << endl;
    return false;
}

// Function name: swapTile
// Pre-condition: an integer multi-dim array defined by MAX_SIZE that contains numbers, AND A VALID row number and column number
// Post-contion: Moves tile (row, column) to the open 0 tile, function only triggers if selectTile() is True
void swapTile(int myArray[MAXSIZE][MAXSIZE], int row, int column) {

    // If we aren't on the row 0, we can look at the row above us
    // If that row equals 0, move the marker up
    if (row > 0)
        if (myArray[row - 1][column] == 0) {

            myArray[row - 1][column] = myArray[row][column];
            myArray[row][column] = 0;
            cout << "The tile slide up." << endl;
            return;
        }

    // If we aren't on column 0, we can look to the columns left of us
    // If the tile to the left of us equals 0, swap the tiles
    if (column > 0)
        if (myArray[row][column - 1] == 0) {

            myArray[row][column - 1] = myArray[row][column];
            myArray[row][column] = 0;
            cout << "The tile slide left." << endl;
            return;
        }

    // If the row we are looking at is less than the maxsize of the array, we can look at the tiles above us
    // If the tile above us equals 0, move the tile up
    if (row < MAXSIZE)
        if (myArray[row + 1][column] == 0) {

            myArray[row + 1][column] = myArray[row][column];
            myArray[row][column] = 0;
            cout << "The tile slide down." << endl;
            return;
        }

    // If the column we are looking is less than the MAXSIZE, we can look to the tile to the right of us
    // If the tile to the right of us equals 0, swap it and move the tile right
    if (column < MAXSIZE)
        if (myArray[row][column + 1] == 0) {

            myArray[row][column + 1] = myArray[row][column];
            myArray[row][column] = 0;
            cout << "The tile slide right" << endl;
            return;
        }


}

// Function name: checkWinner
// Pre-condition: an integer multi-dim array defined by MAX_SIZE, that contains numbers
// Post-condition: Checks to see if array is in order from 1 to MAX_SIZE, returning
// false means that no numbers are out of order and myArray is in order
// returning true means that myArray is not in order
bool checkWinner(int myArray[MAXSIZE][MAXSIZE]) {

    int counter = 1; // Counter to compare itself vs the current element in the array, starts at 1 and moves up to 15

    // Nested for loop that compares a counter to what is at the current index of the array
    for (int i = 0; i < MAXSIZE; i++) {
        for (int x = 0; x < MAXSIZE; x++) {

            // This code triggers only if we go through the nested for loop
            // It stops right before the last index of the array, which should be 0
            // Returning false means that every element is in countable order,
            // so we can exit the ingame while loop
            if (i == MAXSIZE - 1 && x == MAXSIZE - 1)
                return false;

            // If at any time the counter does not equal the element of the array, return true
            // Returning true means keep the ingame while loop running
            if (myArray[i][x] != counter) {

                cout << "No winner." << endl;
                return true;
            }

            counter++;
        }

    }

    // It should never get this far, but return true by default
    // This means the user did not satisfy any win conditions and does not win
    return true;
}

// Function name: printBoard
// Pre-condition: an integer multi-dim array defined by MAX_SIZE, that contains numbers
// Post-condition: Prints the whole array to screen for user to see board
void printBoard(int myArray[MAXSIZE][MAXSIZE]) {

    //Code need to print column indicator
    cout << "       ";
    for (int i = 1; i < MAXSIZE + 1; i++){
        cout << i << "      ";
    }

    cout << endl;

    // Code prints multi-dim array and the row indicators
    for (int i = 0; i < MAXSIZE; i++) {

        cout << i + 1 << "|";

        for (int y = 0; y < MAXSIZE; y++) {

            cout << setw(WIDTH) << myArray[i][y] << "|";
        }

        cout << endl;
    }

}