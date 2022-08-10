/*
** File: mytest.cpp
** Project: CMSC 341 Project 4, Fall 2020
** Author: William Atkins
** Date: 11/30/20
** Email: watkins7@umbc.edu
** Description: This is the mytest.cpp file for project 4
	This is the main driver for project 4
*/


#include <iostream>
#include "hash.h"
#include "car.h"

// Prototype for 16 bit cyclic hash function; implementation is after
// main().
unsigned cyclic_hash16(string key);
unsigned hashCollision2(string key);

int main() {

    // Create a vector of cars to insert in the hash table
    vector<Car> cars;
    cars.push_back(Car("x101", 5, "super car"));
    cars.push_back(Car("x101", 12, "mega car"));
    cars.push_back(Car("x101", 4, "shack of cars"));
    cars.push_back(Car("challenger", 10, "mega car"));
    cars.push_back(Car("challenger", 5, "car world"));
    cars.push_back(Car("stratos", 7, "car world"));
    cars.push_back(Car("stratos", 15, "super car"));
    cars.push_back(Car("stratos", 8, "shack of cars"));
    cars.push_back(Car("challenger", 3, "car joint"));
    cars.push_back(Car("gt500", 3, "shack of cars"));
    cars.push_back(Car("miura", 28, "mega car"));
    cars.push_back(Car("gt500", 11, "super car"));

    // Create the hash table of length 10 using cyclic_hash function
    HashTable<Car> ht(10, cyclic_hash16);

    vector<Car>::iterator itCar;
    for (itCar=cars.begin();itCar!=cars.end();itCar++)
        ht.insert(*itCar);

    cout << "\nDump of ht:\n";
    ht.dump();

    // Extract some orders

    Car d;
    vector<string> orders;

    orders.push_back("challenger");
    orders.push_back("miura");
    orders.push_back("gt500");
    orders.push_back("gt500");
    orders.push_back("gt500");

    vector<string>::iterator itString;

    for ( itString=orders.begin();itString!=orders.end();itString++ ) {
        cout << "\nGet next '" << *itString << "' order...\n";
        if ( ht.getNext(*itString, d) ) {
            cout << "  " << d << endl;
        } else {
            cout << "  No " << *itString << " orders!\n";
        }
    }

    cout << endl;

    cout << "\nDump of ht:\n";
    ht.dump();

    // Simple test of copy constructor; also need to test assignment
    // operator!
    cout << "\nCreate copy of hash table, remove two 'stratos' orders, dump both tables...\n";

    HashTable<Car> ht2(ht);

    ht2.getNext("stratos", d);
    ht2.getNext("stratos", d);

    cout << "\nDump of ht:\n";
    ht.dump();

    cout << "\nDump of ht2:\n";
    ht2.dump();

    cout << "\nht tableSize:    " << ht.tableSize() << endl;
    cout << "ht numEntries:   " << ht.numEntries() << endl;
    cout << "ht lamba:        " << ht.lambda() << endl;


    // My personal tests
    cout << "\n=============================  William Atkins / Student Test  ============================" << endl;
    cout << "\n\n";

    // Create a test car
    Car testCar;

    // Create a empty hashtable
    HashTable<Car> myTestHash(10, cyclic_hash16);
    Heap<Car> myTestHeap;

    cout << "Requirement: If readTop() or removeTop() is called on an empty heap, a range_error exception must be thrown.\n" << endl;

    // GetNext hash function on a empty hash
    cout << "Trying to getNext 'x101' in an empty hashTable" << endl;
    try {
        myTestHash.getNext( "x101", testCar);
    }
    catch( int x) {
        cout << "Expected Error GetNext: " << endl << x;
    }

    // 4 attempts of accessing an empty heap
    cout << "\n\nFour tests on empty heaps:\n\n";
    // readTop on an empty heap
    try {
        myTestHeap.readTop();
    }
    catch (std::exception &err) {
        cout << "Error expected:  " << err.what();
        cout << "\n";
    }

    // removeTop on an empty heap
    try {
        myTestHeap.removeTop();
    }
    catch (std::exception &err) {
        cout << "Error expected:  " << err.what();
        cout << "\n";
    }

    myTestHeap.insert(cars.at(1));
    myTestHeap.removeTop();

    // readTop on an empty heap
    try {
        myTestHeap.readTop();
    }
    catch (std::exception &err) {
        cout << "Error expected:  " << err.what();
        cout << "\n";
    }

    // removeTop on an empty heap
    try {
        myTestHeap.removeTop();
    }
    catch (std::exception &err) {
        cout << "Error expected:  " << err.what();
        cout << "\n";
    }


    cout << "\nRequirement: Hash collisions must be resolved by linear probing." << endl;
    cout << "Requirement: For the HashTable class, a destructor, copy constructor, and assignment operator must be implemented." << endl;

    // Create first hashtable
    HashTable<Car> testA(5, hashCollision2);
    testA.insert(Car("x56", 56, "super car") );
    testA.insert(Car("xSupra", 1, "super world") );
    testA.insert(Car("xPronta", 5, "wonder world") );
    testA.insert(Car("xVondra", 17, "shield world") );

    // Create second hashtable
    HashTable<Car> testB = testA;
    testB.insert( Car("xTempra", 43, "groupon") );

    cout << "\n\nLinear Collision insert and removal test" << endl;
    HashTable<Car> testJ(5, hashCollision2);
    testJ.insert(Car("x56", 56, "super car") );
    testJ.insert(Car("xSupra", 1, "super world") );
    testJ.insert(Car("xPronta", 5, "wonder world") );
    testJ.insert(Car("xVondra", 17, "shield world") );
    testJ.getNext("x56",testCar);
    testJ.insert(Car("xHydra", 17, "shield world") );
    testJ.dump();

    // Assignment operator, copy constructor test
    cout << "\n\nAssignment Operator Test, Hash Tables"<< endl;
    cout << "Hashtable 1: " << endl;
    testA.dump();
    cout << "\n\nHashtable 2, copy of Hashtable 1 plus xTempra: " << endl;
    testB.dump();

    HashTable<Car> testC(5, hashCollision2);
    HashTable<Car> testD = testC;

    testC = testC;
    testC = testB;

    cout << "\n\nHashtable 3, copy of Hashtable 2" << endl;
    testC.dump();

    HashTable<Car> testZ(testC);
    cout << "\n\nCopy Constructor Test" << endl;
    cout << "Hashtable 4, copy of Hashtable 3" << endl;
    testZ.dump();

    cout <<  "\n\nInsering in a full HashTable test" << endl;
    try {
        testZ.insert(Car("xThaddeus", 9, "Zoolock Deck") );;
    }
    catch (std::exception &err) {
        cout << "Error expected:  " << err.what();
        cout << "\n";
    }


    // Insertion, hash collision and deletion tests
    cout << "\n\nTest linear probing is working correctly after insertions and removals." << endl;
    cout << "Hash algorthim always results in '2', show result of three objects inserted.\n" << endl;
    HashTable<Car> testCollision(5, hashCollision2);
    testCollision.insert(cars.at(1));
    testCollision.insert(cars.at(4));
    testCollision.insert(cars.at(7));
    testCollision.dump();

    cout << "\n\nPreform hash function getNext: Stratos\n" << endl;
    testCollision.getNext("stratos",testCar);
    testCollision.dump();


    // Test solely if the heap is working properly
    cout << "\n\nTest whether heap property is maintained after insertions and removals.\n" << endl;
    cout << "Inserting priority 56, 77, 6, 10, 1, 17, 18, 34, 35, 54, 89, 99" << endl;
    vector<Car> heapPriority;

    myTestHeap.insert(Car("x56", 56, "super car"));
    myTestHeap.insert(Car("x77", 77, "super car"));
    myTestHeap.insert(Car("x6", 6, "super car"));
    myTestHeap.insert(Car("x10", 10, "super car"));
    myTestHeap.insert(Car("x1", 1, "super car"));
    myTestHeap.insert(Car("x17", 17, "super car"));
    myTestHeap.insert(Car("x18", 18, "super car"));
    myTestHeap.insert(Car("x34", 34, "super car"));
    myTestHeap.insert(Car("x35", 35, "super car"));
    myTestHeap.insert(Car("x54", 54, "super car"));
    myTestHeap.insert(Car("x89", 89, "super car"));
    myTestHeap.insert(Car("x99", 99, "super car"));

    cout << "\n\nExpected result in Order: 99, 77, 89, 35, 56, 18, 17, 10, 34, 1, 54, 6" << endl;
    cout << "Actual Result: " << endl;
    myTestHeap.dump();

    cout << "\n\nRemove max, and dump" << endl;
    cout << "Expected result in Order: 89, 77, 18, 35, 56, 6, 17, 10, 34, 1, 54" << endl;
    myTestHeap.removeTop();
    cout << "Actual Result: " << endl;
    myTestHeap.dump();

    return 0;
}

unsigned cyclic_hash16(string key) {
    unsigned usize = 16;
    unsigned s = 5; // shift by 5
    unsigned h = 0;
    for ( unsigned int i = 0; i < key.length(); i++ ){
        h = (( h << s ) | ( h >> (usize - s) ));
        h += key[i];
        h = h & 0xffff;
    }
    return h;
}

// hash created specifically for hash collision
unsigned hashCollision2(string key){

    return 2;
}
