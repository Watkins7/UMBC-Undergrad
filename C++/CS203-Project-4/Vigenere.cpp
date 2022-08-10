/*
** File: Vigenere.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .cpp file, child class of "Cipher", and a vigenere cipher class
** for the Cipher Project 4 in CMSC 202 @ UMBC
*/

#include "Vigenere.h"

// Name: Vigenere (Default Constructor)
// Desc: Constructor to build an empty Vigenere Cipher (Defaults key to "test")
// Preconditions - None
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere() {}

// Name: Vigenere (Overloaded Constructor)
// Desc: Constructor to build a populated Vigenere Cipher
// Preconditions - Pass it the message, isEncrypted, and key
// Postconditions - Creates a Vigenere cipher to be encrypted
Vigenere::Vigenere(string message, bool isEncrypted, string key) : Cipher(message, isEncrypted){
    m_key = key;
}

// Name: Vigenere (Destructor)
// Desc: Destructor - Anything specific to delete in Vigenere?
// Preconditions - ~Vigenere exists
// Postconditions - Vigenere destroyed
Vigenere::~Vigenere() {}

// Name: Encrypt
// Desc: Encrypts using key (See project document for details)
// Preconditions - Message exists
// Postconditions - Encrypts using key
void Vigenere::Encrypt() {

    vector<int> keyList; // stores an alternating keylist
    int keySize = m_key.size(); // stores key size

    // Go through the entire key, letter by letter
    for (int i = 0; i < m_key.size(); i++){

        // Go through the alphabet to find a match between key_letter and alphabet
        for (int j = 0; j < UPPERALPHABET.size(); j++){

            // if the key letter matches the letter in the alphabet, record the location for encryption
            if ( m_key.at(i) == LOWERALPHABET.at(j) or m_key.at(i) == UPPERALPHABET.at(j) ) {

                // add key location to list
                keyList.push_back(j);
            }

        }

    } // end of for loop for getting the key list

    // Set the first key
    int currentKeyPosition = 0;

    stringstream newMessage; // holds new encrypted message
    bool found = false; // Whether or not the character was found
    string newLetter; // Holds new encrypted letter

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // Search the lower alphabet for the letter
        for (int j = 0; j < LOWERALPHABET.size(); j++) {
            if (GetMessage().at(i) == LOWERALPHABET.at(j) and !found) {

                // create new letter cipher
                newLetter = LOWERALPHABET.at( (j + keyList.at(currentKeyPosition) ) % 26);

                // set found to true
                found = true;

                //move key position
                currentKeyPosition = (currentKeyPosition + 1) % keySize;

            } // end of if statement
        }

        // Search the upper alphabet for the letter
        for (int x = 0; x < UPPERALPHABET.size(); x++) {
            if (GetMessage().at(i) == UPPERALPHABET.at(x) and !found) {

                // create new letter cipher
                newLetter = UPPERALPHABET.at((x + keyList.at(currentKeyPosition) ) % 26);

                // set found to true
                found = true;

                // move current key position
                currentKeyPosition = (currentKeyPosition + 1) %keySize;

            }
        }

        // if found add new letter to new cipher
        if (found) {
            newMessage << newLetter;
        }

            // else add whatever character it is to cipher
        else
            newMessage << GetMessage().at(i);

        // reset found
        found = false;
    }

    // Set new message
    SetMessage( newMessage.str() );

}

// Name: Decrypt
// Desc: Decrypts using key (See project document for details)
// Preconditions - Message exists
// Postconditions - Uses key to decrypt.
void Vigenere::Decrypt() {

    vector<int> keyList; // stores an alternating keylist
    int keySize = m_key.size(); // stores key size

    // Go through the key, find each letter location and record the int location
    for (int i = 0; i < m_key.size(); i++){

        // Go through the alphabet to find the letter
        for (int j = 0; j < UPPERALPHABET.size(); j++){

            // if the key letter matches the letter in the alphabet, record the location for encryption
            if ( m_key.at(i) == LOWERALPHABET.at(j) or m_key.at(i) == UPPERALPHABET.at(j) ) {

                // add key location to list
                keyList.push_back(j);
            }

        }

    } // end of for loop for getting the key list

    // Set the first key
    int currentKeyPosition = 0;

    stringstream newMessage; // holds new encrypted message
    bool found = false; // Whether or not the character was found
    string newLetter; // Holds new encrypted letter

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // Search the lower alphabet for the letter
        for (int j = 0; j < LOWERALPHABET.size(); j++) {

            // if you find the letter in the alphabet
            if (GetMessage().at(i) == LOWERALPHABET.at(j) and !found) {

                // create new letter cipher
                newLetter = LOWERALPHABET.at( (j - keyList.at(currentKeyPosition) + 26 ) % 26);

                // set found to true
                found = true;

                //move key position
                currentKeyPosition = (currentKeyPosition + 1) % keySize;

            } // end of if statement
        }

        // Search the upper alphabet for the letter
        for (int x = 0; x < UPPERALPHABET.size(); x++) {
            if (GetMessage().at(i) == UPPERALPHABET.at(x) and !found) {

                // create new letter cipher
                newLetter = UPPERALPHABET.at((x - keyList.at(currentKeyPosition) + 26 ) % 26);

                // set found to true
                found = true;

                // move current key position
                currentKeyPosition = (currentKeyPosition + 1) %keySize;

            }
        }

        // if found add new letter to new cipher
        if (found) {
            newMessage << newLetter;
        }

        // else add whatever character it is to cipher
        else
            newMessage << GetMessage().at(i);

        // reset found
        found = false;
    }

    // Set message
    SetMessage( newMessage.str() );

}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Vigenere in this case)
string Vigenere::ToString() {return "(Vigenere)";}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - v, delimiter, isencrypted, delimiter,
// message, delimiter, key are returned for output
string Vigenere::FormatOutput() {

    // Make a stringstream
    stringstream output;

    // Output appropriate data
    output << "v|";

    // get info if it is encrypted
    if (GetIsEncrypted())
        output << "1|";
    else
        output << "0|";

    // output key
    output << GetMessage() << "|" << m_key;

    // return the string for file output
    return output.str();
}