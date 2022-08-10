//
// Created by Thadd-PC on 9/1/2020.
//

#ifndef CMSC341_PROJ0_QUEUE_H
#define CMSC341_PROJ0_QUEUE_H

// CMSC 341 - Fall 2020 - Project 0
// queue.h: a templated, linked list-based queue implementation

// Assignment:
//   (1) Complete the copy constructor
//   (2) Complete the assignment operator
//   (3) Complete the destructor
//   (4) Write a test program (mytest.cpp) to test copy and assignment
//   (5) Verify destructor by running the test program in Valgrind


#include <iostream>
#include <exception>

using std::ostream;
using std::cout;
using std::endl;
using std::range_error;

// Forward declarations
template <class T> class Queue;
template <class T> class Node;
template <class T> ostream& operator<<(ostream&, const Node<T>&);

// Node class for linked list
template <class T>
class Node {

    friend Queue<T>;

public:
    Node(T data = T(), Node<T> *next = nullptr) {
        _data = data;
        _next = next;
    }

    friend ostream& operator<< <T>(ostream &sout, const Node<T> &x);

private:
    T _data;
    Node *_next;
};

// Overloaded insertion operator.  Must be overloaded for the template
// class T, or this won't work! For primitive types in C++ such as string
// or int this is alredy overloaded
template <class T>
ostream& operator<<(ostream &sout, const Node<T> &x) {
    sout << "Data: " << x._data;
    return sout;
}


// Queue class.  Linked-list implementation of a queue. Uses the Node
// class.
template <class T>
class Queue {
public:
    // Constructor
    Queue();

    // Copy constructor, assignment operator, and destructor
    // DO NOT IMPLEMENT HERE.  SEE BELOW.
    Queue(const Queue &rhs);  // Copy
    const Queue& operator=(const Queue& rhs); // Assignment
    ~Queue(); // Desctructor

    // Queue operations: enqueue(), head(), and dequeue()
    void enqueue(const T& data);//inserts at the end
    const T& head() const;      //returns the head value
    void dequeue();             //removes from the head

    // Helpful functions
    bool empty() const;  // Returns 'true' if queue is empty
    void dump() const;   // Dump contents of the linked list

private:
    Node<T> *_head;

    // ***************************************************
    // Any private helper functions must be delared here!
    // ***************************************************
    void getAddress(Node<T> *ptr) const;
};

template <class T>
Queue<T>::Queue() {
    _head = nullptr;
}

template <class T>
Queue<T>::Queue(const Queue<T>& rhs) {

    // ********************************
    // Implement the copy constructor
    // ********************************

    // Node to be copied from old list
    Node<T> *nodeToCopy = rhs._head;

    // Check to see if m_head in other list is empty
    if (nodeToCopy == nullptr){
        // If passed list is empty, QUIT
        _head = nullptr;
        return;
    }

    // Else other list has nodes
    // Set this m_head equal to a new node
    _head = new Node<T>(nodeToCopy->_data);

    // New node for "this" list
    Node<T> *newNode;

    // Previous Node in "this" list
    Node<T> *previousNode = _head;

    // Move "nodeToCopy over by one
    nodeToCopy = nodeToCopy->_next;

    // While there is a node to copy
    while (nodeToCopy != nullptr){

        // Make a new Node
        newNode = new Node<T>(nodeToCopy->_data);

        //Have previous node point to new node
        previousNode->_next = newNode;

        // Move previousNode
        previousNode = previousNode->_next;

        // Move node that you copying
        nodeToCopy = nodeToCopy->_next;

    }

    // Finally have the last node in "this" list point to null
    previousNode->_next = nullptr;


}

template <class T>
const Queue<T>& Queue<T>::operator=(const Queue<T>& rhs) {

    // **********************************
    // Implement the assignment operator
    // **********************************

    // Run Destructor code
    // Make a temp_ptrs that tranverses the list
    Node<T> *previous;
    Node<T> *current = this->_head;
    Node<T> *dataToCopy = rhs._head;

    // While loop to delete
    while(current != nullptr){

        // Set previous equal to current
        previous = current;

        // Move current
        current = current->_next;

        // Delete previous
        delete previous;
        previous = nullptr;
    }


    // Copy data from passed list
    // If there is data in the "passed queue"
    if ( dataToCopy != nullptr ) {

        // Set a new node for _head
        this->_head = new Node<T>( dataToCopy->_data );

        // Move dataToCopy to the next node
        dataToCopy = dataToCopy->_next;

        // Move current to _head of "this queue"
        current = this->_head;

        // While loop to copy data
        while (dataToCopy != nullptr){

            // Make a new node for "this" queue
            current->_next = new Node<T>( dataToCopy->_data );

            // Move current
            current = current->_next;

            // Move the data you are copying to the next node
            dataToCopy = dataToCopy->_next;

        }

        // Have the last node in the list point to null
        current->_next = nullptr;

    }

    // else set this->_head = null
    else
        this->_head = nullptr;


    // Always return this object being modifed
    return *this;

}


template <class T>
Queue<T>::~Queue() {

    // *************************
    // Implement the destructor
    // *************************

    // Make a temp_ptrs that tranverses the list
    Node<T> *previous;
    Node<T> *current = _head;

    // While loop to delete
    while(current != nullptr){

        // Set previous equal to current
        previous = current;

        // Move current
        current = current->_next;

        // Delete previous
        delete previous;
        previous = nullptr;
    }

}

template <class T>
void Queue<T>::enqueue(const T& data) {
    Node<T> *newPtr = new Node<T>(data);
    Node<T> *tempPtr;
    if (_head == nullptr){
        _head = newPtr;
    }
    else{
        tempPtr = _head;
        while ( tempPtr->_next != nullptr ) {
            tempPtr = tempPtr->_next;
        }
        tempPtr->_next = newPtr;
    }
}

template <class T>
const T& Queue<T>::head() const {
    if ( empty() ) {
        throw range_error("Queue<T>::head(): attempt to read empty Queue.");
    }

    return _head->_data;
}

template <class T>
void Queue<T>::dequeue() {
    if ( empty() ) {
        throw range_error("Queue<T>::dequeue(): attempt to dequeue an empty Queue.");
    }

    Node<T> *tmpPtr = _head->_next;
    delete _head;
    _head = tmpPtr;
}

template <class T>
bool Queue<T>::empty() const {
    return _head == nullptr;
}

template <class T>
void Queue<T>::dump() const {

    // Start at _head
    Node<T> *nodePtr = _head;

    // While loop to run through queue to display items to user
    while ( nodePtr != nullptr ) {

        // cout node information
        cout << "Node: " << nodePtr->_data;
        // get Node's address
        getAddress(nodePtr);

        // Get next node
        nodePtr = nodePtr->_next;
    }
}

template <class T>
void Queue<T>::getAddress(Node<T> *ptr) const {

        // cout ptr's address
        cout << " Pointer's Address: "<< ptr << endl;

}


#endif //CMSC341_PROJ0_QUEUE_H
