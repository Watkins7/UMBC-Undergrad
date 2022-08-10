#ifndef CS341PROJ4_HEAP_H
#define CS341PROJ4_HEAP_H

// CMSC 341 - Fall 2020 - Project 4
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

//#ifndef _HEAP_H
//#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor                             []
//  (b) priority function (unsigned priority())         []
//  (c) key function (string key())                     []
//  (d) overloaded insertion operator                   []

class Grader;

template <class T>
class Heap {

    friend Grader;

public:
    // Constructor
    Heap();

    // Inline functions: size, empty, used
    unsigned size() const { return _heap.size() - 1 ; }
    bool empty() const { return _heap.size() <= 1 ; }
    bool used() const { return _used ; }

    // Main heap operations: insert, read, remove
    void insert(const T& object);
    T readTop() const;
    void removeTop();

    // Dump the entire heap
    void dump() const;

    // Root node always has index 1
    static const unsigned ROOT = 1;

private:
    vector<T> _heap;   // Vector-based heap
    bool _used;        // Has the heap ever been used?  Needed for linear probing.

    // *********************************************
    // Private helper function declarations go here!
    // *********************************************
    // Function that will go through back to front to get max
    void maxHeap(){

        // Start at very end of the heap
        int location = _heap.size() - 1;

        // While we arent at the start
        while (location > 1){

            // If the current location is bigger than the parent.
            // Swap them
            if ( _heap.at(location).priority() > _heap.at(location/2).priority() ){
                swap(_heap[location],_heap[location/2]);
            }

            // If not, then we can break
            else{
                break;
            }

            // Move location up
            location = location / 2;
        }

    }
    // Function that will go through front to back to get max
    void fixRemoveMax(int index){

        // Set index
        int largestKnown = index;
        int leftChild = 2*index;
        int rightChild = 2*index+1;

        // See if left child is greater than root
        if (leftChild < _heap.size()-1 and _heap.at(leftChild).priority() > _heap.at(largestKnown).priority() )
            largestKnown = leftChild;

        // See if right child is greater than root
        if (rightChild < _heap.size()-1 and _heap.at(rightChild).priority() > _heap.at(largestKnown).priority() )
            largestKnown = rightChild;

        // If found not root
        // Swap locations
        if (largestKnown != index){
            swap( _heap.at(index), _heap.at(largestKnown) );

            // Then recursively call function
            fixRemoveMax(largestKnown);
        }

    }

};

// ***************************************
// Templated function definitions go here!
// ***************************************

// Default constructor, initializes an empty object.
template <typename T>
Heap<T>::Heap() {

    // Only need to set _used to false
    _used = false;
}

// This function inserts object into the heap
// and maintains the max-heap property.
template <typename T>
void Heap<T>::insert(const T &object) {

    // If heap is empty
    // Push back twice to store "key" + "object"
    if ( _heap.size() == 0 ) {
        _heap.push_back(object);
        _heap.push_back(object);

        // Change that this has been used
        _used = true;

        return;
    }

    // Else push back once
    else {
        _heap.push_back(object);
    }

    // Preform maxHeap
    maxHeap();


}

// This function returns the highest priority element in the heap,
// but does not remove it from the heap.
template <typename T>
T Heap<T>::readTop() const{

    // If the heap has at least a MAX, return the object
    if (_heap.size() >= 2 )
        return _heap.at(1);

    // Else, throw an error saying there are not enough elements
    else
        throw std::domain_error("Error: Not enough elements, cannot return element");

}

// This function removes the highest priority element from the heap.
// The max-heap property must be remained after the highest priority element is removed.
template <typename T>
void Heap<T>::removeTop(){

    // Check bounds, cannot remove top is list is <= 1
    if (_heap.size() <= 1){

        throw std::out_of_range("Heap cannot remove top, does not contain any elements");
        return;
    }

    // Edge case for when there is really one element in the heap
    if ( _heap.size() == 2) {
        _heap.pop_back();
        return;
    }

    // Else
    // Swap head and last element
    swap( _heap[ 1 ], _heap[ _heap.size()-1 ]);

    // pop last element
    _heap.pop_back();

    // Fix max priority, starting at root
    fixRemoveMax(1);


} // End of removeTop


// This function dumps the contents of the heap array in index order.
// It prints the contents of the heap in array-index order (not by priority).
// The template class T must overload the insertion operator (operator<<).
template <typename T>
void Heap<T>::dump() const{

    // If this has been used, we at least have key0
    // Meaning we can dump this heap
    if ( _used ) {

        // Print all but key0
        for (int i = 1; i < _heap.size(); i++) {
            cout << _heap.at(i) << endl;
        }
    }

}


#endif