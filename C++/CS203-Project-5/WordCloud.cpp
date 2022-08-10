/*
** File: WordCloud.cpp
** Project: CMSC 202 Project 5, Spring 2020
** Author: William Atkins
** Date: 5/5/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a header file for WordCloud, this class purpose is to load a file and generate a wordcloud
** ... It does this by creating a linked list for all the words in the file.  User has the option to remove...
** ... single instances of words and will by default will delete common words in a constant vector list.
** ... finally the linked list is outputed to a file
*/

#include "WordCloud.h"

// Name: WordCloud (Default Constructor)
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud. m_fileName would be hardcoded.
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(){

    m_cloud = nullptr;

}


// Name: WordCloud (Overloaded Constructor) - Passed filename for input
// Desc: Used to pass an essay (in input file) and generates word list and frequency
//       Dynamically allocates m_cloud
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
WordCloud::WordCloud(string file){

    // Set file name
    m_fileName = file;

    // Make a new LL string;
    m_cloud = new LL<string>();

}


// Name: ~WordCloud (Destructor)
// Desc: Deallocates m_cloud
// Preconditions: m_cloud has been dynamically allocated
// Postconditions: m_cloud is empty
WordCloud::~WordCloud(){

    delete(m_cloud);
    m_cloud = nullptr;

}


// Name: Export
// Desc: Iterates through m_cloud and exports to file "data:frequency"
// Preconditions: m_cloud is populated
// Postconditions: New export file is created with "data:frequency" one on each line
void WordCloud::Export(){

    string exportFilename; // stores the file name of the file being exported
    int count = 0; // stores how many words were exported

    // Ask user what file they want to export to
    cout << "What would you like to call the export file?" << endl;
    cin >> exportFilename;

    // Open new file
    ofstream newFile;
    newFile.open(exportFilename);

    // Get output and put it into newFile
    newFile << *m_cloud;

    // close file
    newFile.close();

    // display how many words were exported
    cout << m_cloud->GetSize() << " unique words exported" << endl;

}


// Name: Start
// Desc: Calls LoadFile, RemoveCommon, Diplay, and Export
// Preconditions: None (filename is available)
// Postconditions: None
void WordCloud::Start(){

    string response = "blank";  // holds user's response
    stringstream lowerResponseWord; // used to convert word into lowercase

    // Call LoadFile
    LoadFile();

    // RemoveCommon
    RemoveCommon();

    while ( response != ACCCEPTABLE_RESPONSE.at(0) && response != ACCCEPTABLE_RESPONSE.at(1)
            && response != ACCCEPTABLE_RESPONSE.at(2) && response != ACCCEPTABLE_RESPONSE.at(3) ) {

        // Ask if they want to remove singles
        cout << "Would you like to remove all the words with a frequency of 1?" << endl;
        cin >> response;

        // Reset stringstream
        lowerResponseWord.str("");

        // for loop to lower the word
        for (string::iterator it=response.begin(); it != response.end(); it++) {
            lowerResponseWord << tolower(*it, locale());
        }

        // Reset response to lower case
        response = lowerResponseWord.str();

        // if response is "yes" remove all singles in the list
        if (response == ACCCEPTABLE_RESPONSE.at(0) || response == ACCCEPTABLE_RESPONSE.at(1)) {
            RemoveSingles();
        }

        if ( response != ACCCEPTABLE_RESPONSE.at(0) && response != ACCCEPTABLE_RESPONSE.at(1)
           && response != ACCCEPTABLE_RESPONSE.at(2) && response != ACCCEPTABLE_RESPONSE.at(3) ) {
            cout << "Invalid response, please try something like... \"no\", \"n\", \"yes\", \"y\", \"NO\", \"N\", \"YES\", \"Y\" " << endl;
        }

    } // End of the while loop


    // Display
    cout << *m_cloud;

    // Export
    Export();


}


// Name: RemovePunct (passed a string
// Desc: When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void WordCloud::RemovePunct(string& word){

    // Remove extra puncuation
    // If the begining letter is not a number or letter, remove it
    if ( ( word.at(0) >= 48 && word.at(0) <= 57) || ( word.at(0) >= 65 && word.at(0) <= 90 ) || ( word.at(0) >= 97 && word.at(0) <= 122) )
        cout << "";
    else
        word = word.substr(1,word.size());

    // Checks end of the word and removes anything that is not a letter or number
    if ( ( word.at(word.size()-1) >= 48 && word.at(word.size()-1) <= 57 ) || ( word.at(word.size()-1) >= 65 && word.at(word.size()-1) <= 90 ) || ( word.at(word.size()-1) >= 97 && word.at(word.size()-1) <= 122) )
        cout << "";
    else
        word = word.substr(0,word.size()-1);


}


// Name: RemoveCommon
// Desc: Iterates through m_cloud and removes all common words after they are read
// Preconditions: m_cloud is populated and EXCLUDE_LIST is populated
// Postconditions: m_cloud will have no words from EXCLUDE_LIST
void WordCloud::RemoveCommon(){

    string wordInList; // Word in list
    string wordInExcludeList; // Word in exclude list
    stringstream lowerExcludeWord; // Puts Exclude word to lowercase


    // for loop that gets each word in the EXCLUDE-LIST
    for (vector<string>::const_iterator i = EXCLUDE_LIST.begin(); i != EXCLUDE_LIST.end(); ++i){

        // Reset stringstream
        lowerExcludeWord.str("");

        // Set new EXCLUDE WORD
        wordInExcludeList = *i;

        // for loop to get the word in lowercase
        for (string::iterator it=wordInExcludeList.begin(); it != wordInExcludeList.end(); it++) {
            lowerExcludeWord << tolower(*it, locale());
        }

        // Reset word to lowercase
        wordInExcludeList = lowerExcludeWord.str();

        // for loop to go through whole m_cloud list, if the word exist, then delete it
        for (int z = 0; z < m_cloud->GetSize(); z++){

            // Did we find the word?
            if ( wordInExcludeList == m_cloud->operator[](z).first ) {

                // Delete it, and push "z" back
                m_cloud->RemoveAt(m_cloud->operator[](z).first);
                z--;

            } // End of if statement

        } // End of for loop for all the m_cloud words

    } // End of for loop for all the exclude words



} // End of RemoveCommon


// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_cloud is populated
void WordCloud::LoadFile(){

    string word; // word to put in linked list
    ifstream inputFile; // opens file
    stringstream lowerWord; // saves lower

    inputFile.open(m_fileName); // open file name

    // While loop that opens a file and gets words until the end of the file is reached
    while ( inputFile >> word ){

        // Clear the string stream word
        lowerWord.str("");

        // for loop to get the word in lowercase
        for (string::iterator it=word.begin(); it != word.end(); it++) {
            lowerWord << tolower(*it, locale());
        }

        // Reset "word" to lowercase version
        word = lowerWord.str();

        // Clean word of puncucation from ends of the word
        RemovePunct(word);

        // Insert word into linked list
        m_cloud->Insert(word);

    }

}


// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_cloud is a pointer!
// Preconditions: m_cloud is populated
// Postconditions: m_cloud will have no words with a frequency of 1
void WordCloud::RemoveSingles(){

    int count = 0;  // keeps track of how many singles are being removed

    // for loop that runs through m_cloud, looking for instances of 1
    for ( int i = 0; i < m_cloud->GetSize(); i++){

        // See if the pair only has one instance, if it does then delete it
        if ( m_cloud->operator[](i).second == 1 ) {
            m_cloud->RemoveAt(m_cloud->operator[](i).first);
            count++;
            i--;
        }

    }

    cout << count << " words removed." << endl;


}