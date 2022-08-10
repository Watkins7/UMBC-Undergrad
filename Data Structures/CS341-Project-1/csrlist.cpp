/*
** File: csrlist.cpp
** Project: CMSC 341 Project 1, Fall 2020
** Author: William Atkins
** Date: 9/29/20
** Email: watkins7@umbc.edu
** Description: This is a csrlist.cpp for proj1 in 341 Fall 2020
** This can hold the class csr objects and can preform operations in the list
*/

// CMSC 341 - Fall 2020 - Project 1
#include "csrlist.h"

CSRList::CSRList(){
    /***********************************
     *      To be implemented
     * ********************************/
    m_head = nullptr;
    m_size = 0;

}

CSRList::~CSRList(){
    /***********************************
     *      To be implemented
     * ********************************/
    // Default destructor code
    CSR * p_node = m_head;
    while(m_head)
    {
        p_node = m_head;
        m_head = m_head->m_next;
        delete p_node;
    }


}

CSRList::CSRList(const CSRList & rhs){
    /***********************************
     *      To be implemented
     * ********************************/

    // Create m_size
    m_size = rhs.m_size;

    // If there is nothing to copy, return
    if (rhs.m_head == nullptr)
        return;

    // Node for this list
    CSR * p_node;
    // Node to copy
    CSR * toCopy = rhs.m_head;

    // Copy Information
    // Create a new m_head
    this->m_head = new CSR(*toCopy);
    p_node = m_head;

    // Move the passed_list node to start copying the rest of the list
    toCopy = toCopy->m_next;

    // While loop that runs through passed_list
    // Copys every node and inserts it into this list
    while (toCopy != nullptr){

        p_node->m_next = new CSR(*toCopy);

        p_node = p_node->m_next;
        toCopy = toCopy->m_next;
    }

    return;

}

bool CSRList::empty() const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
    if (!m_head)
        return true;
    else
        return false;
}

void CSRList::insertAtHead(const CSR & matrix){
    /***********************************
     *      To be implemented
     * ********************************/

    // Save m_head
    CSR* node = m_head;

    //Make new m_head, point to rest of the list
    m_head = new CSR(matrix);
    m_head->m_next = node;
    m_size++;


}

void CSRList::clear(){
    /***********************************
     *      To be implemented
     * ********************************/
    // Clear data
    m_size = 0;

    // Default destructor code
    CSR * p_node = m_head;
    while(m_head)
    {
        p_node = m_head;
        m_head = m_head->m_next;
        delete p_node;
        p_node = nullptr;
    }

    // have m_head point to null
    m_head = nullptr;

}

int CSRList::getAt(int CSRIndex, int row, int col) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // Out of bounds
    if (CSRIndex < 0 || CSRIndex >= m_size){
        throw out_of_range("Error: Object is not in the list!");
    }


    // Counts indexs in a list, and ptr to navigate the list
    int counter = 0;
    CSR* current = m_head;

    // Move current to index
    while(current != nullptr){

        // If counter equals the index we are looking for
        if (counter == CSRIndex){

            // else return the element
            return current->getAt(row,col);
        }

        // Up counter and move to the next node
        counter++;
        current = current->m_next;
    }

    // Throw error by default if reached this far
    throw out_of_range("Error: Element is out of bounds");

}

void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;

}

bool CSRList::operator== (const CSRList & rhs) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // Nodes to help compare data in both list
    CSR* thisNode = this->m_head;
    CSR* passedNode = rhs.m_head;

    // Edge case if there is nothing in both list
    if (m_head == nullptr and passedNode == nullptr)
        return true;

    // Silly edge cases, for if one head is null and the other one is not
    if (m_head != nullptr && rhs.m_head == nullptr)
        return false;

    if (m_head == nullptr && rhs.m_head != nullptr)
        return false;


    // If the two head in the list equal each other, we can compare the whole list
    if (*m_head == *rhs.m_head) {

        // Compare two list, return false if you dont match
        // Break while loop whenever either loop reaches null
        while (thisNode != nullptr && passedNode != nullptr) {
            // If nodes are the same, then move to the next
            if (*thisNode == *passedNode) {
                // Move nodes in the list
                thisNode = thisNode->m_next;
                passedNode = passedNode->m_next;
            }

                // If we ever find two nodes not the same, return false
            else
                return false;

        } // End of while loop comparing both lists

    } // End of if statement

        // Else the two heads are not equal to each other and we return false
    else
        return false;

    // By default return true
    return true;
}

const CSRList& CSRList::operator=(const CSRList & rhs){
    /***********************************
     *      To be implemented
     * ********************************/

    // Node for this list
    CSR * p_node;
    // Node to copy
    CSR * toCopy = rhs.m_head;

    // Copy new size
    m_size = rhs.m_size;

    // Delete this
    while(m_head) {
        p_node = m_head;
        m_head = m_head->m_next;
        delete p_node;
    }

    // Create a new m_head
    this->m_head = new CSR(*toCopy);
    p_node = m_head;

    // Code to copy the rest of the list
    toCopy = toCopy->m_next;
    while (toCopy != nullptr){

        p_node->m_next = new CSR(*toCopy);

        p_node = p_node->m_next;
        toCopy = toCopy->m_next;
    }

    return *this;

}

int CSRList::averageSparseRatio(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // Number of Nodes
    int numOfNodes = 0;
    int sum = 0;

    // Go through this list to add nodes
    CSR* current = m_head;

    // Go through whole list
    while (current != nullptr){

        // If current is not empty, add its sparse ratio
        if (!current->empty()) {
            // Add the sparse ratio, and up counter;
            sum += current->sparseRatio();
            numOfNodes++;
        }

        // Move current
        current = current->m_next;
    }

    // Return math
    return int (float (sum) / float(numOfNodes));
}