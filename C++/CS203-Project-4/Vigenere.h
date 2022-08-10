/*
** File: Vigenere.h
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .h file, child class of "Cipher", and a vigenere cipher class
** for the Cipher Project 4 in CMSC 202 @ UMBC
*/

#ifndef LAST_PROJECT_VIGENERE_H
#define LAST_PROJECT_VIGENERE_H


#include "Cipher.h"
#include <istream>
#include <string>
using namespace std;

class Vigenere: public Cipher{
public:


    // Name: Vigenere (Default Constructor)
    // Desc: Constructor to build an empty Vigenere Cipher (Defaults key to "test")
    // Preconditions - None
    // Postconditions - Creates a Vigenere cipher to be encrypted
    Vigenere();


    // Name: Vigenere (Overloaded Constructor)
    // Desc: Constructor to build a populated Vigenere Cipher
    // Preconditions - Pass it the message, isEncrypted, and key
    // Postconditions - Creates a Vigenere cipher to be encrypted
    Vigenere(string, bool, string);


    // Name: Vigenere (Destructor)
    // Desc: Destructor - Anything specific to delete in Vigenere?
    // Preconditions - ~Vigenere exists
    // Postconditions - Vigenere destroyed
    ~Vigenere();


    // Name: Encrypt
    // Desc: Encrypts using key (See project document for details)
    // Preconditions - Message exists
    // Postconditions - Encrypts using key
    void Encrypt();


    // Name: Decrypt
    // Desc: Decrypts using key (See project document for details)
    // Preconditions - Message exists
    // Postconditions - Uses key to decrypt.
    void Decrypt();


    // Name: ToString
    // Desc - A function that returns the string of the object type
    // Preconditions - The object exists
    // Postconditions - The subtype is returned (Vigenere in this case)
    string ToString();


    // Name: FormatOutput()
    // Desc - A function that returns the formatted output for Output function
    // Preconditions - The object exists (use stringstream)
    // Postconditions - v, delimiter, isencrypted, delimiter,
    // message, delimiter, key are returned for output
    string FormatOutput();


private:
    string m_key; //Key to encrypt or decrypt message
};


#endif

