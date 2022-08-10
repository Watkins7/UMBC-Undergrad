/*
** File: Ong.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .cpp file, and Ong cipher class, for the Cipher Project 4 in CMSC 202 @ UMBC
*/

#include "Ong.h"

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(){}

// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates a Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted) : Cipher(message, isEncrypted){}

// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){}

// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char letter) {

    // go through a list of vowels and find if the letter matches a vowel
    for (int i = 0; i < UPPERCONSTANTS.size(); i++){

        // if we find the letter equals a constant, return false, meaning it is not a vowel
        if (letter == UPPERCONSTANTS.at(i) or letter == LOWERCONSTANTS.at(i) )
            return false;

    }

    // return true by default, meaning its a vowel or special character
    return true;
}

//Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt(){

    stringstream newMessage; // holds new encrypted message

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // if the message is a vowel/special character, add it to stringstream
        if ( IsVowel( GetMessage().at(i) ) )
            newMessage << GetMessage().at(i);

        // else the letter is a constant and we add "ong-"
        else
            newMessage << GetMessage().at(i) << "ong-";

    }

    // Last thing to do, set new message
    SetMessage( newMessage.str() );

}

// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt(){

    stringstream newMessage; // holds new encrypted messager

    // for every element in the message
    for (int i = 0; i < GetMessage().size(); i++) {

        // while the letter is a dash, skip it
        while ( GetMessage().at(i) == DASH )
            i++;

        // if the message is a vowel/special character, add it to stringstream
        if ( IsVowel( GetMessage().at(i) ) )
            newMessage << GetMessage().at(i);

        // else the letter is a constant and we know the next four letters are "ong-"
        // so we skip the next four letters
        else {
            newMessage << GetMessage().at(i);
            i+=3;
        }

    }

    // Last thing to do, set new message
    SetMessage( newMessage.str() );

}

// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString(){return "(Ong)";}

// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
// message, delimiter, blank are output
string Ong::FormatOutput(){

    // Make a stringstream
    stringstream output;

    // Output appropriate data
    output << "o|";

    // Output if it is encrypted
    if (GetIsEncrypted())
        output << "1|";
    else
        output << "0|";

    output << GetMessage() << "|";

    // Return string for file output
    return output.str();
}