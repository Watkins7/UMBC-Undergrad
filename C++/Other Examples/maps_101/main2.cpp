/*Title: map2.cpp
Author: CMSC 202
Date: 10/22/2019
Description: This is an example of using the map STL in C++.
*/
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <set>

using namespace std;

int main () {

    /*
    // How to
    multimap<string, int> mapOfWords;
    mapOfWords.insert(make_pair("earth" , 1));
    mapOfWords.insert(make_pair("moon" , 2));
    mapOfWords.insert(make_pair("earth", 5));


    // make a interator to help traverse the list
    multimap<string, int>::iterator findIt = mapOfWords.find("moon");

    // How to set a new value inside a map
    if (findIt != mapOfWords.end())
        findIt->second = 9999;

    // iterator to help go through list
    multimap<string, int>::iterator it = mapOfWords.begin();
    while(it != mapOfWords.end()){
        cout << it->first << " :: " << it->second << endl;
        it++;
    }

    if(mapOfWords.find("sun") != mapOfWords.end())
        cout << "word sun found" << endl;

    if(mapOfWords.find("mars") == mapOfWords.end())
        cout << "Word mars not found" << endl;



    //******************************************************************
    // Lists

    // empty list of ints
    std::list<int> first;

    // four ints with value 100
    list<int> second (4,100);

    // iterating through second
    list<int> third (second.begin(),second.end());

    // a copy of third
    list<int> fourth (third);

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    list<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    cout << "The contents of fifth are: ";
    for (list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
        cout << *it << ' ';

    cout << '\n';

     */
    //********************************************************************
    // /*
    vector< pair<int, int> > myPairs;
    for(int i = 0; i < 100; i=i+20){
        myPairs.push_back( make_pair(i,i+10) );
    }
    for(vector<pair<int,int> >::iterator it = myPairs.begin(); it!=myPairs.end(); ++it){
        cout << "Pair:" << it->first << ":" << it->second << endl;
    }

    // */
    //*************************************************************************
    //REVERSE ITERATOR

     int i = 0;
    string subj[] = {"math","science","cs","stat"};
    for(auto it = rbegin(subj); it != rend(subj); it++)
        cout << *it << endl;

    //************************************************************************

    // AUTO

    int c_array[] = {1,3,5,7,9}, acc = 0;

    for (auto it : c_array) {
        acc += it;
    }

    cout << "Acc is: " << acc << endl;

    //**************************************************************
    /*
    set<int> mySet;

    mySet.insert(1);
    mySet.insert(-3);
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(5);

    for (auto it = mySet.begin(); it != mySet.end(); it++){
        cout << *it << endl;
    }
    */
    //*********************************************************

    struct Node {
        Node *m_next = nullptr;
        int data;
    };

    Node apples;
    apples.data = 1;
    Node bannanas;
    bannanas.data = 2;
    Node pickles;
    pickles.data = 3;

    apples.m_next = &bannanas;
    bannanas.m_next = &pickles;

    Node *test = &apples;
    while (test != nullptr){
        cout << test->data << endl;
        test = test->m_next;
    }




    return 0;



    return 0;
}

