/*
** File: wordTree.cpp
** Project: CMSC 341 Project 2, Fall 2020
** Author: William Atkins
** Date: 10/20/20
** Email: watkins7@umbc.edu
** Description: This is a wordTree.cpp for proj2 in 341 Fall 2020
** This is an AVL Tree of words in a book
*/

// CMSC 341 - Fall 2020 - Project 2

#include "wordTree.h"

WordTree::~WordTree(){
    /***********************************
     *      To be implemented
     * ********************************/
    // Find the beginning of the AVL tree
    Node* start = _root;

    // Clear the tree and deallocate memory
    clearTree(start);

}

void WordTree::updateHeight(Node *aNode) {
    /***********************************
      *      To be implemented
      * ********************************/

      /*
       * This function recalculates and updates the height of aNode.
        Note: The childern which are nullptr hold a height of -1.
        The lowest level nodes with a key value hold the height 0.
       */

       // If the children point to nullptr (-1)
       // Set height to (-1) + (1) = 0
       if(!aNode->_left and !aNode->_right){
           aNode->_height = 0;

           // We updated, now we return
           return;
       }

       // If both node exist
       if (aNode->_left and aNode->_right) {

           // If right side height bigger/equal than left
           if (aNode->_right->getHeight() >= aNode->_left->getHeight()){

               // Set height equal to right side + 1
               aNode->_height = aNode->_right->getHeight() + 1;

           }

           // Else the left side is bigger and we set the height equal to that (+1)
           else {
               aNode->_height = aNode->_left->getHeight() + 1;
           }

           // We updated the height now return;
           return;

       }

       // Else if only the left node
       // Set height to the leftside + 1
       else if (aNode->_left and !aNode->_right){
           aNode->_height = aNode->_left->getHeight() + 1;

           // We updated, now return
           return;
       }

       // Else is only the right node
       // Set height to the rightside + 1
       else if(aNode->_right and !aNode->_left){
           aNode->_height = aNode->_right->getHeight() + 1;

           // We updated, now return
           return;
       }

}

void WordTree::clearTree(Node* aNode){
    /***********************************
     *      To be implemented
     * ********************************/
    // Destroys recursively based on location in the tree

    // If node exists
     if (aNode){

         // Have it call this function on its children
         clearTree(aNode->_left);
         clearTree(aNode->_right);

         // Then delete yourself, and praise nullptr
         delete aNode;
         aNode = nullptr;
     }

}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // This function finds a node using the provided key and returns the node.
    // aNode is a subTree that we need to look for the value
    // Function is recursive

    // Base case, if aNode is nullptr
    if (!aNode){
        return nullptr;
    }

    // Base case, we find it
    if (element == aNode->_value){
        return aNode;
    }

    // Recursive call if element is less than current
    // Move left
    else if (element < aNode->_value){

        //i89hjynnh
        // My injured cat typed this and I wont remove it

        return find(aNode->_left, element);
    }

    // Recursive call if element is greater than current
    // Move right
    else //(element > aNode->_value){
        return find(aNode->_right,element);


}

Node* WordTree::find(const string& element){
    /***********************************
     *      To be implemented
     * ********************************/

    // This function finds a node using the provided key and returns the node.
    return find(_root,element);

}

Node* WordTree::leftRotation(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // This function performs left rotation around aNode
    // and returns the new root for the current sub-tree.
    Node* C = aNode;
    Node* B = aNode->_right;

    // Save what B_left is pointing to
    Node* B_left = B->_left;

    // Have B_leftSide point to C
    B->_left = C;

    // Have C_rightside point to B_oldLeftSide
    C->_right = B_left;

    // Change parents
    // ADDED AFTER INTIAL TESTS
    B->_parent = C->_parent;
    C->_parent = B;

    if (C->_right)
    {
        C->_right->_parent = C;
    }

    // Update Heights
    updateHeight(C);
    updateHeight(B);

    // Return new root;
    return B;

}

Node* WordTree::rightRotation(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // This function performs right rotation around aNode
    // and returns the new root for the current sub-tree.

    // Node for switching
    Node* C = aNode;
    Node* B = aNode->_left;

    // Save what B_right is pointing to
    Node* B_right = B->_right;

    // Have B_rightSide point to C
    B->_right = C;

    // Have C_leftside point to B_oldRightSide
    C->_left = B_right;

    // Change parents
    B->_parent = C->_parent;
    C->_parent = B;

    // If C's left exist, have its parents become c
    if (C->_left)
    {
        C->_left->_parent = C;
    }

    // Update Heights
    updateHeight(C);
    updateHeight(B);

    // Return new root;
    return B;
}

int WordTree::checkBalance(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
    /*
     * This function returns the height difference between
     * left child and right child of aNode. If left child has a greater height,
     * it returns a positive number,
     * and if the right child has a greater height,
     * it returns a negative number.
     Note: The childern which are nullptr hold a height of -1.
     The lowest level nodes with a key value hold the height 0.
     */

    // Hold the left and right height
    int leftHeight, rightHeight;

    // Get right height
    if (!aNode->_right)
        // If it doesnt exist, -1
        rightHeight = -1;
    else
        rightHeight = aNode->_right->getHeight();


    // Get left height
    if (!aNode->_left)
        // If it doesnt exist, -1
        leftHeight = -1;
    else
        leftHeight = aNode->_left->getHeight();


    // Return the heights, + if left, - if right
    return (leftHeight-rightHeight);


}

Node* WordTree::reBalance(Node* aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
     /*
     * This function rebalances the AVL tree using the proper rotation operations when the tree becomes unbalanced.
     * For example, after inserting a new node, we need to check whether the tree becomes unbalanced.
     * If it is unbalanced we need to rebalance the tree using this function.
     * The function returns the new root for the current sub-tree.
     */

    // Find if we need to rebalance the leftside or rightside
    int balance = checkBalance(aNode);

    // If aNode balance is negative
    // aNode has more right nodes than left
    // reBalance to the left
    if (balance <= -2){

        // if the child on right has a negative inbalance, it means that "the true right" side has too many nodes
        if ( checkBalance(aNode->_right) < 0)
            aNode = leftRotation(aNode);

        // Else we need to preform a right rotation then left
        else {
            aNode->_right = rightRotation(aNode->_right);
            aNode = leftRotation(aNode);
        }

    }

    // if balance is positive that means that there are more left nodes than right
    // rebalance to the right
    else if (balance >= 2){

        // if the child on left still has a positive inbalance, it means that "the true left" side has too many nodes
        if ( checkBalance(aNode->_left) > 0)
            aNode = rightRotation(aNode);

        // Else we need to preform a left rotation then right
        else {
            aNode->_left = leftRotation(aNode->_left);
            aNode = rightRotation(aNode);
        }

    }

    return aNode;
}

void WordTree::insert(const string& element){
    /***********************************
     *      To be implemented
     * ********************************/

    //This function inserts the word in the tree.
    // Since, the tree is an AVL tree, it needs to rebalance the tree
    // and recalculate heights after insertion.
    // A duplicate key is not allowed.
    // In the case of duplicate insertion we only update the word count in the node.


    // If there is a _root, then we search through the tree
    if (_root){

        // See if element exists
        Node* doesExist = find(_root,element);

        // If the node doesnt exist with element
        if (!doesExist){

            // Call a recusive function that searches through the list
            // AND WILL HAVE TO INSERT, AND UP HEIGHT
            _root = insert(element,_root);

        }

        // Else the element exists in a node
        else{

            // Just update doesExist and return
            // Up count and return
            doesExist->_count++;
            return;

        }

    } // End of if statement to search through a populated tree

        // Else, there isn't a root, then we need to make one
        else {
            _root = new Node(element);
            _root->_count++;

            // root's parent = nullptr
            _root->_parent = nullptr;
        }

}

Node* WordTree::insert(const string& element, Node*& aNode){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // This is a helper function which is called by the public insert(...) function
    // and inserts a new node with element as key.
    // A duplicate key is not allowed.
    // In the case of duplicate insertion we only update the word count in the node.

    // Recursive backwords...

    // Base case, node passed is null, make NEW NODE
    if (!aNode){
        Node* newNode = new Node(element);
        newNode->_count++;

        // Return the newNode
        return newNode;
    }

    // Recursive case
    else {

        // move left when element is less
        if (element < aNode->_value) {

            // Recursive call
            aNode->_left = insert(element, aNode->_left);

            // Set new parent
            aNode->_left->_parent = aNode;
        }

        // Move right when element is more
        else {

            // Recursive call
            aNode->_right = insert(element,aNode->_right);

            // Set new parent
            aNode->_right->_parent = aNode;
        }

            // FOR ALL ANODES
            // Returning back through the list

            // Update height
            updateHeight(aNode);

            // Check if unbalanced children
            if (checkBalance(aNode) <= -2 or checkBalance(aNode) >= 2) {

                // Rebalance Tree code
                aNode = reBalance(aNode);
            }

            // return aNode;
            return aNode;

        } // End of the recursive case

    }  // End of function

void WordTree::dump(std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    /*
     *  This function returns the number of visited nodes in the WordTree when searching for a word.
     *  It starts at zero when visiting root, then the path from root to its child counts as one,
     *  and it continues until the word is found or is not found.
     */

    return searchCountHelp(_root, word, 0);
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    /*
     * The helper function that returns the number of visited nodes in the AVL when searching for a word.
     * It starts at zero when visiting root,
     * then the path from root to its child counts as one,
     * and it continues until the word is found or is not found.
     */

    // While loop that will go through the whole tree trying to find "word"
    while (aNode != nullptr){

        // If we found the word, return how many steps it took
        if (aNode->_value == word){
            return counter;
        }

        // If the word is bigger that aNode's value
        // Move right
        if (aNode->_value <= word) {
            aNode = aNode->_right;
            counter++;
        }

        // Else move left
        else {
            aNode = aNode->_left;
            counter++;
        }

    }

    // Return how many paths taken
    return counter;

}

int WordTree::getRootHeight(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // if root, return height
    if (_root)
    {
        return _root->_height;
    }

    //else height is 0
    return -1;
}

int WordTree::getNodeHeight(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // Call helper function
    return getNodeHeightHelp(_root,word);
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // The helper function that looks recursively for the node
    // with the key value word and returns its height.
    // If the node is not found the function returns -1.
    // Note: The height of null children is -1.

    // Find the node we want
    Node* nodeToFind = find(word);

    // If we found the node, return its height
    if (nodeToFind){
        return nodeToFind->_height;
    }

    // Else by default return -1
    else
        return -1;
}