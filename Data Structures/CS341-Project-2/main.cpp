/*
** File: driver.cpp
** Project: CMSC 341 Project 2, Fall 2020
** Author: William Atkins
** Date: 10/20/20
** Email: watkins7@umbc.edu
** Description: This is the driver for Project 2 in CSMC 341.
 * It runs all the tests for bNode, bookTree and wordTree.
*/

// CMSC 341 - Fall 2020 - Project 2

#include "bookTree.h"
//#include "wordTree.h"

#include "iostream"

using namespace std;

int main(){

    // Pregiven Test

    cout << "//////////////////////////////////    Given Test    //////////////////////////////////////////////" << endl;

    BookTree aTree;
    aTree.loadData("data.txt");

    cout << "Frequency of tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.findFrequency("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Count of search operation for tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.searchCount("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Height of the node containing tinsmith in The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.getWordHeight("the wonderful wizard of oz","tinsmith") << endl << endl;
    cout << "Height of word tree for The Wonderful Wizard of Oz: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("the wonderful wizard of oz") << endl << endl;
    cout << "Dumping the word tree for The Wonderful Wizard of Oz:" << endl << endl;
    aTree.dumpTitle("the wonderful wizard of oz");
    cout << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << endl << "//////////////////////////////////   My Extra Test (SPLAY)     /////////////////////////////" << endl << endl;

    cout << "Output aTree:" << endl << endl;
    aTree.dump(false);
    cout << endl << endl;

    cout << "Current root of aTree: " << aTree.getRootKey() << endl << endl;

    cout << "Dump the word tree for Moby Dick:" << endl << endl;
    aTree.dumpTitle("moby dick");

    cout << endl << endl << "New root for aTree: " << aTree.getRootKey() << endl;
    cout << endl << "Dumping aTree:" << endl << endl;
    aTree.dump(false);
    cout << endl << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << endl << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "Try to do operations on a book that does not exist in aTree: " << endl << endl;

    cout << "Frequency of tinsmith in The Wonderful Wizard of Thaddeus: " << endl;
    cout << "\t" << aTree.findFrequency("the wonderful wizard of thaddeus","tinsmith") << endl << endl;
    cout << "Count of search operation for tinsmith in The Wonderful Wizard of Thaddeus: " << endl;
    cout << "\t" << aTree.searchCount("the wonderful wizard of thaddeus","tinsmith") << endl << endl;
    cout << "Height of the node containing tinsmith in The Wonderful Wizard of Thaddeus: " << endl;
    cout << "\t" << aTree.getWordHeight("the wonderful wizard of thaddeus","tinsmith") << endl << endl;
    cout << "Height of word tree for The Wonderful Wizard of Thaddeus: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("the wonderful wizard of thaddeus") << endl << endl;
    cout << "Dumping the word tree for The Wonderful Wizard of Thaddeus:" << endl << endl;
    aTree.dumpTitle("the wonderful wizard of thaddeus");
    cout << endl;

    cout << "Recheck current root of aTree, should be Moby Dick: " << aTree.getRootKey() << endl << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << endl << "---------------------------------------------------------------------------------------------------" << endl;
    cout << "With a known book in aTree, try to find a word that doesn't exist: " << endl << endl;

    cout << "Frequency of thaddeus in The Brothers Karamazov: " << endl;
    cout << "\t" << aTree.findFrequency("the brothers karamazov","thaddeus") << endl;
    cout << "Recheck current root of aTree, should be the brothers karamazov: " << aTree.getRootKey() << endl << endl;

    cout << "Count of search operation for thaddeus in Pride and Prejudice: " << endl;
    cout << "\t" << aTree.searchCount("pride and prejudice","thaddeus") << endl;
    cout << "Recheck current root of aTree, should be pride and prejudice: " << aTree.getRootKey() << endl << endl;

    cout << "Height of the node containing thaddeus in The Masque of the Red Death: " << endl;
    cout << "\t" << aTree.getWordHeight("the masque of the red death","thaddeus") << endl;
    cout << "Recheck current root of aTree, should be the masque of the red death: " << aTree.getRootKey() << endl << endl;

    cout << "Height of word tree for A Tale of Two Cities: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("a tale of two cities") << endl << endl;
    cout << "Recheck current root of aTree, should be a tale of two cities: " << aTree.getRootKey() << endl << endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout << endl << "//////////////////////////////////   My Test (AVL TREE)   //////////////////////////////////" << endl << endl;
    WordTree thisTree;
    thisTree.insert("cherry");
    thisTree.insert("apple");
    thisTree.insert("plum");
    thisTree.insert("banana");
    thisTree.insert("apple");
    thisTree.insert("orange");
    thisTree.insert("tomato");

    cout << "Output should be:  " << "[[apple:2:1[banana:1:0]]cherry:1:2[[orange:1:0]plum:1:1[tomato:1:0]]]" << endl;
    cout << "Actual Output:     ";
    thisTree.dump();
    cout << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Left rotation test
    WordTree leftRotationTree;
    leftRotationTree.insert("Applebees");
    leftRotationTree.insert("BBQ");
    leftRotationTree.insert("Cherry Fries");
    cout << "This test is for LEFT rotation" << endl;
    leftRotationTree.dump();
    cout << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Right rotation test
    WordTree rightRotationTree;
    rightRotationTree.insert("Carpenters");
    rightRotationTree.insert("Bananas Hamocks");
    rightRotationTree.insert("Awesome Sauce");
    cout << "This test is for RIGHT rotation" << endl;
    rightRotationTree.dump();
    cout << endl << endl;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Right Left rotation test
    WordTree rightLeftRotationTree;
    rightLeftRotationTree.insert("Bananas");
    rightLeftRotationTree.insert("Kiwi");
    rightLeftRotationTree.insert("Dates");
    cout << "This test is for RIGHT LEFT rotation" << endl;
    rightLeftRotationTree.dump();
    cout << endl << endl;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Left Right rotation test
    WordTree leftRightRotationTree;
    leftRightRotationTree.insert("Lemoncake");
    leftRightRotationTree.insert("Allison Atkins");
    leftRightRotationTree.insert("Brandon Kree");
    cout << "This test is for LEFT RIGHT rotation" << endl;
    leftRightRotationTree.dump();
    cout << endl << endl;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WordTree rotationTree;
    rotationTree.insert("Lemons");
    rotationTree.insert("Lemons");
    rotationTree.insert("Apples");
    rotationTree.insert("Bananas");
    rotationTree.insert("Tree");

    // Duplicates
    rotationTree.insert("Tupa");
    rotationTree.insert("Tupa");
    rotationTree.insert("Apricot");
    rotationTree.insert("Apricot");

    rotationTree.insert("Avacado");
    rotationTree.insert("Fig");
    rotationTree.insert("Farkleberry");
    rotationTree.insert("Fingleberry");
    rotationTree.insert("Evergreen");

    // Duplicates
    rotationTree.insert("Tree");
    rotationTree.insert("Tupa");
    rotationTree.insert("Apricot");
    rotationTree.insert("Avacado");

    cout << "This test is for a huge rotation!!!" << endl;
    cout << "Root with height of 3: should be Fig." << endl;
    cout << "Leave nodes with height 0 should be:  Apple, Avacado, Evergreen, Fingleberry, and Tupa" << endl;
    rotationTree.dump();
    cout << endl << endl;

    return 0;

}