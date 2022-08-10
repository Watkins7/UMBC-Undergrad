/*
** File: Driver.cpp
** Project: CMSC 202 Project 2, Spring 2020
** Author: William Atkins
** Date: 3/5/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is part of the Subnautica in CMSC 202 @ UMBC
    Diver contains functions and programs to change, display, and check materials
*/

#include "Diver.h"

// Diver Default Constructor
Diver::Diver() {}

// Diver Overload Constructor
Diver::Diver(string name) {

   // Diver being constructed and sets his name accordingly
   SetName(name);
}

// Sets name of the diver
void Diver::SetName(string name) {

   // Sets the name of the Diver
   m_myName = name;
}

// Returns the name of the diver
string Diver::GetName() {

   return m_myName;
}

// Passes a material and adds it to the diver's array
void Diver::AddMaterial(Material newMaterial) {

   // Set the last_known_number_of_material in the array...
   // ... equal to the new material passed
   m_myMaterials[m_numMaterials] = newMaterial;

   // Increase the number of known materials
   m_numMaterials++;

   // Print how many materials loaded once we reach PROJ2_SIZE - 1
   if (m_numMaterials == PROJ2_SIZE - 1){
       cout << m_numMaterials + 1 << " materials loaded." << endl;
   }

}

// Will display diver's materials to the screen
void Diver::DisplayMaterials() {

   // For loop to display all the materials in the Diver's Array
   for (int i = 0; i < PROJ2_SIZE; i++){
       cout << i+1 << ". " << m_myMaterials[i].m_name << " "
           << m_myMaterials[i].m_quantity << endl;
   }

}

// Will increment a material
void Diver::IncrementQuantity(Material materialToUp) {

   // Get index of material to up
   int index = (CheckMaterial(materialToUp));

   // Up the material in m_myMaterial array at the corresponding index
   m_myMaterials[index].m_quantity += 1;

   // Simple print statement for display raw materials found
   if (materialToUp.m_type == "raw") {

       cout << materialToUp.m_name << " Found!  " << m_myName << " now has " <<
           m_myMaterials[index].m_quantity << " " << materialToUp.m_name << "!" << endl;
   }

   // Simple print statement to display that the diver has built something
   else {

       cout << m_myName << " has built a " << materialToUp.m_name << "!  "
           << m_myName << " now has " << m_myMaterials[index].m_quantity
           << " " << materialToUp.m_name << "!" << endl;
   }


}

// Decrement's the chosen's material quantity
bool Diver::DecrementQuantity(Material myMaterial) {

   // Get index number of material to decrement
   int index = CheckMaterial(myMaterial);

   // Decrease according index in the diver's material array
   m_myMaterials[index].m_quantity--;

   // Because we have to return something, even when it doesnt mean a thing
   return true;
}

// Will return T or F based if the materials being passed have enough quantity
bool Diver::CheckQuantity(Material materialA, Material materialB) {

   // Switch materialA into materials in the diver array
   int index = CheckMaterial(materialA);
       materialA = m_myMaterials[index];

   // Switch materialB in the material in the diver array
   index = CheckMaterial(materialB);
       materialB = m_myMaterials[index];


   // If materials are different then we must have at least 1 quantity for both
   // Returning true means that we have enough quantity
   if (materialA.m_name != materialB.m_name) {
       if (materialA.m_quantity - 1 >= 0) {
           if (materialB.m_quantity - 1 >= 0)

               return true;
       }
   }

   // If both materials are the same, we must have at least 2 quantity
   // Returning true means that we have enough quantity
   else if (materialA.m_name == materialB.m_name) {
       if (materialA.m_quantity - 2 >= 0)

           return true;
   }

   // By defualt return false
   return false;

}

// Will return a sum of the diver's depth
int Diver::CalcDepth() {

   int sum = 0;

   // For loop to calculate depth
   for (int i = 0; i < PROJ2_SIZE; i++) {
       sum += m_myMaterials[i].m_quantity * m_myMaterials[i].m_depth;
   }

   // Return diver's depth
   return sum;
}

// Returns the index number of the material passed
int Diver::CheckMaterial(Material materialToCheck) {

   // for loop looks for the name is in m_myMaterials array, it will return it's index number
   for (int i = 0; i < PROJ2_SIZE; i++){
       if (materialToCheck.m_name == m_myMaterials[i].m_name) {
           return i;
       }
   }

   // By default return -1
   return -1;

}

// Passes a index number, will return the material of the chosen index
Material Diver::GetMaterial(int indexNumber) {

   return m_myMaterials[indexNumber];
}