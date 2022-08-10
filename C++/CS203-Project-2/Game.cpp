/*
** File: Game.cpp
** Project: CMSC 202 Project 2, Spring 2020
** Author: William Atkins
** Date: 3/5/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is part of the Subnautica in CMSC 202 @ UMBC
** Game.cpp that acts as a driver and runs functions for project 2
*/

#include "Game.h"

// Default Constructor
Game::Game() {

   // Loads game title
   GameTitle();

   // load materials into "Game Material" array
   // Also print how many materials loaded
   LoadMaterials();

   // Set Diver's material array
   // For loops populates the Diver's material array by passing each
   //...material one at a time
   for (int i = 0; i < PROJ2_SIZE; i++){
       m_myDiver.AddMaterial(m_materials[i]);
   }

   // Get Diver's name from user
   cin.clear();
   string name;
   cout << "What is your player's name?:  ";
   getline(cin,name);
   cin.clear();

   // Set member variable "Diver's name" through class setter function
   m_myDiver.SetName(name);


}

// Function that runs the entire game
void Game::StartGame() {

   bool inGame = true; // Variable to keep game running until win conditions have been met
   int answer; // User's response

   // Do-while loop to the run the game until the user wins
   do {

       // Run the MainMenu() function to display options
       // ...and get's the user's answer
       answer = MainMenu();

       // Case statement for user's answer
       switch (answer) {

           // Display Materials
           case 1:

               DisplayMaterials();

               break;

           // Search for Raw Materials
           case 2:

               SearchMaterials();
               break;

           // Attempt to Merge Materials
           case 3:

               CombineMaterials();
               break;

           // See Score
           case 4:

               CalcScore();
               break;

           // Quit
           case 5:

               cout << "Thanks for playing Subnautica! This was your score!" << endl;
               CalcScore();
               inGame = false;
               break;

           // User enters a non-menu number
           default:

               cout << "Opps. Not an option." << endl;
               break;
       }

       // Win condition automatic for winning the game, if user's depth exceeds or equals max depth
       if (m_myDiver.CalcDepth() >= MAX_DEPTH){
           cout << endl << m_myDiver.GetName() << " has the ability to reach the maximum depth!" <<
               "  You have won the game!" << '\n' << endl;
           CalcScore();

           // Break ingame while loop
           inGame = false;
       }

   } while (inGame); // Do while to keep the game running

}

// Loads materials from a file
void Game::LoadMaterials() {

   // Open PROJ2_DATA file
   ifstream inputFile;
   inputFile.open(PROJ2_DATA);

   int counter = 0; // Counter
   string name, type, material1, material2; // Variables in the file
   int depth; // Variable in the file


   // From 0 to a max_size, input a material from a file
   // Goes until PROJ2_SIZE
   while (counter < PROJ2_SIZE){

       // How to gather information from the first line
       getline(inputFile,name,',');
       getline(inputFile,type,',');
       getline(inputFile,material1,',');
       getline(inputFile,material2,',');
       inputFile >> depth;

       // Add a new material to "m_material" Array
       m_materials[counter] = Material(name, type, material1,
                   material2, 0, depth);

       // Removes new line
       inputFile.ignore(256,'\n');

       // End up counter
       counter++;
   }

   // Close file
   inputFile.close();

}

void Game::DisplayMaterials() {

   // Run the Diver function to display materials
   m_myDiver.DisplayMaterials();

}

// Displays the main menu
int Game::MainMenu() {

   cout << endl << "What would you like to do?" << endl;
   cout << "1. Display your Diver's Materials" << endl;
   cout << "2. Search for Raw Materials" << endl;
   cout << "3. Attempt to Merge Materials" << endl;
   cout << "4. See score" << endl;
   cout << "5. Quit" << endl;

   // Get answer and verify response is valid
   int answer;
   cin >> answer;

   // Return int that is our answer for the menu
   return answer;
}

// Gives us a random raw material
void Game::SearchMaterials() {

   int randomNumber; // Our chosen random index

   // Chose a random number "0 - number of materials in the file - 1"
   // And make sure that the type is "raw"
   do {
       randomNumber = rand() % PROJ2_SIZE;
   } while (m_materials[randomNumber].m_type != "raw");

   // Now that we have our random material that is raw
   // We can pass that material to the diver to increment
   m_myDiver.IncrementQuantity(m_myDiver.GetMaterial(randomNumber));

}

// Choice is the user's answer, and we are "returning" by refrence the position
// ...of the material that we want to combine
void Game::RequestMaterial(int &choice) {

   // Sanatize input
   cin.clear();
   cin.ignore(256, '\n');

   // While input is not between 1 and PROJ2_SIZE
   // Try to get a valid material index
   do {
       cout << "Which materials would you like to merge?" << endl;
       cout << "To list known materials enter -1" << endl;
       cin >> choice;

       // If they chose -1, then display the menu of items
       if (choice == -1)
           m_myDiver.DisplayMaterials();

   } while (choice < 1 or choice > PROJ2_SIZE);

   // Change choice into the actual index location
   choice -= 1;

}

// This should be the main driver to combine materials
void Game::CombineMaterials() {

   int materialOneIndexNumber = -1; // Material 1 index
   int materialTwoIndexNumber = -1; // Material 2 index
   int recipeIndexNumber = -1; // Recipe index
   bool decrement; // Needed for decrement function

   // Request and change the index number of the two materials that Diver wants to combine
   RequestMaterial(materialOneIndexNumber);
   RequestMaterial(materialTwoIndexNumber);

   // Search for a reciepe with the two materials and their valid index locations
   recipeIndexNumber = SearchRecipes(m_materials[materialOneIndexNumber].m_name,
           m_materials[materialTwoIndexNumber].m_name);

   // If recipeIndexNumber is -1, then the recipe does not exist
   // ...and we stop trying to merge materials
   if (recipeIndexNumber == -1)
       return;

   // Check to see if recipe is unique and already made, it is then we can
   //...quit trying to merge materials
   // Condtions: First condition lets us know if item is unique,
   // Second condition: GetMaterials will tell us if we have a quantity already
   if ( m_materials[recipeIndexNumber].m_type == "unique" and
       m_myDiver.GetMaterial(recipeIndexNumber).m_quantity > 0) {

       cout << "You can only have one of this unique item, you cannot craft another." << endl;

       return;
   }

   // Checks to see in both materials being merged have enough quantity to forge
   // If they do then we can increment the material that the diver wants
   // if statement: Triggers true if Diver has both materials and quantity
   // Then we can increase and decrease material
   if (m_myDiver.CheckQuantity(m_myDiver.GetMaterial(materialOneIndexNumber),
           m_myDiver.GetMaterial(materialTwoIndexNumber))){

           // Print what the diver is making and with which materials
           cout << m_materials[materialOneIndexNumber].m_name << " combined with " <<
               m_materials[materialTwoIndexNumber].m_name << " to make " <<
               m_materials[recipeIndexNumber].m_name << "!" << endl;

           // Increment and Decrement according materials
           m_myDiver.IncrementQuantity(m_myDiver.GetMaterial(recipeIndexNumber));
           decrement = m_myDiver.DecrementQuantity(m_myDiver.GetMaterial(materialOneIndexNumber));
           decrement = m_myDiver.DecrementQuantity(m_myDiver.GetMaterial(materialTwoIndexNumber));

           // Need so we dont get warnings during make
           if (decrement)
               cout << "";
   }


   // In none of the above if statements have triggered,
   // then that means we do not have enough materials
   else {

       // Same material print statement
       if (m_materials[materialOneIndexNumber].m_name ==
            m_materials[materialTwoIndexNumber].m_name) {
           cout << "You do not have enough " << m_materials[materialOneIndexNumber].m_name <<
               " to attempt that merge." << endl;

       }

       // Different material print statement
       else {
           cout << "You do not have enough " << m_materials[materialOneIndexNumber].m_name <<
                " or " << m_materials[materialTwoIndexNumber].m_name <<
                " to attempt that merge." << endl;

       }

   } // End of else

}

// Looks for a valid recipe by comparing material names
// Names of the two materials being combined are passed
int Game::SearchRecipes(string materialA, string materialB) {

   // For the whole material array
   for (int i = 0; i < PROJ2_SIZE; i++){

       // If a material needs both materialA and materialB (in that order)
       //... return the material index, which will be the recipe index
       if (m_materials[i].m_material1 == materialA and
       m_materials[i].m_material2 == materialB) {
           return i;
       }

       // Else, search the reverse, if a material needs...
       // ...materialB and materialA (in that order)
       //... return the material index, which will be the recipe index
       else if (m_materials[i].m_material1 == materialB and
       m_materials[i].m_material2 == materialA) {
           return i;
       }
   }

   // else, by default if no recipe is found return -1 to indicate
   // that nothing was found
   cout << "Sorry, the recipe that you are looking for does not exist." << endl;
   return -1;
}

// Output how the user is doing
void Game::CalcScore() {

   // Use diver's function to calculate the depth
   int userScore = m_myDiver.CalcDepth();

   // Cout apporiate information
   cout << "***The Diver***" << endl;
   cout << "The Great Diver " << m_myDiver.GetName() << endl;
   cout << "Maximum Depth: " << MAX_DEPTH << endl;
   cout << "Current Depth: " << userScore << endl;
}