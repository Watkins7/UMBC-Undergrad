/*
** File: LL.cpp
** Project: CMSC 202 Project 5, Spring 2020
** Author: William Atkins
** Date: 5/5/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a templated linked list for project 5 in CMSC 202
** Each node holds a pair with a "data type" and "int"
** This .cpp also holds functions on how to handle the linked list
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:

    Node( const T& data ); //Node Constructor - Assume each quantity

    pair<T,int>& GetData(); //Node Data Getter

    void SetData( const pair<T,int>& ); //Node Data Setter

    Node<T>* GetNext(); //Node m_next getter

    void SetNext( Node<T>* next ); //Node m_next setter


private:

    // Holds "type T" and an "integer"
    pair <T,int> m_data; //Holds templated data

    Node<T>* m_next; //Pointer to next node

};


//***************************************************************
// <T> Template class implemeted here
//***************************************************************
template <class T>
Node<T>::Node( const T& data ) {

    m_data = make_pair(data,1);
    m_next = nullptr;

}

template <class T>
pair<T,int>& Node<T>::GetData() {

    return m_data;

}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {

    m_data = data;

}

template <class T>
Node<T>* Node<T>::GetNext() {

    return m_next;

}

// Function to set next node in the list
// Passes the next node, and sets "this_node" to points "m_next" to the node passed
template <class T>
void Node<T>::SetNext( Node<T>* next ) {

    m_next = next;

}



//Templated Linked List class
template <class T>
class LL {
public:

    // Name: LL() (Linked List) - Default Constructor
    // Desc: Used to build a new linked list
    // Preconditions: None
    // Postconditions: Creates a new linked list where m_head points to nullptr
    LL();

    // Name: ~LL() - Destructor
    // Desc: Used to destruct a LL
    // Preconditions: There is an existing LL with at least one node
    // Postconditions: A LL is deallocated (including dynamically allocated nodes)
    //                 to have no memory leaks!
    ~LL();

    // Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
    LL(const LL&);

    // Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
    LL<T>& operator= (const LL&);

    // Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
    Node<T>* Find(const T& data);

    // Name: Insert
    // Desc: Either inserts a node to the linked list OR increments frequency of first
    //       Takes in data. If "first" (of pair) NOT in list, adds node
    //       If "first" (of pair) is already in list, increments quantity
    //       Inserts "first" in order with no duplicates
    // Preconditions: Requires a LL.
    // Postconditions: Node inserted in LL based on first value (or quantity incremented)
    void Insert(const T&);

    // Name: RemoveAt
    // Desc: Removes a node at a particular position based on data passed (matches first)
    // Preconditions: LL with at least one node.
    // Postconditions: Removes first node with passed value (in first)
    void RemoveAt(const T&);

    // Name: Display
    // Desc: Display all nodes in linked list
    // Preconditions: Outputs the LL
    // Postconditions: Displays the pair in each node of LL
    void Display();

    // Name: GetSize
    // Desc: Returns the size of the LL
    // Preconditions: Requires a LL
    // Postconditions: Returns m_size
    int GetSize();

    // Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
    template <class U>
    friend ostream& operator<<(ostream& output, const LL<U>&);

    // Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
    pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL



private:
    Node<T> *m_head; //Node pointer for the head
    int m_size; //Number of nodes in queue
};




/********************************************************************************************************

        Implement LL here

********************************************************************************************************/

// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL() {

    // Set m_head to point to nullptr
    m_head = nullptr;
    m_size = 0;

}


// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL(){

    // Variables need to help traverse the list and help delete items
    Node<T> *previous;  // Keeps track of previous node
    Node<T> *current = m_head;  // Keeps track of current node

    // Run through list, and delete all items, do this until we reach nullptr
    while (current != nullptr){

        // Set previous equal to current
        previous = current;

        // Move current
        current = current->GetNext();

        // Delete previous
        delete previous;
        previous = nullptr;

    }

}

// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL
template <class T>
LL<T>& LL<T>::operator=(const LL& passedList){

    // Step 1: Delete everything in the link list
    // Step 2: Copy and paste constructor code

    //  As long as passed list is not this list
    if (&passedList != this) {

        // Variables need to help traverse the list and help delete items

        Node<T> *current = m_head; // Pointer for this list, keeps track of a current pointer for the linked list
        Node<T> *previous = current; // Pointer for this list, Used to delete items in this list

        Node<T> *currentPassedNode = passedList.m_head;  // Pointer for passed_list, Keeps track of current node, in passed_list
        Node<T> *previousNode = passedList.m_head; // Pointer for passed_list, Keeps track of previous node, in passed_list

        Node<T> *newNode; //  For this list, New dynamically allocated node


        // While loop to delete all items in the list
        while (current != nullptr) {

            // Set previous equal to current
            previous = current;

            // Move current
            current = current->GetNext();

            // Delete previous
            delete previous;
            previous = nullptr;

        }

        // if the passed_list is empty, make an empty list and then return this
        if ( passedList.m_head == nullptr ) {

            m_head = nullptr;
            return *this;

        }

        // Create a new node, copy the data from the old m_head
        // set this m_head to new node
        newNode = new Node<T>( passedList.m_head->GetData().first );

        // Set data for the new node
        newNode->SetData(previousNode->GetData());

        // Set new m_head
        m_head = newNode;

        // Moves currentPassed_listNode to the next item in it's list
        currentPassedNode = currentPassedNode->GetNext();

        // Set previous node equal to m_head
        current = m_head;

        // Go through the whole passed list until we reach nullptr
        while (currentPassedNode != nullptr) {

            // Create new dynamically allocated object
            newNode = new Node<T>( passedList.m_head->GetData().first );

            // Set the approriate data for the node, using the data from passed_list
            newNode->SetData(currentPassedNode->GetData());

            // Set the current to point to newNode
            current->SetNext(newNode);

            // Move current node, so that current is the newNode
            current = newNode;

            // Move the currentPassed_listNode
            currentPassedNode = currentPassedNode->GetNext();

        }
    }

    // Finally return this object
    return *this;


}


// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL( const LL& passedList) {

    Node<T> *currentPassedNode = passedList.m_head;  // Node for passed_list, Node need to help traverse the list and copy other nodes

    Node<T> *previousNode; // Node for this list, Keeps tack of previous last known node

    // Just by default have m_head point to nullptr
    m_head = nullptr;

    // if, by some miracle, m_head in passed_list points to nullptr, then just return because we are dealing
    // ...with an empty list
    if ( passedList.m_head == nullptr) {
        return;
    }


    //  Create a new dynamically allocated node
    Node<T> *newNode = new Node<T>( passedList.m_head->GetData().first );

    // Copy the data from the old m_head
    newNode->SetData( currentPassedNode->GetData() );

    // Have m_head point to the newNode
    m_head = newNode;

    // Move currentNode
    currentPassedNode = currentPassedNode->GetNext();

    // Set previous node equal to m_head
    previousNode = m_head;

    while (currentPassedNode != nullptr){

        // Create new dynamically allocated object
        newNode = new Node<T>( passedList.m_head->GetData().first );
        // Set data for new node
        newNode->SetData( currentPassedNode->GetData() );
        // Have previous node point to newNode
        previousNode->SetNext( newNode );
        // Move previousNode to newNode
        previousNode = previousNode->GetNext();


        // Move the currentPassedNode
        currentPassedNode = currentPassedNode->GetNext();
    }



}


// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T& newNode){

    Node<T> *current = m_head;  // Needed to help traverse the list
    Node<T> *previous = m_head;  // Needed to help traverse the list

    // Sets m_head point to newNode, only if nothing is in the list
    if (m_head == NULL) {

        // Create a new dynamically allocated Node, passed whatever value the user passd
        Node<T> *dynamicNode = new Node<T>(newNode) ;

        // Have m_head point to it
        m_head = dynamicNode;

        // Up size then return
        m_size++;
        return;

    }

    // Else, the list is populated
    else {

        Node<T> *temp = m_head; // New temparory pointer to help traverse the list

        // Find if item is in the list, then update second
        // Go through whole list to search for the item
        while (temp != nullptr) {

            // if the "first" equals the word, just update second
            if (temp->GetData().first == newNode) {

                //  up counter for item
                temp->GetData().second++;

                // Return after updating second
                return;
            }

            // Continue to next, if item is not found
            temp = temp->GetNext();

        }

        // Reset temp
        temp = m_head;

        //  ****************************************************************************************
        //  If we have reach this far, that means that we need to insert this word in the list
        //  Start at m_head and find when "passed_data" is less than "temp"


        // Case for if "item" is less than "m_head"
        // If so, than word should be at the front
        if (newNode < temp->GetData().first) {

            // Set the new m_head
            m_head = new Node<T>(newNode);

            // Have new m_head point to old m_head
            m_head->SetNext(temp);

            // up size
            m_size++;

        }

        // else we need to search in the list on where to put the "item"
        else {

            // Move current one time to the next item
            current = current->GetNext();

            // Move temp all the way down to the last item of the list
            while (current != nullptr){

                // If and when we finally get WORD to be less than CURRENT
                // Set linked list to: previous->word->current
                if (newNode < current->GetData().first) {

                    // Save current pointer information
                    temp = current;

                    // Have previous point to new node
                    previous->SetNext( new Node<T>(newNode) );

                    // Have new node point to current
                    previous->GetNext()->SetNext(temp);

                    // Up list size
                    m_size++;

                    // return
                    return;

                }

                // Set previous equal to current
                previous = current;

                // move current
                current = current->GetNext();
            }

            // else, if we have gotten this far, we just add word to the end of the list
            previous->SetNext(new Node<T>(newNode));

            // up list size
            m_size++;

        }

    }



}


// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the L3L
// Postconditions: Displays the pair in each node of LL
template <class T>
void LL<T>::Display(){

    Node<T> *temp = m_head;  // Temporary node to help traverse the list

    // While we are not at the end of the list
    while (temp != nullptr){

        // cout data
        cout << temp->GetData().first << ":" << temp->GetData().second << endl;

        // get next node in the list
        temp = temp->GetNext();

    }

}


// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T>* LL<T>::Find(const T& data){

    // Temporary node to help traverse list
    Node<T> *temp = m_head;

    // Traverse the list and find if we can find the item
    while (temp != nullptr){

        // If we find it, return the node
        if (data == temp->GetData().first)
            return temp;

        temp = temp->GetNext();

    }

    // Else by default return nullptr
    return nullptr;

}


// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node.
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& nodeName){

        Node<T> *previous = m_head; // Node to help traverse the list
        Node<T> *current = m_head->GetNext(); // Node to help traverse the list

        // If user selected the first node to delete, remove m_head
        if ( nodeName == m_head->GetData().first ) {

            // Delete m_head then reassign the pointer
            delete m_head;
            m_head = current;

            // Lower size count, then return
            m_size--;
            return;

        }


        // While loop to help traverse the list
        while (current != nullptr) {


            // If we find the "item"...then delete it and return
            if (nodeName == current->GetData().first){

                // Have previous point to where current was pointing to
                // (Have previous point around current)
                previous->SetNext( current->GetNext() );

                // delete current
                delete current;
                current = nullptr;

                // Lower size, and then return
                m_size--;
                return;

            }

            // Move previous to point to current
            previous = current;

            // Get next node for current
            current = current->GetNext();
        }

        cout << "Opps, we failed to delete the node chosen." << endl;


}


// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream &output, const LL<U> &thing) {


    Node<U> *temp = thing.m_head; // Temporary node to help traverse the list

    // while loop to traverse the whole list and help return info
    while (temp != nullptr){

        // cout data
        output << temp->GetData().first << ":" << temp->GetData().second << endl;

        // get next node in the list
        temp = temp->GetNext();

    }

    // Finally, return the output
    return output;

}


// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
//Overloaded [] operator to pull data from LL
pair<T,int>& LL<T>::operator[] (int x){

    Node<T> *temp = m_head; // temporary node to help traverse the list to find an item at index "x"
    int counter = 0;  // helps to get info at index "x"

    // if x is out of bounds
    if ( x < 0 or x > m_size){
        cout << "Could not get that pair.  Instead we gave you m_head.  The value of X is " << x << endl;
        return m_head->GetData();
    }

    // While loop, using a counter, we cycle through the list until we get index "x"
    while (temp != nullptr){

        // if counter matches the integer passed, return the data at the location
        if (counter == x){
            return temp->GetData();
        }

        // Up counter and move temp
        counter++;
        temp = temp->GetNext();

    } // End of while


    // Return m_head by default
    cout << "Returning m_head by default" << endl;
    return m_head->GetData();

}

// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize(){ return m_size; }


//****************************************************************
// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)

/*
int main () {
  //Test 1 - Default Constructor and Push
  cout << "Test 1 - Default Constructor and Push Running" << endl;
  //Test Default Constructor
  LL <string>* newLL1 = new LL<string>();
  //Push 4 nodes into LL
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Insert("candy");
  newLL1->Insert("cookies");
  newLL1->Insert("candy");
  newLL1->Insert("bananas");
  newLL1->Insert("dogs");
  newLL1->Insert("apples");
  newLL1->Insert("elephants");
  newLL1->Insert("barf");
  newLL1->Display();

  //  delete newLL1;

  //Test 2 - Copy Constructor and Assignment Operator
  cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
  //Test Copy constructor
  LL <string>* newLL2 = new LL<string>(*newLL1);
  cout << "*******Original*********" << endl;
  newLL1->Display();
  cout << "*******Copy*********" << endl;
  newLL2->Display();

  //Test Overloaded Assignment Operator
  LL <string>* newLL3 = new LL<string>();
  newLL3 = newLL1;
  cout << "*******Assignment*********" << endl;
  newLL3->Display();
  cout << endl;

  //Test 3 - Test Display and Overloaded <<
  cout << "Test 3 - Display and Overloaded << Running" << endl;
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();
  cout << "newLL1 Overloaded" << endl;
  cout << *newLL1;
  cout << "RemoveAt(candy)" << endl;
  newLL1->RemoveAt("candy");
  cout << "newLL1 Display Function" << endl;
  newLL1->Display();

  return 0;
}
*/


