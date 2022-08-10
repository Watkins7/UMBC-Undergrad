/*
** File: csr.cpp
** Project: CMSC 341 Project 1, Fall 2020
** Author: William Atkins
** Date: 9/29/20
** Email: watkins7@umbc.edu
** Description: This is a csr.cpp for proj1 in 341 Fall 2020
** This makes a csr matrix, and does other neat features
*/

// CMSC 341 - Fall 2020 - Project 1
#include "csr.h"

CSR::CSR(){
    /***********************************
     *      To be implemented
     * ********************************/
     m_m = 0;
     m_n = 0;
     m_nonzeros = 0;
     m_row_index = nullptr;
     m_col_index = nullptr;
     m_values = nullptr;
     m_next = nullptr;


}

CSR::~CSR(){
    /***********************************
     *      To be implemented
     * ********************************/
     delete[] m_row_index;
     m_row_index = nullptr;
     delete[] m_col_index;
     m_col_index = nullptr;
     delete[] m_values;
     m_values = nullptr;

}

CSR::CSR(const CSR & rhs){
    /***********************************
     *      To be implemented
     * ********************************/

    // If Object is empty
    if (!rhs.m_row_index && !rhs.m_col_index && !rhs.m_values)
    {

        // Set this object to empty
        m_values = nullptr;
        m_col_index = nullptr;
        m_row_index = nullptr;
        m_next = nullptr;
        m_n = 0;
        m_m = 0;
        m_nonzeros = 0;

        return;
    }

    // Copy passed CSR
    // Set new arrayValues
    m_m = rhs.m_m;
    m_n = rhs.m_n;
    m_nonzeros = rhs.m_nonzeros;

    // Make new arrays with correct sizes
    m_row_index = new int[m_m+1];
    m_col_index = new int[m_nonzeros];
    m_values = new int[m_nonzeros];

    // FIX M_NEXT, have it point to null by default
    m_next = nullptr;

    // Deep copy arrays
    // Set Column numbers
    for (int i = 0; i < m_nonzeros; i++){

        this->m_col_index[i] = rhs.m_col_index[i];
    }

    // Set Value numbers
    for (int i = 0; i < m_nonzeros; i++){

        this->m_values[i] = rhs.m_values[i];
    }

    // Set Row numbers
    for (int i = 0; i < m_m+1; i++){

        this->m_row_index[i] = rhs.m_row_index[i];

    }


}

void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!" << endl;
    cout << endl;

}

void CSR::clear(){
    /***********************************
     *      To be implemented
     * ********************************/

    // Clear data
    delete[] m_row_index;
    m_row_index = nullptr;
    delete[] m_col_index;
    m_col_index = nullptr;
    delete[] m_values;
    m_values = nullptr;

    // Clear values
    m_nonzeros = 0;
    m_n = 0;
    m_m = 0;

}

bool CSR::empty() const{
    /***********************************
     *      To be implemented/
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // if m_values still points to null, return true meaning that the list csr has nothing
    if (!m_values)
        return true;
    else
        return false;
}

void CSR::compress(int m, int n, int array[], int arraySize){
    /***********************************
     *      To be implemented
     * ********************************/

    // If there is data in here, then delete all old data
    if (m_values || m_col_index || m_row_index) {
        m_m = 0;
        m_n = 0;
        m_nonzeros = 0;
        delete[] m_row_index;
        m_row_index = nullptr;
        delete[] m_values;
        m_values = nullptr;
        delete[] m_col_index;
        m_col_index = nullptr;
    }

    // Edge case, for zero x zero matrix
    if (m == 0 and n == 0){
        return;
    }

     // Set rows (m)
     m_m = m;
     // Create blank "m" size row array
     m_row_index = new int[m+1];
     // Set columns (n)
     m_n = n;
     // Set number of m_nonzeros = 0
     m_nonzeros = 0;

     // Find the number of non-zero number
     for (int i = 0; i < m*n && i < arraySize; i++) {
         if ( array[i] != 0)
             m_nonzeros++;
     }

     // Create blank "m_nonzero" size column array
     m_col_index = new int[m_nonzeros];
     // Create a blank "m_nonzero" size m_value array, to hold actual values
     m_values = new int[m_nonzeros];

     // Index tracker for m_values
     int j = 0;

     // Create a for loop that inputs the non-zero numbers
     for (int i = 0; i < m*n && i < arraySize; i++) {

         // Check each element of the passed array
         // See if it is non-zero
         if ( array[i] != 0) {

             // Copy value over
             m_values[j] = array[i];

             // Up index tracker
             j++;
         }

     }


     // Code to populate arrays
     // Now we need to populate column and row arrays with their respectable numbers
     int arrayNumberTracker = 0; // Tracks which index we are at with the orginal array
     int columnTracker = 0; // Tracks current m_col_index[] index
     int rowTracker = 0; // Tracks current m_row_index[] index
     int currentNumbersFound = 0;  // Tracks number of nonzero items found


     // Special case for M * N > arraySize
     // Code that makes a big matrix from a small array
     if (m_m * m_n > arraySize){

         // Populate column array, Special case
         for (int i = 0; i < arraySize; i++){

             // If we find a non-zero number
             if (array[i] != 0){

                 // We record the location using the mod of # of columns
                 m_col_index[columnTracker] = i % m_n;
                 columnTracker++;
             }
         }

         // Populate the row array, Special case
         for (int i = 0; i < arraySize; i++) {

             // If we mod i with the row length and it loops back around to 0
             // Then we know when to record information
             if (i % m_m == 0){

                 m_row_index[rowTracker] = currentNumbersFound;
                 rowTracker++;
             }

             // If we find a nonzero number, up number of nonzeros found
             if (array[i] != 0){
                 currentNumbersFound++;
             }

         }

         // Fill in the rest of m_row_index
         for (int i = rowTracker; i < m_m+1; i++){
             m_row_index[i] = currentNumbersFound;
         }

         return;
     }

     // Populating code for all other type of arrays
     // For Loop works for correct array, and when making a smaller array;
     // For loop to run through number of rows
     for (int i = 0; i < m_m && currentNumbersFound <= m_nonzeros; i++){

         // Record number of numbers found on each row
         m_row_index[rowTracker] = currentNumbersFound;

         // For loop to run through number of columns
         for (int y = 0; y < m_n && currentNumbersFound <= m_nonzeros; y++) {

             // If we find a non-zero number!!
             if ( array[arrayNumberTracker] != 0) {

                 // Add to m_col_index which column that number was found
                 m_col_index[columnTracker] = y;

                 // Up columnTracker index
                 columnTracker++;

                 // Up that we found a number
                 currentNumbersFound++;
             }

             // Finally up the arrayTracker
             arrayNumberTracker++;
         }

         // Up that we went through 1 row
         rowTracker++;

     }

     // To get the last possible row numbers
     for (int i = rowTracker; i < m_m+1; i++)
         m_row_index[i] = currentNumbersFound;

}

int CSR::getAt(int row, int  col) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     // Check out of bounds
     if (row < 0 || row >= m_m || col < 0 || col >= m_n)
         throw out_of_range("Error: Element is out of bounds");

     // Else we are inbounds
     else {

         // Track which non zero value we are at
         int valueTracker = 0;
         int columnTracker = 0;

         // Make a 2d array
         int twoD_array[m_m][m_n];

         // Set 0 arrays
         for (int i = 0; i < m_m; i++)
             for (int j = 0; j < m_n; j++)
                 twoD_array[i][j] = 0;

         // Do this for each row
         for (int i = 0; i < m_m; i++) {

             // For the difference in the row matrix
             for (int k = 0; k < m_row_index[i + 1] - m_row_index[i]; k++) {

                 // Populate the 2d array
                 twoD_array[i][m_col_index[columnTracker]] = m_values[valueTracker];

                 // Update trackers
                 columnTracker++;
                 valueTracker++;
             }
         }

         // Bounds checking already done
         return twoD_array[row][col];

     }

}

bool CSR::operator==(const CSR & rhs) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // Check to see if there is any mismatch in the numbers
    if (this->m_m != rhs.m_m)
        return false;
    if (this->m_n != rhs.m_n)
        return false;
    if (this->m_nonzeros != rhs.m_nonzeros)
        return false;

    // Check columns for mismatches
    for (int i = 0; i < this->m_nonzeros; i++) {

        if (this->m_col_index[i] != rhs.m_col_index[i]) {
            return false;
        }
    }

    // Check values for mismatches
    for (int i = 0; i < this->m_nonzeros; i++){

        if (this->m_values[i] != rhs.m_values[i]){
            return false;
        }
    }

    // check rows for mismatches
    for (int i = 0; i < this->m_m; i++){
        if (this->m_row_index[i] != rhs.m_row_index[i]){
            return false;
        }

    }

    return true;

}

int CSR::sparseRatio(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     // If object is empty, return a zero sparse ratio
     if (empty()){
         cout << "This matrix is empty, so it will return a sparse ratio of 0" << endl;
         return 0;
     }

     // Return math equation
     return int (float(m_nonzeros) / float(m_n * m_m) * 100);
}
