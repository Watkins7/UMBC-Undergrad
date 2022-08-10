/*
** File: bookTree.cpp
** Project: CMSC 341 Project 2, Fall 2020
** Author: William Atkins
** Date: 10/20/20
** Email: watkins7@umbc.edu
** Description: This is a bookTree.cpp for proj2 in 341 Fall 2020
** This is an SPLAY Tree of bNodes.  Inside this tree, there are many bNodes that are books.
 * Each bNode contains 1 wordTree, which is all the words for the book.  Only one same title
 * per bookTree tree.
*/

// CMSC 341 - Fall 2020 - Project 2

#include "bookTree.h"
BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
    /***********************************
     *      To be implemented
     * ********************************/
     // Clear root
     clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     /*This function performs the splay operation using rotations recursively.
      * It returns a new root everytime for the current sub-tree.
      * When the recursive calls end, the returned value would be the current root
      * of the splay tree. Then, we need to set the tree root to the returned value.
      */

     // return the last node in the list
     if (root ->_key == key || (root->_right == nullptr && _root->_left == nullptr)){
         return root;
     }

     else {

         // if root_key is less than passed key, move right
         if (root->_key <= key){
             root->_right = makeSplay(root->_right, key);

             // Rotate left up
             root = leftRotate(root);
             return root;
         }

         // else the root_key is bigger than the passed_key, move left
         else {
                 root->_left = makeSplay(root->_left, key);

                 // Rotate right up
                 root = rightRotate(root);
                 return root;
         }

     }

}

BNode* BookTree::rightRotate(BNode* x){
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
    BNode* parent = x;
    BNode* child = x->_left;

    // Save what child_right is pointing to
    BNode* child_right = child->_right;

    // Have child_rightSide point to parent
    child->_right = parent;

    // Have parent_leftside point to child_oldRightSide
    parent->_left = child_right;

    // Change parents
    child->_parent = parent->_parent;
    parent->_parent = child;

    // Check to see of parent left child exist, then set it's parent to parent
    if (parent->_left)
    {
        parent->_left->_parent = parent;
    }

    // Return new root;
    return child;

}

BNode* BookTree::leftRotate(BNode* x){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    // This function performs left rotation around aNode
    // and returns the new root for the current sub-tree.
    BNode* parent = x;
    BNode* child = x->_right;

    // Save what child_left is pointing to
    BNode* child_left = child->_left;

    // Have child_leftSide point to parent
    child->_left = parent;

    // Have parents_rightside point to child's_oldLeftSide
    parent->_right = child_left;

    // Change parents
    // ADDED AFTER INTIAL TESTS
    child->_parent = parent->_parent;
    parent->_parent = child;

    // Check to see of parent right child exist, then set it's parent to parent
    if (parent->_right)
    {
        parent->_right->_parent = parent;
    }

    // Return new root;
    return child;

}

bool BookTree::insert(string key, string author, string text){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     /*
     * This function inserts the data for a book title into the splay tree.
      * If the title already exists, it does not insert a duplicate and it returns false.
      * Otherwise it insertes the title and returns true.
     */

     // if the root is null, set a new _root
     if (_root == nullptr){
         _root = new BNode(key, author, text);
         return true;
     }

     // Search to see of title exists
     BNode* temp = _root;
     BNode* parent = temp;
     while (temp != nullptr) {

         // Set parent equal to temp
         parent  = temp;

         // Search for the key, if it exists return false
         if (temp->_key == key){
             return false;
         }

         // if the key you are looking for is more than the current key, move right
         if (temp->_key < key){
             temp = temp->_right;
         }

         // else move left
         else {
             temp = temp->_left;
         }

     }

     // If the key is bigger than the parent's key, set new parents right
     if (key >= parent->_key){
         parent->_right = new BNode(key, author, text);
     }

     // Else the key is less than the parent's key
     else {
         parent->_left = new BNode(key, author, text);
     }

     // Splay the bookTree
     _root = makeSplay(_root, key);

     return true;
}

void BookTree::clear(BNode* root){
    /***********************************
     *      To be implemented
     * ********************************/

    // If the node passed exists, delete it
    if (root){

        // Have it call this function on its children
        clear(root->_left);
        clear(root->_right);

        // Then delete yourself, and praise nullptr
        delete root;
        root = nullptr;
    }
}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
    /***********************************
    *      Do not modify
    * ********************************/
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
            root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
            inorderHelp( root->_left, verbose );
            cout << root->_key;
            inorderHelp( root->_right, verbose );
        }
    }
}

void BookTree::dump(bool verbose) const{
    /***********************************
    *      Do not modify
    * ********************************/
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     /* This function returns the number of occurrences of the word for a book title.
      * The number of occurrences is stored in the nodes of WordTree.
        Note: This operation tries to access a node in the splay tree, then it requires splay operation too.
     */

     // while loop to through list and get count
    BNode* temp = _root;
    int count = 0;
    while (temp != nullptr){

        // If title is found
        if (title == temp->_key){

            // Get number of occurances
            count = temp->findFrequency(word);

            // Splay temp
            _root = makeSplay(_root, title);

            // Return number of occurances
            return count;

        }

        // If the title_passed is bigger than the temp key, move right
        if (title >= temp->_key){
            temp = temp->_right;
        }

        // move left instead
        else {
            temp = temp->_left;
        }

    }

    cout << "Error findFrequency: We could not find " << title << " in this bookTree" << endl;
    return 0;

}

void BookTree::dumpTitle(string title){
    /***********************************
     *      To be implemented
     * ********************************/

     /* This function prints out the list of all nodes in the word tree of a book title.
      * The word is printed along with its number of occurrences and its height in the tree.
      * An example of the output is provided in the Additional Requirements section below.
        Note: This function tries to access a node in the splay tree. Then, it requires splay operation too.
      */

     // While loop to see if title is in the list
    BNode* temp = _root;
    while (temp != nullptr){

        // If title is found
        if (title == temp->_key){

            // Print wordTree
            temp->_tree.dump();

            // Splay temp
            _root = makeSplay(_root, title);

            // Return after finding
            return;

        }

        // If the title_passed is bigger than the temp key, move right
        if (title >= temp->_key){
            temp = temp->_right;
        }

        // move left instead
        else {
            temp = temp->_left;
        }

    }


    cout << "Error dumpTitle: We could not find " << title << " in this bookTree" << endl;

}

int BookTree::searchCount(string title, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

     /*
      * This function returns the number of visited nodes in the WordTree when searching for a word.
      * It starts at zero when visiting root, then the path from root to its child counts as one,
      * and it continues until the word is found or is not found.
        Note: This operation tries to access a node in the splay tree,
        then it requires splay operation too.
        If the title does not exist in the splay tree, the function returns zero,
        otherwise it returns the number of operations that happen in the AVL tree.
        This function does not count the number of operations in the splay tree.
      *
      */

    // While loop to see if key is in the list
    BNode* temp = _root;
    while (temp != nullptr){

        // If title is found
        if (title == temp->_key){

            //  Get the search count for the word
            int searchCount = temp->searchCount(word);

            // Splay temp
            _root = makeSplay(_root, title);

            // Return Search count
            return searchCount;

        }

        // If the title_passed is bigger than the temp key, move right
        if (title >= temp->_key){
            temp = temp->_right;
        }

            // move left instead
        else {
            temp = temp->_left;
        }

    }

     cout << "Error searchCount: We could not find " << title << " in this bookTree" << endl;
     return 0;
}

int BookTree::getTextTreeHeight(string title){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    /*
     * This function returns the height of the word tree for a book title.
        Note: This function tries to access a node in the splay tree.
        Then, it requires splay operation too.
     */

    // While loop to see if key is in the list
    BNode* temp = _root;
    while (temp != nullptr){

        // If title is found
        if (title == temp->_key){

            // Get height of word node
            int wordTreeHeight = temp->getTextTreeHeight();

            // Splay temp
            _root = makeSplay(_root, title);

            return wordTreeHeight;

        }

        // If the title_passed is bigger than the temp key, move right
        if (title >= temp->_key){
            temp = temp->_right;
        }

        // move left instead
        else {
            temp = temp->_left;
        }

    }

    cout << "Error getTextTreeHeight: We could not find " << title << " in this bookTree" << endl;
    return -1;

}

int BookTree::getWordHeight(string title, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

    /*
        This function returns the height of the word node in the word tree of a book title.
        Note: This function tries to access a node in the splay tree.
        Then, it requires splay operation too.
     */

    //While loop to see if key is in the list
    BNode* temp = _root;
    while (temp != nullptr){

        // If title is found
        if (title == temp->_key){

            // Get height of word node
            int wordHeight = temp->getNodeHeight(word);

            // Splay temp
            _root = makeSplay(_root, title);

            return wordHeight;

        }

        // If the title_passed is bigger than the temp key, move right
        if (title >= temp->_key){
            temp = temp->_right;
        }

            // move left instead
        else {
            temp = temp->_left;
        }

    }


    cout << "Error getWordHeight: We could not find " << title << " in this bookTree" << endl;
    return -1;
}

string BookTree::getRootKey(){
    /***********************************
    *      Do not modify
    * ********************************/

    // If there is a root, return the key, otherwise say it is empty
    if (_root){
        return _root->_key;
    }

    else{
        return "This tree is empty";
    }
}

void BookTree::loadData(string dataFile){
    /***********************************
    *      This function is implemented
    *      to help you. You should't need
    *      to modify it.
    * ********************************/
    //read the entire file at once
    std::ifstream t(dataFile);
    std::stringstream buffer;
    buffer << t.rdbuf();

    //time to parse the information
    string titleDelimiter = "<==>";
    string itemsDeleimiter = "<=>";
    string s = buffer.str();
    size_t pos = 0;
    string token;
    while ((pos = s.find(titleDelimiter)) != string::npos) {
        token = s.substr(0, pos);//token is complete data for one title
        //get the title
        int tempPos = token.find(itemsDeleimiter);
        string title = token.substr(0,tempPos);
        //convert title to lower case
        std::transform (title.begin(), title.end(), title.begin(), ::tolower);
        token.erase(0, tempPos + itemsDeleimiter.length()+1);
        //get the author
        tempPos = token.find(itemsDeleimiter);
        string author = token.substr(0,tempPos);
        //convert author to lower case
        std::transform (author.begin(), author.end(), author.begin(), ::tolower);
        token.erase(0, tempPos + itemsDeleimiter.length()+1);
        //get the text
        string text = token.substr(0,token.length() - 1);//remove last newline
        //clean up the text, remove all non-alphanumeric characters
        for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
            if( !std::isalnum(*iter) && *iter != ' ')
                iter = text.erase(iter) ;
            else
                ++iter ; // not erased, increment iterator
        }
        //convert text to lower case
        std::transform (text.begin(), text.end(), text.begin(), ::tolower);

        insert(title,author,text);

        //move to info for the next title
        s.erase(0, pos + titleDelimiter.length()+1);
    }
}