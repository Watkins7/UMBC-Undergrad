/*
** File: Game.cpp
** Project: CMSC 202 Project 3, Spring 2020
** Author: William Atkins
** Date: 3/30/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a driver for the Pokemon Project 3 in CMSC 202 @ UMBC
** It runs all the functions and returns the result of the game back to proj3.cpp
*/

#include "Game.h"
Game::Game(string filename){

    // Set file name in game
    m_filename = filename;

    // Create dynamically allocated lists
    m_list = new PokemonList;
    m_userPocket = new PokemonList;
    m_enemyPocket = new PokemonList;

}

// Destructor
Game::~Game() {

    // Im starting to think that this is not needed since they are not dynamically allocated
    delete m_list;
    m_list = NULL;

    delete m_enemyPocket;
    m_enemyPocket = NULL;

    delete m_userPocket;
    m_userPocket = NULL;


}

void Game::LoadFile() {

    int counter = 0; // Current Counter
    string name, type, strong, newIndex; // Variables in the file
    int index; // Current Index

    // Open file
    ifstream inputFile;
    inputFile.open(m_filename);

    // From 0 to a max_size, input a material from a file
    // Goes until PROJ2_SIZE
    for (int i = 0; i < PROJ3_SIZE; i++){

        // How to gather information from the first line
        inputFile >> index;
        getline(inputFile,name,',');
        getline(inputFile,name,',');
        getline(inputFile,type,',');
        getline(inputFile,strong,'\n');

        // Add a new pokemon to "m_list" linked list
        Pokemon *newPokemonPtr = new Pokemon(index, name, type, strong);

        // Up counter
        counter++;

        // Insert the pokemon in the list
        m_list->InsertEnd(newPokemonPtr);

    }

    // Close file
    inputFile.close();


}

// Loads file into linked list, m_list
// m_userPocket is populated
// m_enemyPocket is populated
int Game::Start() {

    int randomNumber; // Random Number
    int enemyCounter = 0; // Number of enemy pokemon

    // Load file
    LoadFile();

    // Make m_userPocket team
    ChooseTeam();

    // Display m_userPocket team
    cout << "-----------------------------" << '\n' <<
        "Your Team:" << endl;
    m_userPocket->Display();
    cout << "-----------------------------" << '\n';
    cout << "Enemy Team:" << '\n';

    // Make m_enemyPocket team
    // Run a for loop to make enemy team
    while (enemyCounter < NUM_TEAM){

        // Gets us a random number from 1 - 151
        randomNumber = rand() % PROJ3_SIZE;

        // If the index exists
        if (m_list->Exist(randomNumber)) {

            // Then transfer the pokemon from m_list to m_enemyPocket
            m_list->Transfer(randomNumber,m_enemyPocket);

            // Have m_list remove the transfered pokemon
            m_list->Remove( randomNumber );

            // Up number of enemy pokemon that have been obtained
            enemyCounter++;

        }

    }

    // Display m_enemeyPocket
    m_enemyPocket->Display();

    // Run the battle, then return the results to main
    return Battle();
}

// Runs the menu and returns user's response
int Game::Menu() {

    // Gets user's answer
    int answer = -1;

    // Display menu
    cout << "CPU's Pokemon: " << m_enemyPocket->GetHead()->GetName() << " ("
        << m_enemyPocket->GetHead()->GetType() << ":" << m_enemyPocket->GetHead()->GetHealth()
        << " health)" << endl;
    cout << "Your Pokemon:" << m_userPocket->GetHead()->GetName() << " ("
        << m_userPocket->GetHead()->GetType() << ":" << m_userPocket->GetHead()->GetHealth()
        << " health)" << endl;
    cout << "--------------------------------------------------" << '\n';
    cout << "Menu:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Swap" << endl;
    cout << "3. Forfeit" << endl;
    cout << "--------------------------------------------------" << '\n';

    // Get answer
    cin >> answer;

    // Keep asking for an answer that is betwen 1-3
    while (answer < 1 or answer > 3) {

        cout << "Please enter a valid choice: ";
        cin >> answer;
        cout << endl;

    }

    // return answer
    return answer;

}

// Returns an int on wheter the user or cpu won
int Game::Battle() {

    int caseDecision; // variable deals decisions from the menu function
    int attackResult; // varaible deals with information about what happens after a attack
    int round = 1; // variable keeps track of the round

    // Techical while loop condition is never met, but it runs the game until...
    // The user still has an active pokemon
    while (m_userPocket->GetHead()->GetHealth() > 0) {

        // Cout round information
        cout << "--------------------------------------------------" << '\n';
        cout << "Round " << round << ":" << '\n';

        // Print menu, function returns an int, case statement below will evaluate the int
        caseDecision = Menu();

        // switch statement for what was chosen during the menu
        switch (caseDecision){

            // Attack Case
            case 1:

                // Pass enemy pokemon to attack, get back result
                attackResult = m_userPocket->Attack(m_enemyPocket);

                // if statement for attack results
                if (attackResult == 2)
                {
                    // If the user's pokemon has died
                    if (m_userPocket->GetHead()->GetHealth() <= 0) {
                        cout << "Your pokemon has been defeated!" << endl;
                        m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());

                        // Ask for replacement pokemon
                        if ( m_userPocket->GetSize() >  1 )
                            m_userPocket->SwapPokemon();

                        // Tell user if they are on their last pokemon
                        else if ( m_userPocket->GetSize() == 1 ) {
                            cout << "YOU ARE ON YOUR LAST POKEMON! YOU CANNOT SWITCH POKEMON!" << endl;
                        }

                    }

                    // If the enemy pokemon has dies
                    if (m_enemyPocket->GetHead()->GetHealth() <= 0) {
                        cout << "The enemy Pokemon has been defeated!" << endl;
                        m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());
                    }

                }

                // Check winning conditions after combat
                // Check to see if CPU wins
                if (m_userPocket->GetSize() == 0) {
                    cout << "You have no more usable Pokemon left." << endl;
                    return 2;
                }


                // Check to see if user wins
                if (m_enemyPocket->GetSize() == 0) {
                    cout << "The CPU has no more usable Pokemon left." << endl;
                    return 1;
                }

                // Up round count
                round++;

                break;

            // Swap case
            case 2:
                m_userPocket->SwapPokemon();
                break;

            // Forfeit Case
            case 3:
                cout << "You have chosen to quit the battle" << endl;
                return 2;
                break;

            default:
                cout << "The number entered does not match any choices, please enter another number." << endl;
                break;

        };


    } // End of while loop

    // By deafult return 0 for error
    return 0;

}

// Loops as many times as the user is allowed to have pokemon
// Takes pokemon from m_list and puts them into m_userPocket
void Game::ChooseTeam() {

    int index; // index of pokemon wanted
    int counter = 0; // counter of total pokemon

    // for loop to run as many times as NUM_TEAM (number of pokemon on a team)
    while ( counter < NUM_TEAM ){

        // Cout prompt about possible pokemon
        cout << "Here is a list of Pokemons you can choose from:" << '\n'
             << "----------------------------------------" << '\n';
        m_list->Display();
        cout << "----------------------------------------" << '\n';
        cout << "Pick a pokemon by enter the index (" << NUM_TEAM - m_userPocket->GetSize()
             << " left):" << endl;

        // Get index wanted
        cin >> index;

        // Keep asking until you get a index that is valid
        while ( !m_list->Exist(index) ) {
            cout << "That is not a valid pokemon index.  Please try again." << endl;
            cin >> index;
        }

        // If the index exists in the master_list...
        if (m_list->Exist(index)) {

            // Transfer the pokemon from m_list to m_userPocket by comparing index chosen
            m_list->Transfer(index, m_userPocket);
            // Remove chosen index/pokemon in m_list
            m_list->Remove(index);

            //Up counter of how many pokemon were chosen
            counter++;

        }


    } // End of While loop

} // End of function