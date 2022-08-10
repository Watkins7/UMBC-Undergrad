/*
** File: proj4.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is main for the Cipher Project 4 in CMSC 202 @ UMBC
*/
#include "CipherTool.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

//Inside the parameters for main, we can pass arguments
//argc is the count of arguments
//argv are the parameters themselves
int main() {
    srand(time(NULL)); //Seeds the random number generator
    cout << "Welcome to UMBC Encryption" << endl;
    /*while (argc < 2) { //Checks to make sure the user passes a file to load
        cout << "You are missing a data file." << endl;
        cout << "Expected usage ./proj4 proj4_test1.txt" << endl;
        cout << "The input file should have some strings to encrypt or decrypt" << endl;
        return 0;
    }*/
    string filename = "project";
    CipherTool myCipher("proj4_test4.txt"); //Creates a new ciphertool passing the filename
    //myCipher.Start(); //Starts the cipherTool
    return 0;
}