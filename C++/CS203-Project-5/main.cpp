//Title: proj5.cpp
//Author: Jeremy Dixon
//Date: 4/20/2020
//Description: This is main for project 5.
#include "WordCloud.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

//Inside the parameters for main, we can pass arguments
//argc is the count of arguments
//argv are the parameters themselves
int main(int argc, char* argv[]) {
    cout << "Welcome to UMBC Word Clouds" << endl;
    /*while (argc < 2) { //Checks to make sure the user passes a file to load
        cout << "You are missing a data file." << endl;
        cout << "Expected usage ./proj5 proj5_test1.txt" << endl;
        cout << "The input file should have some words" << endl;
        return 0;
    }
     */
    WordCloud myCloud("proj5_test2.txt"); //Creates a new word cloud by passing the filename
    //cout << "********Made Word cloud" << endl;
    myCloud.Start(); //Starts the wordCloud


    //Test 1 - Default Constructor and Push
    cout << "Test 1 - Default Constructor and Push Running" << endl;
    //Test Default Constructor
    LL <string>* newLL1 = new LL<string>();
    //Push 4 nodes into LL
    newLL1->Insert("candy");
    newLL1->Insert("caaandy");
    newLL1->Insert("caaaaaaaaaaaaandy");
    newLL1->Insert("caaaaaaaaaandy");
    newLL1->Insert("cookies");
    newLL1->Insert("candy");
    newLL1->Insert(":bananas");
    newLL1->Insert(";dogs");
    newLL1->Insert("apples");
    newLL1->Insert(".elephants");
    newLL1->Insert("barf");
    newLL1->Insert("candy");
    newLL1->Insert("cookies/");
    newLL1->Insert("candy,");
    newLL1->Insert("bananas.");
    newLL1->Insert("dogs:");
    newLL1->Insert("apples");
    newLL1->Insert("!elephants");
    newLL1->Insert("barf");
    newLL1->Insert("barf");
    newLL1->Insert("barf");
    newLL1->Insert("barf");
    newLL1->Insert("barf");
    newLL1->Insert("barf");
    newLL1->Insert("!elephants");

    newLL1->Display();

    cout << "Test 1.a - Default Constructor and Push Running, WITH INTS!" << endl;
    //Test Default Constructor
    LL <int>* newLL1a = new LL<int>();
    //Push 4 nodes into LL
    newLL1a->Insert(1);
    newLL1a->Insert(1);
    newLL1a->Insert(2);
    newLL1a->Insert(12);
    newLL1a->Insert(14);
    newLL1a->Insert(1);
    newLL1a->Insert(5);
    newLL1a->Insert(8);
    newLL1a->Insert(3);
    newLL1a->Insert(7);
    newLL1a->Insert(1);
    newLL1a->Insert(5);
    newLL1a->Insert(8);
    newLL1a->Insert(3);
    newLL1a->Insert(7);

    newLL1a->Display();


    //Test 2 - Copy Constructor and Assignment Operator
    cout << "Test 2.a - Copy Constructor and Assignment Operator Running" << endl;
    //Test Copy constructor
    LL <int>* newLL2a = new LL<int>(*newLL1a);
    cout << "*******Original*********" << endl;
    newLL1a->Display();
    cout << "*******Copy*********" << endl;
    newLL2a->Display();






    //Test 2 - Copy Constructor and Assignment Operator
    cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
    //Test Copy constructor
    LL <string>* newLL2 = new LL<string>(*newLL1);
    cout << "*******Original*********" << endl;
    newLL1->Display();
    cout << "*******Copy*********" << endl;
    newLL2->Display();


    //Test Overloaded Assignment Operator
    LL <int>* newLL3a = new LL<int>();
    *newLL3a = *newLL1a;
    cout << "*******Assignment, List 3, With ints*********" << endl;
    newLL3a->Display();
    cout << endl;


    //Test Overloaded Assignment Operator
    LL <string>* newLL3 = new LL<string>();
    *newLL3 = *newLL1;
    cout << "*******Assignment, List 3*********" << endl;
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

    cout << "-----------------------------Testing find function" << endl;
    cout << newLL1->Find("barf")->GetData().second << endl;
    cout << newLL1a->Find(14)->GetData().second << endl;

    if ( newLL1->Find("Thaddeus") == nullptr )
        cout << "cannont find that name" << endl;




    return 0;
}
