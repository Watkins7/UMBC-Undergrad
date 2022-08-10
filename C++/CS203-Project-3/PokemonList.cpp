/*
** File: PokemonList.cpp
** Project: CMSC 202 Project 3, Spring 2020
** Author: William Atkins
** Date: 3/30/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a linked list class that can contain pokemon for the Pokemon Project 3 in CMSC 202 @ UMBC
*/

#include "PokemonList.h"

// Name: PokemonList
// Desc - Default constructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Creates an empty PokemonList (linked list)
PokemonList::PokemonList(){

    m_size = 0;
    m_head = nullptr;

}

// Name: ~PokemonList
// Desc - Destructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Clears out a PokemonList (linked list)
PokemonList::~PokemonList() {

    // Create a temporary pointer
    Pokemon *current;
    Pokemon *previous = m_head;

    // Iterate through the list
    while (previous != nullptr) {

        // Move current
        current = previous->GetNext();

        // Delete Previous, dynamically allocated pokemon
        delete previous;
        previous = NULL;

        // Move previous to current
        previous = current;
    }
}

// Name: SwapPokemon
// Desc - Allows user to move a Pokemon from any position into the first position
// Special cases: Empty list, Pokemon chosen at m_head or choice doesn't exist
// Preconditions - Linked list is populated
// Postconditions - User selects a Pokemon and it is moved into the first position
void PokemonList::SwapPokemon() {

    // Temporary variables to hold information
    int index;  // Stores index
    Pokemon *temp1 = nullptr; // Will store m_head
    Pokemon *temp2 = nullptr; // Will store what m_head is pointing to
    Pokemon *temp3 = nullptr; // Will store current pointer
    Pokemon *temp4 = nullptr; // Will store what current pointer is pointing to

    Pokemon *tempPrevious = GetHead(); // Previous pokemon
    Pokemon *tempCurrent = GetHead(); // Current pokemon

    // Check to see if user has enough pokemon to switch with
    if ( GetSize() <= 1 ){
        cout << "You do not have any pokemon to switch with.  Good Luck!" << endl;
        return;
    }

    // Do this while the index is invalid, or does not exist
    // This Loop will keep asking the user for a pokemon to switch with
    do {

        // Ask user what pokemon they would like
        cout << "Which Pokemon would you like to choose? (Enter the index#)" << endl;
        Display();
        cin >> index;

        // If the pokemon they chose was already fighting
        if (index == m_head->GetIndex()) {

            cout << "Your pokemon is already battling.  Your choice was head." << endl;
            return;

        }

        // Check to see if pokemon is in the list, if not then cout an error
        if (!Exist(index)) {

            cout << "Opps, we could not find the pokemon you are looking for." << endl;

        }

    }   while (!Exist(index)); //End of do while, searching for a valid index

    // This far means that the pokemon chosen is somewhere in the list
    // While loop to traverse the pokemonlist
    while (tempCurrent != nullptr) {

        // Set previous equal to the current
        tempPrevious = tempCurrent;

        // Move current to the next pokemon
        tempCurrent = tempCurrent->GetNext();

        // If tempCurrent is equal to the index we are looking for then...
        if ( tempCurrent->GetIndex() == index ) {

            // Store pointing information
            // See variable declarations for information
            temp1 = m_head;
            temp2 = m_head->GetNext();
            temp3 = tempCurrent;
            temp4 = tempCurrent->GetNext();

            // Case if index wanted is RIGHT NEXT to m_head
            if (temp2->GetIndex() == temp3->GetIndex()){

                // Set m_head and currentTemp to their new respected pokemon
                m_head = temp3;
                tempCurrent = temp1;

                // Change pointers for tempCurrent and m_head to point appropriately
                m_head->SetNext(tempCurrent);
                tempCurrent->SetNext( temp4 );

                return;
            }

            // Else, if the pokemon being switched are not next to each other...
            // ...we can switch like this
            // Have tempCurrent become the active pokemon (m_head)
            tempCurrent = temp1;

            // Have the previous pokemon point to the old m_head
            tempPrevious->SetNext( temp1 );

            // Have the old m_head point to where the currentIndex was pointing to
            tempCurrent->SetNext( temp4 );

            // Have new m_head become tempCurrent
            m_head = temp3;

            // Have the new m_head point to where the old m_head used to point
            m_head->SetNext( temp2 );

            //VERY LAST THING, QUIT FUNCTION
            return;

        } // End of if statement

    } // End of while loop

}

// Name: InsertEnd
// Desc - Inserts an already dynamically allocated Pokemon to end of linked list
// Preconditions - PokemonList already created
// Postconditions - The passed Pokemon appears at the end of the list
void PokemonList::InsertEnd(Pokemon *newPokemon) {

    // If m_head has nothing to point at, then point it to the pokemon passed
    if (m_head == nullptr)
        m_head = newPokemon;

    else {

        // Create a tempoary pointer pokemon starting at m_head
        Pokemon *temp = m_head;

        // Traverse list until you reach a pokemon that points to null
        while (temp->GetNext() != NULL) {
            temp = temp->GetNext();
        }

        // Have the last pokemon in the list point to the newPokemon
        temp->SetNext(newPokemon);

    }

    // Increase size of the list
    m_size++;
}

// Name: Display
// Desc - Iterates over PokemonList and displays each Pokemon formatted as in output
// Preconditions - PokemonList already created and has Pokemon
// Postconditions - Displayed Pokemon information
void PokemonList::Display() {

    // If the pokemon list is empty
    if (m_size == 0)
        cout << "The linked list is empty" << endl;

    // If the pokemonlist has pokemon
    else {

        // Create a temporary pointer
        Pokemon *temp = m_head;

        // Iterate through the list
        // For some reason I chose to iterate by size, and I'm too tired to rewrite code that works fine
        // So if it bothers you, just believe it is a while loop until it reaches nullptr
        for (int i = 0; i < m_size; i++){

            // Output data
            cout << *temp << endl;

            // Change temp pointer, to next pokemon
            temp = temp->GetNext();

        }

        // Delete new dynamically allocated pokemon
        temp = nullptr;
        delete temp;

    }
}

// Name: GetSize
// Desc - Returns the size of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the size of the linked list
int PokemonList::GetSize() {
    return m_size;
}

// Name: Transfer
// Desc - Searches for a Pokemon with a specific index. If found,
// creates a new Pokemon and copies it into the PokemonList passed in
// Preconditions - int is the index of the desired Pokemon and
// PokemonList is the destination
// Postconditions - Adds new Pokemon to the destination list and removes it from
// the source
void PokemonList::Transfer(int index, PokemonList *pokemonTransferList) {

    // Create a new dynamically
    Pokemon *temp = m_head;

    // For loop that will run through all of a list and compare pokemon until a similar index is found
    while (temp->GetIndex() != index) {

        // Set the next temp
        temp = temp->GetNext();

    }

    // Add a new pokemon to linked list
    // Get information and create a new dynamically allocated object, like a good old boy
    string name = temp->GetName();
    string type = temp->GetType();
    string strong = temp->GetStrong();
    Pokemon *newPokemonPtr = new Pokemon(index, name, type, strong);

    // Once index is found, add that pokemon to the pokemonTransferList
    pokemonTransferList->InsertEnd(newPokemonPtr);


}

// Name: GetHead
// Desc - Returns the Pokemon at the head of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the Pokemon at the head of the linked list
Pokemon* PokemonList::GetHead() {
    return m_head;
}

// Name: Remove (int)
// Desc - Searches for a Pokemon with a specific index. If found,
// removes it from the linked list
// Preconditions - int is the index of the desired Pokemon
// Postconditions - Removes Pokemon from linked list
// Removes a chosen index
// Given that you have a populated list
void PokemonList::Remove(int index) {

    // Create new temporary allocated pokemon
    Pokemon *currentTemp = m_head;
    Pokemon *previousTemp = m_head;

    // One-time check to see if the first pokemon is the chosen index
    // Check to see in m_head is the index wanted
    if (currentTemp->GetIndex() == index){

        // Move m_head to the next pokemon
        m_head = currentTemp->GetNext();

        // Delete dynamically allocated pointer (that is m_head)
        delete currentTemp;
        currentTemp = nullptr;

        // Lower size of the list
        // Then return since we removed the pokemon
        m_size--;
        return;
    }

    // Check rest of list's indexs
    // Move through list, find index, then remove the pokemon, then reattach list;
    // We do this while we are currently not on the end
    while (currentTemp != nullptr) {

        // First thing, move previousTemp to currentTemp pokemon marker
        previousTemp = currentTemp;

        // Move currentTemp pokemon marker over to the next pokemon
        currentTemp = currentTemp->GetNext();

        // If the currentTemp pokemon has the index we want, then...
        if (currentTemp->GetIndex() == index){

            // Reattach list by skipping over currentTemp
            // Link previousTemp to the pokemon that currentTemp was pointing to
            previousTemp->SetNext(currentTemp->GetNext());

            // Delete currentTemp, the pokemon that was wanted to be removed
            delete currentTemp;
            currentTemp = nullptr;

            // Return after modifying list
            m_size--;
            return;

        }

    }

}

// Name: Attack(PokemonList)
// Desc - Passes an enemy pocket to the user's pocket to attack
// User always attacks the enemy Pokemon in this game
// Preconditions - This list is populated and enemy list is populated
// Postconditions - Does damage to the user Pokemon and enemy Pokemon
// and updates their health. Returns 2 if enemy Pokemon is less than 0
// Returns 2 if user's health is less than 0 else returns 0.
// Passes Enemy PokemonList to attack
int PokemonList::Attack(PokemonList *m_enemeyPokemonList) {

    // If the user is strong againist the CPU pokemon
    if ( GetHead()->GetStrong() == m_enemeyPokemonList->GetHead()->GetType() ) {
        m_enemeyPokemonList->GetHead()->SetHealth(m_enemeyPokemonList->GetHead()->GetHealth() - STRONG_DAMAGE);
        cout << "Critical Damage!  CPU pokemon took " << STRONG_DAMAGE << " damage!" << endl;
    }

    // Regular Damage to the CPU pokemon
    else {
        m_enemeyPokemonList->GetHead()->SetHealth( m_enemeyPokemonList->GetHead()->GetHealth() - DAMAGE2ENEMY );
        cout << "CPU's pokemon took " << DAMAGE2ENEMY << " damage" << endl;
    }

    // If the enemy pokemon is dead, then return back to main menu
    if (m_enemeyPokemonList->m_head->GetHealth() <= 0)
        return 2;

    // Else, the CPU can do damage to the user
    else {

        // Critical Damage to user pokemon
        if (m_enemeyPokemonList->GetHead()->GetStrong() == GetHead()->GetType()) {
            GetHead()->SetHealth( GetHead()->GetHealth() - STRONG_DAMAGE );
            cout << "Critical Damage! Your pokemon took " << STRONG_DAMAGE << " damage!" << endl;
        }

        // Regular Damage to user pokemon
        else {
            GetHead()->SetHealth( GetHead()->GetHealth() - DAMAGE2USER );
            cout << "Your pokemon took " << DAMAGE2USER << " damage" << endl;
        }

        // Returning if the user pokemon is knocked out
        if ( GetHead()->GetHealth() <= 0 )
            return 2;

        // Returning if the user pokemon is still active and enemy pokwmon is still alive
        else
            return 0;

    }


}

// Name: Exist(int)
// Desc - Iterates through linked list looking for a specific index of a Pokemon
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns true if found else false
// Checks to see if list has a chosen index
bool PokemonList::Exist(int index) {

    // Create a new currentTemp pokemon to help transverse the list
    Pokemon* currentTemp = m_head;

    // While loop to find is a chosen index exists in a list
    while (currentTemp != nullptr){

        // If you find the index, return true
        if (currentTemp->GetIndex() == index) {

            // We found the pokemon!  Return that information
            return true;
        }

        // Move pointer to next pokemon in the list
        currentTemp = currentTemp->GetNext();

    }

    // By default, return false, we could not find the pokemon!
    return false;

}