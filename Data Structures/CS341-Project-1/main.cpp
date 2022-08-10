/*
** File: driver.cpp
** Project: CMSC 341 Project 1, Fall 2020
** Author: William Atkins
** Date: 9/29/20
** Email: watkins7@umbc.edu
** Description: This is a driver.cpp for proj1 in 341 Fall 2020
*/

#include <iostream>

#include "csrlist.h"

bool testEquality(CSR& a, CSR& b);
bool testEquality(CSRList& a, CSRList& b);

int main()
{
    try{

        cout << "Orginal Test | *******************************************************************************" << endl;
        CSR aCSR;
        int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        aCSR.compress(4,6,array1,24);//initialize object aCSR

        CSR bCSR(aCSR);//create bCSR using copy constructor
        CSR cCSR;
        int array2[] = {0,0,0,0,100,200,0,0,300};
        cCSR.compress(3,3,array2,9);//initialize object cCSR
        CSR dCSR(cCSR);//create dCSR using copy constructor

        CSRList aCSRList;//create aCSRList
        aCSRList.insertAtHead(aCSR);
        aCSRList.insertAtHead(cCSR);
        CSRList bCSRList;//create bCSRList
        bCSRList.insertAtHead(dCSR);
        bCSRList.insertAtHead(bCSR);

        cout << endl << "Dumping aCSRList:" << endl;
        aCSRList.dump();
        cout << endl << "Dumping bCSRList:" << endl;
        bCSRList.dump();

        if (testEquality(cCSR,dCSR)) cout << endl << "testEquality(cCSR,dCSR) passed!" << endl;
        else cout << endl << "testEquality(cCSR,dCSR) failed!" << endl;
        if (testEquality(aCSR,dCSR)) cout << endl << "testEquality(aCSR,dCSR) passed!" << endl;
        else cout << endl << "testEquality(aCSR,dCSR) failed!" << endl;

        if (testEquality(aCSRList,bCSRList)) cout << "testEquality(aCSRList,bCSRList)) passed!" << endl;
        else cout << endl << "testEquality(aCSRList,bCSRList) failed!" << endl;

        cout << endl << aCSRList.getAt(1,2,4) << endl;//returns the value 70

        cout << endl << aCSRList.getAt(5,2,2) << endl;//throws an exception

    }
    catch (exception &e){
        cout << e.what() << endl;
    }

    // My extra test for driver
    cout << endl << "My Extra Test | **************************************************************" << endl;
    cout << "******************************************************************************" << endl;

    cout << "Test: Creating a matrix and coping it:" << endl << endl;

    // Make matrixs and copy construct them
    CSR firstCSR;
    int arrayBig[] = {11,0,0,0,12,0,12,0,0,0,0,0,13,11,0,0,0,0,0,13,0,0,0,0,17};
    firstCSR.compress(5,5,arrayBig,25);//initialize object aCSR
    CSR firstCopyCSR(firstCSR);//create bCSR using copy constructor
    CSR secondCSR;
    int arrayLong[] = {0,0,1,2,3,0,0,0,0,0,0,9};
    secondCSR.compress(2,6,arrayLong,12);//initialize object cCSR
    CSR secondCopyCSR(secondCSR);//create dCSR using copy constructor

    // Copy constructor address test
    cout << "Display address matrix 1: " << &firstCSR << endl;
    firstCSR.dump();
    cout << endl;

    // This address should be different, but the address is the same
    cout << "Display address matrix 2: " << &firstCopyCSR << endl;
    firstCopyCSR.dump();
    cout << endl;

    // This address should be different, but the address is the same
    cout << "Test: Equality test between copy constructed and orginal matrix" << endl;
    if (testEquality(firstCopyCSR,firstCSR)){
        cout << "These matrixs match!!" << endl;
    }
    cout << "Code should have displayed 'These matrixs match!!'" << endl << endl;

    // Test code for a 0 x 0 Matrix
    cout << "Test: Create a 0 x 0 matrix:" << endl;
    CSR zeroCSR;
    zeroCSR.compress(0,0, arrayBig,25);
    cout << "Display zero matrix:" << endl;
    zeroCSR.dump();
    cout << endl;

    // Test code for n * m < arraysize
    cout << "Test: Create a 2 x 2 matrix, with a big array:" << endl;
    CSR twoBytwoCSR;
    twoBytwoCSR.compress(2,2, arrayBig,25);
    cout << "Display 2 x 2 matrix:" << endl;
    twoBytwoCSR.dump();
    cout << endl;

    // Test code for n * m > arraysize
    cout << "Test: Create a 10 x 10 matrix, with a small array:" << endl;
    CSR tenByTenCSR;
    tenByTenCSR.compress(10,10, arrayBig,25);
    cout << "Display 10 x 10 matrix:" << endl;
    tenByTenCSR.dump();
    cout << endl;

    // Test code for n * m > arraysize
    cout << "Test: Create a 7 x 8 matrix, with a small array:" << endl;
    CSR sevenByEightCSR;
    sevenByEightCSR.compress(7,8, arrayBig,25);
    cout << "Display 7 x 8 matrix:" << endl;
    sevenByEightCSR.dump();
    cout << endl;

    // Test Equality between two different matrixs
    cout << "Test: Equality test between 2 x 2 matrix and 10 x 10 matrix" << endl;
    if (testEquality(tenByTenCSR,twoBytwoCSR)){
        cout << "These matrixs match!!" << endl << endl;
    }
    else
        cout << "These matrixs do not match!!" << endl << endl;
    cout << "Code should have displayed 'These matrixs do not match!!'" << endl << endl;

    // Test code to show that a matrix can be cleared
    cout << "Test: Clearing Matrix 1:" << endl;
    firstCSR.clear();

    // Show a cleared matrix
    cout << "Matrix 1:" << endl;
    firstCSR.dump();

    // Show the copy constructed matrix and show that it was unchanged
    cout << "Matrix 2:" << endl;
    firstCopyCSR.dump();
    cout << endl;


    // Test Equality between two different matrixs
    cout << "Test: Equality test between cleared matrix and copied matrix" << endl;
    if (testEquality(firstCopyCSR,firstCSR)){
        cout << "These matrixs match!!" << endl << endl;
    }
    else
        cout << "These matrixs do not match!!" << endl << endl;
    cout << "Code should have displayed 'These matrixs do not match!!'" << endl << endl;


    // Make a list and insert CSR matrixs into the list
    cout << "Test: Making a list with matrixs:" << endl;
    CSRList newList;
    newList.insertAtHead(secondCopyCSR);
    newList.insertAtHead(firstCSR);
    newList.insertAtHead(secondCSR);
    newList.insertAtHead(twoBytwoCSR);

    // Show all lists in the matrix_1 list
    cout << "Display Matrix list_1:" << endl << endl;
    newList.dump();

    // Test shows that a matrix list can be cleared
    cout << "Test: Clear Matrix list_1 and show it throws an error:" << endl;
    newList.clear();
    cout << endl << "Display Matrix list_1" << endl;

    // Try to dump and print an empty linked_list
    try{ newList.dump();}
    catch (exception &e){
        cout << e.what() << endl;
    }

    // Show that empty function works
    cout << endl << "Test: Show that empty function works for linked list" << endl;
    if (newList.empty())
        cout << "Result: Empty function in linked_list works" << endl << endl;


    // Make another linked list with copy constructor
    cout << endl << "Test: Copy Constructor, CSR Linked_Lists" << endl;
    newList.insertAtHead(firstCopyCSR);
    newList.insertAtHead(secondCopyCSR);
    newList.insertAtHead(twoBytwoCSR);
    cout << "Matrix list_1:  " << &newList << endl << endl;
    newList.dump();
    CSRList matrix2List(newList);
    cout << "Matrix list_2:  " << &matrix2List << endl << endl;
    matrix2List.dump();


    // Compare newList and matrix, this should work
    cout << endl << "Test: Compare Matrix list_1 to Matrix list_2" << endl;
    if (testEquality(matrix2List,newList)){
        cout << endl << "The lists match!!" << endl << endl;
    }

    else {
        cout << endl << "The lists do not match" << endl << endl;
    }
    // Say what should had happened
    cout << "This test should have outputed: 'The lists match!!' " << endl << endl;


    // Tests to see if matrix lists are not equal to each other, should not work
    cout << "Test: Add another element to the second linked list and compare" << endl;
    newList.insertAtHead(tenByTenCSR);
    if (matrix2List == newList){
        cout << "These two list equal each other" << endl;
    }
    else
        cout << "These lists do not equal each other"  << endl;

    cout << endl << "Result: Code should have outputed 'list should not equal each other'" << endl << endl;


    // Show current matrix lists
    cout << endl << endl << "*******************************************************************" << endl;
    cout << "Current Matrix Lists:" << endl << endl;
    cout << "Display Matrix list_1" << endl;
    newList.dump();
    cout << endl << "Display Matrix_list 2" << endl;
    matrix2List.dump();

    // GetAt function tests
    cout << endl << "Test: Preform the precious get at function: Get row 2, column 4, on 10 x 10 matrix" << endl;
    cout << "Elemental: " << tenByTenCSR.getAt(2,4) << endl << endl;

    cout << "Test: Preform the precious get at function: Get row 9, column 9, on 10 x 10 matrix" << endl;
    cout << "Elemental: " << tenByTenCSR.getAt(9,9) << endl << endl;

    cout << "Test: Failed attempt at getAt(), 2 x 2 matrix, index 2,2" << endl;
    try { twoBytwoCSR.getAt(2,2);}
    catch (exception &e){
        cout << e.what() << endl << endl;
    }

    cout << "Test: Try to get an impossible matrix in a list, matrix_2_List" << endl << endl;
    try {matrix2List.getAt(3,1,1);}
    catch (exception &e){
        cout << e.what() << endl << endl;
    }

    cout << endl << "Test: Try to get an impossible matrix in a list, matrix_1_list" << endl << endl;
    try {matrix2List.getAt(-1,1,1);}
    catch (exception &e){
        cout << e.what() << endl << endl;
    }

    //Linked list getAt() function test
    cout << endl << "Test: Preform the linked list getAt() function: Get row 0, column 0, matrix '#2' in list Matrix list_2" << endl;
    cout << "Elemental: " << matrix2List.getAt(2,0,0) << endl << endl;

    //Linked list getAt() function test
    cout << "Test: Preform the linked list getAt() function: Get row 0, column 4, matrix '#0' in list Matrix list_1" << endl;
    cout << "Elemental: " << newList.getAt(0,0,4) << endl << endl;

    //Linked list getAt() function test
    cout << "Test: Preform the linked list getAt() function: Get row 1, column 1, matrix '#1' in list Matrix list_1" << endl;
    cout << "Elemental: " << newList.getAt(1,1,1) << endl << endl;

    //Linked List getAt function failed test
    cout << "Test: Linked_list, valid matrix, but impossible location with a invalid row or invalid column: "<< endl << endl;
    try { matrix2List.getAt(0,1,1000);}
    catch (exception &e){
        cout << e.what() << endl << endl;
    }

    //Linked List getAt function failed test
    cout << "Test: Linked_list, valid matrix, but impossible location with a invalid row or invalid column: "<< endl << endl;
    try { newList.getAt(0,-1,0);}
    catch (exception &e){
        cout << e.what() << endl << endl;
    }

    cout << endl << "**********************************************************************************************" << endl;

    // "= "sign linked list test
    cout << "Test: Set both list equal to each other, see if they match" << endl;
    newList = matrix2List;
    if (newList == matrix2List){
        cout << "Both lists equal each other" << endl <<endl;
    }

    cout << "Result: Code should have outputed 'Both lists equal each other'" << endl << endl;

    cout << "Show that both lists are now the same" << endl << endl;
    cout << "Display List_1: " << endl;
    newList.dump();
    cout << "Display List_2:" << endl;
    matrix2List.dump();

    // Sparse Ratio Tests
    cout << endl << "Test: Sparse Ratio of aCSR:" << endl;
    CSR aCSR;
    int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
    aCSR.compress(4,6,array1,24);//initialize object aCSR
    cout << "Ratio of aCSR: " << aCSR.sparseRatio() << endl << endl;


    // Sparse Ratio Tests
    cout << "Test: Sparse Ratio of empty matrix:" << endl;
    twoBytwoCSR.clear();
    cout << "Ratio: " << twoBytwoCSR.sparseRatio() << endl << endl;

    // Sparse ratio test
    cout << "Test: Sparse Ratio of list_3, with empty matrixs:" << endl;
    CSRList matrix3List;
    matrix3List.insertAtHead(twoBytwoCSR);
    matrix3List.insertAtHead(twoBytwoCSR);
    matrix3List.insertAtHead(twoBytwoCSR);
    matrix3List.insertAtHead(aCSR);
    cout << "CSR_List_3:" << endl;
    matrix3List.dump();
    cout << "Ratio: " << matrix3List.averageSparseRatio() << endl << endl;

    // Sparse ratio test
    cout << "Test: Sparse Ratio of list_2" << endl;
    cout << "Ratio: " << matrix2List.averageSparseRatio() << endl << endl;

    // CSRS Equality test
    cout << "Test: Clearing two 'CSR matrixs' and seeing if they are equal test: " << endl;
    aCSR.clear();
    firstCSR.clear();

    // test equality test of a CSR
    if (testEquality(firstCSR, aCSR))
        cout << "   Test Worked, both CSR's were cleared and are equal to each other" << endl << endl;


    // Equality tests
    cout << "Test: Adding CSR Matrix's to list_1, but not list_2, and then seeing if they are equal test: " << endl;
    matrix2List.insertAtHead(tenByTenCSR);
    // Test equality test
    if (testEquality(newList,matrix2List))
        cout << "   Result: CSR List are equal to each other" << endl << endl;
    else
        cout << "   Result: CSR Lists are not equal to each other" << endl << endl;

    cout << "Should have outputed: 'CSR Lists are not equal to each other'" << endl << endl;


    // Equality tests
    cout << "Test: Clearing one CSR Matrix List, and seeing if both are equal test: " << endl;
    matrix2List.clear();
    // Test equality test
    if (testEquality(newList,matrix2List))
        cout << "   Result: CSR List are equal to each other" << endl << endl;
    else
        cout << "   Result: CSR Lists are not equal to each other" << endl << endl;

    cout << "Should have outputed: 'CSR Lists are not equal to each other'" << endl << endl;


    // Equality tests
    cout << "Test: Clearing both CSR Matrix Lists, and seeing if both are equal test: " << endl;
    newList.clear();
    // Test equality test
    if (testEquality(newList,matrix2List))
        cout << "   Result: CSR List are equal to each other" << endl << endl;
    else
        cout << "   Result: CSR Lists are not equal to each other" << endl << endl;

    cout << "Should have outputed: 'CSR List are equal to each other'" << endl << endl;


    cout << "*******************************************************************************" << endl << endl;
    cout << "Test recompression by resusing old CSR objects:" << endl << endl;
    tenByTenCSR.compress(5,7, arrayBig,25);
    cout << "Display new, 5 x 7 matrix:" << endl;
    tenByTenCSR.dump();
    cout << endl;

    zeroCSR.compress(3,6, arrayBig,25);
    cout << "Display new, 3 x 6 matrix:" << endl;
    zeroCSR.dump();
    cout << endl;

    twoBytwoCSR.compress(2,7, arrayBig,25);
    cout << "Display new, 2 x 7 matrix:" << endl;
    twoBytwoCSR.dump();
    cout << endl;

    return 0;
}

bool testEquality(CSR& a, CSR& b){
    return (a == b);
}
bool testEquality(CSRList& a, CSRList& b){
    return (a == b);
}