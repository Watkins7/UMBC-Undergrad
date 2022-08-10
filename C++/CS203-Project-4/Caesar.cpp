/*
** File: Caesar.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .cpp file, and Caesar cipher class, for the Cipher Project 4 in CMSC 202 @ UMBC
*/

#include "Caesar.h"

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar():Cipher(){};

// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift):Cipher(message, isEncrypted) {
    m_shift = shift;
}

// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar() {}

// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt() {

    stringstream newMessage; // holds new encrypted message
    bool found = false; // Whether or not the character was found
    string newLetter; // Holds new encrypted letter

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // Search the lower alphabet for the letter
        for (int j = 0; j < LOWERALPHABET.size(); j++) {
            if (GetMessage().at(i) == LOWERALPHABET.at(j) and !found) {

                // create new letter cipher
                newLetter = LOWERALPHABET.at( (j + m_shift) % 26);
                // set found to true
                found = true;

                } // end of if statement

        } // end of for loop to search for letter

        // Search the upper alphabet for the letter
        for (int x = 0; x < UPPERALPHABET.size(); x++) {
            if (GetMessage().at(i) == UPPERALPHABET.at(x) and !found) {

                // create new letter cipher
                newLetter = UPPERALPHABET.at((x + m_shift) % 26);

                // set found to true
                found = true;
            }
        }

        // if found, add new letter to new cipher
        if (found) {
            newMessage << newLetter;
        }

        // else, add whatever character it is to cipher
        else
            newMessage << GetMessage().at(i);

        // reset found
        found = false;
    }

    // Last thing to do, set new message
    SetMessage( newMessage.str() );

} // End of encrypt function

// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
//Similar to encryption but different formula
void Caesar::Decrypt() {

    stringstream newMessage; // holds new decrypted message
    bool found = false; // Whether or not the character was found
    string newLetter; // Holds new decrypted letter

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // Search the lower alphabet for the letter
        for (int j = 0; j < LOWERALPHABET.size(); j++) {
            if (GetMessage().at(i) == LOWERALPHABET.at(j) and !found) {

                // create new letter cipher
                newLetter = LOWERALPHABET.at( (j - m_shift + 26) % 26);
                // set found to true
                found = true;

            } // end of if statement
        }

        // Search the upper alphabet for the letter
        for (int x = 0; x < UPPERALPHABET.size(); x++) {
            if (GetMessage().at(i) == UPPERALPHABET.at(x) and !found) {

                // create new letter cipher
                newLetter = UPPERALPHABET.at((x - m_shift + 26) % 26);
                // set found to true
                found = true;
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

    // Last thing to do, set new message
    SetMessage( newMessage.str() );

} // End of decryption function

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
// message, delimiter, m_shift are returned for output
string Caesar::FormatOutput() {

    // Make a stringstream
    stringstream output;

    // Output appropriate data
    output << "c|";

    // Output if it is encrypted
    if (GetIsEncrypted())
        output << "1|";
    else
        output << "0|";

    output << GetMessage() << "|" << m_shift;

    // Return string for file output
    return output.str();

}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
// Return the word "Caesar"
string Caesar::ToString() {
    return "(Caesar)";
}