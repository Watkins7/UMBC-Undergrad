/*
** File: Pokemon.cpp
** Project: CMSC 202 Project 3, Spring 2020
** Author: William Atkins
** Date: 3/30/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is the pokemon class needed for the Pokemon Project 3 in CMSC 202 @ UMBC
** Techniccally can call it a node class that contains index, name, type, what it is strong againist
*/

#include "Pokemon.h"

// Default Constructor
Pokemon::Pokemon(){};

// Overload constructor
Pokemon::Pokemon(int index, string name, string type, string strong){

    // Set values accordingly
    m_index = index;
    m_name = name;
    m_type = type;
    m_strong = strong;
    m_health = MAX_HEALTH;
    SetNext(nullptr);
}

// Returns a pointer of the next pokemon
Pokemon* Pokemon::GetNext() {
    return m_next;
}

// Returns the name of the pokemon
string Pokemon::GetName() {
    return m_name;
}

// Returns index
int Pokemon::GetIndex(){
    return m_index;
}

// Returns type
string Pokemon::GetType(){
    return m_type;
}

// Returns health
int Pokemon::GetHealth(){
    return m_health;
}

// Returns type of Pokemon this Pokemon is strong against
string Pokemon::GetStrong(){
    return m_strong;
}

// Sets health of pokemon
void Pokemon::SetHealth(int newHealth){
    m_health = newHealth;
}

// Sets the pointer to the next Pokemon in the list
void Pokemon::SetNext(Pokemon* pokemonPointer){
    m_next = pokemonPointer;
}

// Overloaded print statement for pokemon
ostream &operator << ( ostream &output, Pokemon &P) {

    output << left << "Index: " << setw(3)<< P.GetIndex() ;
    output << left << "  Name: " << setw(11) << P.GetName();
    output << left << "  Type: " << setw(10) << P.GetType();
    output << left << setw(4) << " Health: " << P.GetHealth();

    return output;
}
