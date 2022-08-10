// CMSC 341 - Fall 2020 - Project 3
// PQueue.cpp: an ER triage queue using a skew heap and function pointers
// Author: William Atkins
// Email: watkins7@umbc.edu
// Date: 9/10/20
// Purpose: Informational Skew Heap

#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

//  CONSTRUCTOR
//  This is the constructor for the PQueue class.
//  It must be provided with a pointer to the prioritization function.
PQueue::PQueue(prifn_t priFn) {

    // Set the function pointer Priority
    priority = priFn;

    // Set other parameters;
    _heap = nullptr;
    _size = 0;

}

//  Destructor, all dynamically-allocated data must be deallocated.
PQueue::~PQueue() {

    // Clear tree, delete all nodes
    clear();

}

//  COPY CONSTRUCTOR
//  Copy constructor, must make a deep copy of the rhs object.
//  Must function correctly if rhs is empty.
PQueue::PQueue(const PQueue& rhs) {

    // Case of being passed null, nothing in the heap
    if (!rhs._heap){
        _heap = nullptr;
        _size = 0;
        priority = rhs.getPriorityFn();

        return;
    }

    else {

        // Copy size, priority over
        _size = rhs._size;
        priority = rhs.getPriorityFn();

        // Copy root from "passed tree"
        _heap = new Node(rhs._heap->getPatient());

        // Copy left side, and right side
        _heap->_left = copyTree(rhs._heap->_left);
        _heap->_right = copyTree(rhs._heap->_right);
    }


}

//  Assignment operator, remember to check for self-assignment and to free all dynamically allocated data members of the host.
//  You should not call the copy constructor in the implementation of the assignment operator.
PQueue& PQueue::operator=(const PQueue& rhs) {

    // Check for self assignment
    if (rhs._heap == this->_heap){
        return *this;
    }

    else {

        // clear current tree
        this->clear();

        // Copy size, priority function over
        _size = rhs._size;
        priority = rhs.getPriorityFn();

        // Copy root from "passed tree", recursively
        _heap = copyTree(rhs._heap);

    }

    return *this;

}

//  Insert a patient into the queue.
//  Must maintain the min-heap property.
void PQueue::insertPatient(const Patient& input) {

    // up size
    _size++;

    // Make a new node to insert
    Node *newNode = new Node(input);

    // Merge the two Node trees
    _heap = mergeNodes(_heap,newNode);

}

//  Extract and return the highest priority patient from the queue.
//  Must maintain the min-heap property.
//  Should throw a domain_error exception if the queue is empty when the function is called.
Patient PQueue::getNextPatient() {

    if (!_heap){
        throw domain_error("Min-heap is empty, there is no next patient");
    }

    else {

        // save root patient
        Patient rootPatient = _heap->getPatient();
        Node* temp = _heap;

        // split tree
        Node* leftHeap = _heap->_left;
        Node* rightHeap = _heap->_right;

        // merge tree
        // IF FUCKS UP, TRY MAKING LEFT LESS THAN RIGHT.
        _heap = mergeNodes(leftHeap, rightHeap);

        // lower size
        _size--;

        // delete root node
        delete temp;

        // return patient
        return rootPatient;
    }
}

//  Merge the host queue with the rhs; leaves rhs empty.
//  Two skew heaps can only be merged if they have the same priority function.
//  If the user attempts to merge queues with different priority functions,
//  a domain_error exception should be thrown.
//  This function requires protection against self-merging.
//  Merging a heap with itself is not allowed.
void PQueue::mergeWithQueue(PQueue& rhs) {

    // nullptrs being passed, nothing to do
    if ( (this->_heap == nullptr) and (rhs._heap == nullptr) ){
        return;
    }

    // Merging with itself is not allowed
    if (this->_heap == rhs._heap){
        throw domain_error("Domain Error:  Cannot merge a queue with itself.");
    }

    // Different prioritys, return an error
    else if (rhs.priority != this->priority)
    {
        throw domain_error("Domain Error:  Different merging priorities");

    }

    else {

        // Copy rhs
        //PQueue *copy = new PQueue(rhs);

        // Call actual merge Function
        _heap = mergeNodes(_heap, rhs._heap);

        // Clear RHS
        rhs._heap = nullptr;
        rhs._size = 0;
    }

}

//  Clear the queue. Must delete all the nodes in the skew heap, leaving the skew heap empty.
void PQueue::clear() {

    if (_heap) {
        // Delete _heap recursively
        deleteTree(_heap);
    }

    _heap = nullptr;
    _size = 0;

}

//  Return the current number of patients in the queue.
int PQueue::numPatients() const { return _size; }

//  Print the contents of the queue using preorder traversal.
//  Although the first patient printed should have the highest priority,
//  the remaining patients will not necessarily be in priority order.
//  Please refer to the sample output file (driver.txt) for the format of this function's output.
void PQueue::printPatientQueue() const { printNode(_heap);}

//  Get the current priority function.
prifn_t PQueue::getPriorityFn() const { return priority; }

// NOT DONE
//  Set a new priority function. Must rebuild the heap!
void PQueue::setPriorityFn(prifn_t priFn) {

    // Set priority
    priority = priFn;

    // New PQueue
    PQueue *newPQueue = new PQueue(priFn);

    // while loop, while there is a _heap
    while(_heap){

        // Insert min into newPQueue, which has a new priority
        newPQueue->insertPatient( getNextPatient() );

    }

    // Afterwards this->_heap should be cleared
    // Now set this->_heap = to new priotity_heap
    // Deep copy "this"
    *this = *newPQueue;

    // Delete newPQueue
    delete newPQueue;


    // We should have done
    // 1) Make a temp PQueue with the new priority
    // 2) Make a new heap with different priority
    // 3) this->PQueue =  newPQueue
    // 4) Delete newPQueue
    return;

}

// NOT DONE
//  Use an inorder traversal to dump the heap and indicate the tree structure (as in the previous project).
//  Represent a node in the tree by its integer priority as computed using the priority function and the name of the patient.
//  Please refer to the sample output file (driver.txt) for the format of this function's output.
void PQueue::dump() const{ printTree(_heap); cout << endl;}

// COMPLETED FOR ME
ostream& operator<<(ostream& sout, const Patient& patient) {
    sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
         << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
         << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
    return sout;
}

// COMPLETED FOR ME
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getPatient();
    return sout;
}

// My recursive delete code
void PQueue::deleteTree(Node* toDelete) {

    // If null, return
    // Base case
    if (toDelete == nullptr)
        return;

    // Recusively Delete
    else {
        deleteTree(toDelete->_left);
        deleteTree(toDelete->_right);
        delete toDelete;
        toDelete = nullptr;
    }
}

// My recursive copy code
Node* PQueue::copyTree(Node *toCopy) {

    // If null, return null
    if (!toCopy) {
        return nullptr;
    }


    else {

        // Get Patient info
        Patient copiedPatient = toCopy->getPatient();

        // Make new node to return
        Node *returnNode = new Node(copiedPatient);

        // Copy left and right
        returnNode->_left = copyTree(toCopy->_left);
        returnNode->_right = copyTree(toCopy->_right);

        // Finally return youself, which is a node
        return returnNode;

    }


}

// My merge code
Node* PQueue::mergeNodes(Node *firstNode, Node *secondNode) {

    // Base cases, if there is ONLY secondNode
    if (!firstNode && secondNode)
        return secondNode;

        // Base case, if there is ONLY firstNode
    else if (firstNode and !secondNode)
        return firstNode;

        // Base case, if neither exist
    else if (!firstNode && !secondNode)
        return nullptr;

    else{

        // Compare Priorities

        // If the first priority passed is lower or equal, make it root
        if (priority(firstNode->getPatient()) < priority(secondNode->getPatient())){

            // Recursive call, but save min
            firstNode->_right = mergeNodes(firstNode->_right, secondNode);

            // Swap children
            Node *temp = firstNode->_left;
            firstNode->_left = firstNode->_right;
            firstNode->_right = temp;

            // Return the lower priority
            return firstNode;

        }

            // Else the second Node has a better prioirty and needs to be save
        else {

            // Recursive call, but save second Node
            secondNode->_right = mergeNodes(firstNode, secondNode->_right);

            // Swap children
            Node *temp = secondNode->_left;
            secondNode->_left = secondNode->_right;
            secondNode->_right = temp;

            // Return the lower priority
            return secondNode;

        }

    }

}

// Print one way, tree structure
// inorder traversal
void PQueue::printTree(Node *toPrint) const {

    // If nothing to print
    if (!toPrint)
        return;

        // Else print in this order
    else {

        cout << "(";

        printTree(toPrint->_left);

        cout << priority(toPrint->_patient) << ":" << toPrint->getPatient().getPatient();

        printTree(toPrint->_right);

        cout << ")";

    }

}

// Print another way, info
// Preorder travesal
void PQueue::printNode(Node *toPrint) const {

    if (!toPrint){
        return;
    }

    else {
        cout << toPrint->getPatient() << endl;
        printNode(toPrint->_left);
        printNode(toPrint->_right);
    }
}