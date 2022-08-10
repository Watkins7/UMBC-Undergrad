/*
** File: Cipher.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .cpp file, and abstract cipher class, for the Cipher Project 4 in CMSC 202 @ UMBC
** The parent class of all other ciphers in the project
*/

#include "Cipher.h"

// Name: Cipher (Default Constructor)
// Desc - Stores a message that is either read to be encrypted or already encrypted
// Preconditions - None
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher() {}

// Name: Cipher (Overloaded Constructor)
// Desc - Stores a message that is either read to be encrypted or already encrypted
// Preconditions - A message is passed to this constructor, and if it is encrypted
// Postconditions - A message is stored in a Cipher object
Cipher::Cipher(string message, bool isEncrypted) {
    m_message = message;
    m_isEncrypted = isEncrypted;
}

// Name: ~Cipher (Destructor)
// Desc - Virtual destructor
// Preconditions - A derived class is being deleted
// Postconditions - A base class is deleted
Cipher::~Cipher() {}

// Name: SetMessage
// Desc - Updates a message
// Preconditions - The message exists
// Postconditions - A message is updated
void Cipher::SetMessage(string message) {
    m_message = message;
}

// Name: GetMessage
// Desc - Returns the message
// Preconditions - The message exists
// Postconditions - A message is returned
string Cipher::GetMessage() {
    return m_message;
}

// Name: GetIsEncrypted
// Desc - Returns isEncrypted (0 is not encrypted and 1 is encrypted)
// Preconditions - The cipher exists
// Postconditions - A bool is returned
bool Cipher::GetIsEncrypted() {
    return m_isEncrypted;
}

// Name: ToggleEncrypted
// Desc - Turns (true to false) or (false to true)
// Preconditions - The cipher exists
// Postconditions - The m_isEncrypted is toggled
void Cipher::ToggleEncrypted() {
    m_isEncrypted = !m_isEncrypted;
}

// Name: Overloaded << Operator
// Desc - Outputs the message
// Preconditions - The object exists
// Postconditions - The message from the object is returned
ostream& operator<<(ostream &output, Cipher &C) {
    cout << C.m_message;
}
