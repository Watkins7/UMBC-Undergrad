/*
** File: bNode.cpp
** Project: CMSC 341 Project 2, Fall 2020
** Author: William Atkins
** Date: 10/20/20
** Email: watkins7@umbc.edu
** Description: This is a bNode.cpp for proj2 in 341 Fall 2020
** This is a node that is used in bookTree, it contains a wordTree, parent, left child,
 * and right child.  It contains all the elements that a book might have.
*/

// CMSC 341 - Fall 2020 - Project 2
#include "bNode.h"
BNode::BNode(){}

BNode::BNode(string key, string author, string text){
    _key = key;
    _author = author;
    _left = nullptr;
    _right = nullptr;
    _flag = false;
    _parent = nullptr;
    createTextTree(text);
}

BNode::~BNode(){
      // Destructor, no memory allocation is required in this class.
}

void BNode::createTextTree(string text){
    istringstream iss(text);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
        _tree.insert(*it);
    }
}

int BNode::findFrequency(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
     //This function calls the corresponding function from WordTree class and returns the word's number of occurrences.
     // If the word is not found, the function returns zero.

     // Find word
     Node* wordToFind = _tree.find(word);

     // If found, return the number of off
     if (wordToFind){
         return wordToFind->getFrequency();
     }

     else
        return 0;

}

int BNode::searchCount(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
     // This function calls the corresponding function from WordTree class.
     return _tree.searchCount(word);
}

int BNode::getTextTreeHeight(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    //This function calls the corresponding function from WordTree class.
    return _tree.getRootHeight();
}

int BNode::getNodeHeight(string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     //This function calls the corresponding function from WordTree class.
     return _tree.getNodeHeight(word);
}