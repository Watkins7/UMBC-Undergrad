/*
** File: hash.h
** Project: CMSC 341 Project 4, Fall 2020
** Author: William Atkins
** Date: 11/30/20
** Email: watkins7@umbc.edu
** Description: This is the hash.h file for project 4
*/

#ifndef CS341PROJ4_HASH_H
#define CS341PROJ4_HASH_H

// CMSC 341 - Fall 2020 - Project 4
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor                         []
//  (b) priority function (unsigned priority())     []
//  (c) key function (string key())                 []
//  (d) overloaded insertion operator               []

//#ifndef _HASH_H
//#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

    friend Grader;

public:
    // Constructor.  Requires table size and hash function.
    HashTable(unsigned size, hash_fn hash);

    // Destructor, copy, and assignment
    ~HashTable();
    HashTable(const HashTable<T>& ht);
    const HashTable<T>& operator=(const HashTable<T>& ht);

    // In-line functions

    // Table size; set by constructor
    unsigned tableSize() const { return _N; }
    // Number of entries in the table
    unsigned numEntries() const { return _n; }
    // Load factor
    float lambda() const { return ((float) _n) / _N; }

    // Main hash table functions

    // insert returns 'true' if successful; 'false' otherwise
    bool insert(const T& object);

    // getNext retrieves **and removes** the highest priority order of
    // type indicated by key.  It returns 'true' if successful; 'false'
    // otherwise.
    bool getNext(string key, T& obj);

    // Dump the entire hash table
    void dump() const;

private:
    unsigned _N;       // hash table size
    unsigned _n;       // current number of entries
    hash_fn _hash;     // hash function
    Heap<T> *_table;   // array of heaps

    // ***********************************************
    // Private helper function declarations go here! *
    // ***********************************************

};

// Key = car = bucket = hash
// car dealer = heap = priority

// Hash Table
// A  hash table is a data structure which implements the map ADT.
// It stores the pairs of key-value. The key determines the index number
// of an array cell (bucket) in which the value will be stored.
// A hash function calculates the index number.
// If there is more than one value for a key in the data set,
// the hash table uses a collision handling scheme to find another cell
// for storing the new value.

// *****************************************
// Templated function definitions go here! *
// *****************************************
// The alternative constructor, size is an unsigned integer to specify
// the length of hash table, and hash is a function pointer to a hash function.
// The type of hash is defined in hash.h.
template <typename T>
HashTable<T>::HashTable(unsigned size, hash_fn hash) {

    // Set length of hash table
    _N = size;
    _n = 0;

    // Set hash function
    _hash = hash;

    // Make the array of heaps, with an empty heap
    _table = new Heap<T>[_N];

    // For loop to populate the array
    for (unsigned int i = 0; i < _N; i++){
        _table[i] = Heap<T>();
    }

}

// Destructor, deallocates the memory.
template <typename T>
HashTable<T>::~HashTable(){

    // Delete memory
    // delete _table;
    delete[] _table;
}

// Copy constructor, must make a deep copy of the hash table.
template <typename T>
HashTable<T>::HashTable(const HashTable<T>& ht){

    // Set length of hash table
    _N = ht._N;
    _n = ht._n;

    // Set hash function
    _hash = ht._hash;

    // Make the array of heaps, with an empty heap
    _table = new Heap<T>[_N];

    // For loop to populate the array
    for (unsigned int i = 0; i < _N; i++){
        _table[i] = ht._table[i];
    }

}

// Assignment operator, must make a deep copy of the right-hand-side object.
// It must also guard against self-assignment.
template <typename T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){

    // Protects againist self assignment
    if (&ht == this){
        return *this;
    }

    // Delete memory
    // delete _table;
    delete[] _table;

    // Set length of hash table
    _N = ht._N;
    _n = ht._n;

    // Set hash function
    _hash = ht._hash;

    // Make the array of heaps, with an empty heap
    _table = new Heap<T>[_N];

    // For loop to populate the array
    for (unsigned int i = 0; i < _N; i++){
        _table[i] = ht._table[i];
        //_table[i]._used = ht._table[i].used();
    }

    return *this;

}


// This function inserts an object into the hash table.
//The insertion index is determined by applying the hash function _hash that is set in the HashTable constructor call...
// ..and then reducing the output of the hash function modulo the table size (the MOD compression function).
// Hash collisions should be resolved using linear probing.
//It returns true if the object is successfully inserted and false otherwise.
// The function could fail to insert an object if, for example, the hash table is full.
template <typename T>
bool HashTable<T>::insert(const T& object){

    // if the current number of elements == size
    // Hashtable is full
    if (_n == _N){
        cout << "Hash Table is full, unable to insert object" << endl;
        return false;
    }

    // get index
    int index = _hash( object.key() );
    index = index % _N;

    // if there is nothing at that index
    if ( !_table[index].used() ){

        // Insert for the first time
        _table[index].insert(object);

        // Update how many keys are recorded
        _n++;

        return true;

    }

        // Else there is something at that index
        // Check to see if keys match

    else if ( !_table[index].empty() and _table[index].readTop().key() == object.key() ){

        _table[index].insert(object);

        return true;

    }

        // Solve hash collision
    else {
        // Last half of the vector
        for (unsigned int i = index; i < _N; i++){

            // Nested if statement for if used and empty, skip
            // If the loctation has a key
            if ( _table[i].used() ){

                // If location has items in it, check the key
                if ( !_table[i].empty() ){

                // Check to see keys match
                if ( _table[i].readTop().key() == object.key() ) {

                    // Insert object into heap
                    _table[i].insert(object);

                    // Return after insert
                    return true;

                } // End of keys match

                } // End of empty()

            } // End of _used


            // If we find an empty space, insert the object there
            if ( !_table[i].used() ){

                // Insert for the first time
                _table[i].insert(object);

                // Update how many keys are recorded
                _n++;

                return true;

            }

        }

        // First half of the vector
        for (int i = 0; i < index; i++){

            // Nested if statement for if used and empty, skip
            // If the loctation has a key
            if ( _table[i].used() ){

                // location is not empty
                if ( !_table[i].empty()) {

                // Check to see keys match
                if ( _table[i].readTop().key() == object.key() ) {

                    // Insert object into heap
                    _table[i].insert(object);

                    // Return after insert
                    return true;
                }

                }
            }

            // If we find an empty space, insert the object there
            if ( !_table[i].used() ){

                // Insert for the first time
                _table[i].insert(object);

                // Update how many keys are recorded
                _n++;

                return true;

            }

        }
    }

    // Return false by default
    cout << "End of *hash.insert(), failed to insert." << endl;
    return false;

}


// This function reads and removes the highest priority object with the given key.
// It locates the bucket corresponding to the given key using the hashing method described for the insert() function...
// ...and resolving collisions using linear probing. It then retrieves AND removes the highest priority object from the heap...
// ...and returns the object in the reference parameter obj.
// It returns true if it sucessfully locates and returns an object with the specified key value; otherwise, it returns false.
template <typename T>
bool HashTable<T>::getNext(string key, T& obj){

    // Get the index of where the object should be at
    int index = _hash( key );
    index = index % _N;

    // Edge case where there is no object at the index
    if ( !_table[index].used() ) {
        cout << "Cannot getNext object, key does not exist" << endl;
        //cout << "Bucket not used" << endl;
        return false;
    }

    // If the object exists, keys match
    // Return object, then remove top
    if ( !_table[index].empty() )
        if ( _table[index].readTop().key() == key ){

            obj = _table[index].readTop();

            _table[index].removeTop();

            return true;

        }

    // Do a linear probing search to see in the object exists in the list
    for (unsigned int i = index; i < _N; i++){

        // If we find a "blank space", key does not exist in this list
        if ( !_table[i].used() ){

            cout << "Cannot getNext object, key does not exist" << endl;
            return false;
        }

        // If you find the key, and there are objects still in the heap
        if ( !_table[i].empty() ){

            if (_table[i].readTop().key() == key){

                //cout << "Trying to do the right thing" << endl;
                // Get object and remove top
                obj = _table[i].readTop();
                _table[i].removeTop();
                return true;

            }
            //else {
                //cout << "Error:  Cannot find a key that matches to the hash" << endl;
                //return false;
           // }

        } // End of if empty


        // If we find the key, and it is empty, return false
        //if (  _table[i].empty() ) {
            //if ( _table[i].readTop().key() == key ){
            //cout << "Cannot getNext object, no objects in this heap" << endl;
            //return false;
       // }

    }

    // Second linear probing check
    for (int i = 0; i < index; i++){

        // If we find a "blank space", key does not exist in this list
        if ( !_table[i].used() ){
            cout << "Cannot getNext object, key does not exist" << endl;
            return false;
        }

        // If you find the key, and there are objects still in the heap
        if ( !_table[i].empty() ) {

            if (_table[i].readTop().key() == key){

                // Get top, remove top
                obj = _table[i].readTop();
                _table[i].removeTop();
                return true;
            }

            //else {
                //cout << "Error:  Cannot find a key that matches to the hash" << endl;
                //return false;
            //}

        } // End of ifEmpty()

        // If we find the key, and it is empty, return false
        //if (  _table[i].empty() ) {
            //if ( _table[i].readTop().key() == key ){
            //cout << "Cannot getNext object, no objects in this heap" << endl;
           // return false;
        //}

    }

    // By default return false
    cout << "Cannot getNext object, key does not exist" << endl;
    return false;
}


// This function dumps the contents of the hash table in index order.
// It prints the contents of the hash table in array-index order.
// For each bucket, it should call the heap dump() function to output the heap contents.
template <typename T>
void HashTable<T>::dump() const{

    // For loop for dump
    for (unsigned int i = 0; i < _N; i ++){

        cout << "[" << i << "]:" << endl;

        // If this "object" at index "i", has been used
        // Output the heap to the screen
        // Note: Probably not need since it preforms check
        if ( _table[i].used() ){
            _table[i].dump();
        }

    }

}

#endif