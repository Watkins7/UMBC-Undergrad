/*
** File: Cipher.h
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .h file, and abstract cipher class, for the Cipher Project 4 in CMSC 202 @ UMBC
** The parent class of all other ciphers in the project
*/


#ifndef LAST_PROJECT_CIPHER_H
#define LAST_PROJECT_CIPHER_H


#include <iostream>
#include <string>
#include <sstream>      //Used to format output for each subtype for output
#include <vector>
using namespace std;

//**Constants**
const char DELIMITER = '|';

const vector<char> LOWERALPHABET{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

const vector<char> UPPERALPHABET{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                                 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const vector<char> UPPERCONSTANTS{ 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z'};

const vector<char> LOWERCONSTANTS{ 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

const char DASH = '-';

class Cipher{
public:


    // Name: Cipher (Default Constructor)
    // Desc - Stores a message that is either read to be encrypted or already encrypted
    // Preconditions - None
    // Postconditions - A message is stored in a Cipher object
    Cipher();

    // Name: Cipher (Overloaded Constructor)
    // Desc - Stores a message that is either read to be encrypted or already encrypted
    // Preconditions - A message is passed to this constructor, and if it is encrypted
    // Postconditions - A message is stored in a Cipher object
    Cipher(string message, bool isEncrypted);

    // Name: ~Cipher (Destructor)
    // Desc - Virtual destructor
    // Preconditions - A derived class is being deleted
    // Postconditions - A base class is deleted
    virtual ~Cipher();

    // Name: Decrypt
    // Desc - A purely virtal function to decrypt a message
    // Preconditions - The message is not already decrypted
    // Postconditions - A message is decrypted based on the child class
    virtual void Decrypt() = 0;

    // Name: Encrypt
    // Desc - A purely virtal function to encrypt a message
    // Preconditions - The message is not already encrypted
    // Postconditions - A message is encrypted based on the child class
    virtual void Encrypt() = 0;

    // Name: GetMessage
    // Desc - Returns the message
    // Preconditions - The message exists
    // Postconditions - A message is returned
    string GetMessage();

    // Name: GetIsEncrypted
    // Desc - Returns isEncrypted (0 is not encrypted and 1 is encrypted)
    // Preconditions - The cipher exists
    // Postconditions - A bool is returned
    bool GetIsEncrypted();

    // Name: SetMessage
    // Desc - Updates a message
    // Preconditions - The message exists
    // Postconditions - A message is updated
    void SetMessage(string);

    // Name: ToggleEncrypted
    // Desc - Turns (true to false) or (false to true)
    // Preconditions - The cipher exists
    // Postconditions - The m_isEncrypted is toggled
    void ToggleEncrypted();

    // Name: ToString
    // Desc - A purely virtual function that returns the string of the object type
    // Preconditions - The object exists
    // Postconditions - The subtype is returned
    virtual string ToString() = 0;


    // Name: FormatOutput
    // Desc - A purely virtual function that returns the formatted data for Output
    // Preconditions - The object exists
    // Postconditions - The type, message, and key are output
    virtual string FormatOutput() = 0;

    // Name: Overloaded << Operator
    // Desc - Outputs the message
    // Preconditions - The object exists
    // Postconditions - The message from the object is returned
    friend ostream &operator<<( ostream &output, Cipher &C);

private:
    string m_message; //The message being encrypted/decrypted
    bool m_isEncrypted; //Indicates if the message is encrypted/decrypted
};

#endif

