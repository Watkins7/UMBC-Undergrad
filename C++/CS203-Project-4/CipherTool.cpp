/*
** File: CipherTool.cpp
** Project: CMSC 202 Project 4, Spring 2020
** Author: William Atkins
** Date: 4/20/20
** Section: 55
** Email: watkins7@umbc.edu
** Description: This is a .cpp driver for the Cipher Project 4 in CMSC 202 @ UMBC
*/

#include "CipherTool.h"

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string fileName){

    // Set file name
    m_filename = fileName;

    // Start Game setup
    Start();

}

// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers emptied
// Destructor
CipherTool::~CipherTool() {

    // Dynmacillay delete items in the vector
    while ( !m_ciphers.empty() ) {

        // Delete it and then pop it out
        delete m_ciphers.back();
        m_ciphers.pop_back();

    }

}

// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
// Game setup and while loop to run
void CipherTool::Start() {

    //Load the file selected
    LoadFile();

    int response; // stores users answer
    string exportFilename; // Stores the file name the user wants to export

    do {

        // Display Menu, return user's input
        response = Menu();

        switch (response){

            // Display all ciphers
            case 1:
                DisplayCiphers();
                break;

            // Encrypt all ciphers
            case 2:
                EncryptDecrypt(true);

                break;

            // Decrypt code
            case 3:
                EncryptDecrypt(false);

                break;

            // File output code
            case 4:
                Export();

                break;

            // Quit
            case 5:
                cout << "Thanks for using UMBC Ciphers" << endl;
                break;

            default:
                cout << "Menu() returned an int that is not coded in Start()" << endl;
                break;

        }

    } while (response != 5);

}

// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
//Load a file that contains ciphers
void CipherTool::LoadFile() {

    string message; // Stores the message
    string typeOfEncryption; // Stores what the encryption type is
    string isEncrypted; // Stores if the message is or is not encrypted

    // Open file
    ifstream inputFile;
    inputFile.open(m_filename);

    //Pointers for ciphers
    Cipher *newCipher;

    while(!inputFile.eof()){

        // Parse the message from the file, all ciphers should have 3 things
        getline(inputFile,typeOfEncryption,DELIMITER);
        getline(inputFile,isEncrypted,DELIMITER);
        getline(inputFile,message,DELIMITER);

        // Switch from string to bool
        bool isActuallyEncrypted = stoi(isEncrypted);

        //Create a new "Caesar Cipher"
        // We know that this is a caesar cipher
        if (typeOfEncryption == "c") {

            // Get key from file
            string caesarKey;
            getline(inputFile,caesarKey);
            //cout << "Caesar key from the file was: " << caesarKey << endl;

            //Change caesarKey from string to int
            int actualCaesarKey = stoi(caesarKey);

            // Create a new dynamically allocated caesar cipher
            newCipher = new Caesar(message,isActuallyEncrypted,actualCaesarKey);

            // Add cipher to vector
            m_ciphers.push_back(newCipher);

        } // End of Ceasar cipher creation

        //Create a new "Vigenere Cipher"
        // We know that this is a Vigenere cipher
        if (typeOfEncryption == "v"){

            // Get vigenereKey
            string vigenereKey;
            getline(inputFile,vigenereKey);

            // create new dynamically allocated vigenere cipher
            newCipher = new Vigenere(message,isActuallyEncrypted,vigenereKey);

            // put cipher into the vector
            m_ciphers.push_back(newCipher);

        }

        //Create a new "Ong Cipher"
        // We know that this is a ong cipher
        if (typeOfEncryption == "o"){

            // needed to store the rest of the line, even though there is nothing there
            string empty;
            getline(inputFile,empty);

            // create new dynamically allocated Ong cipher
            newCipher = new Ong(message, isActuallyEncrypted);

            // put cipher into the vector
            m_ciphers.push_back(newCipher);

        }

    } // End of while loop


    inputFile.close();

}

// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
// Will display all ciphers in the vector
void CipherTool::DisplayCiphers() {

    // Simple for loop to display all ciphers
    for (int i = 0; i < m_ciphers.size(); i++){
        cout << i+1 << ". " << *m_ciphers.at(i) << " " << m_ciphers.at(i)->ToString() << endl << endl;
    }

}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
// Displays a menu to the user
int CipherTool::Menu() {

    int answer = -1;

    do {

        // Message to screen
        cout << "What would you like to do?" << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export All Ciphers" << endl;
        cout << "5. Quit" << endl;

        // get answer from user
        cin >> answer;

    } while (answer <= 0 or answer >= 6);

    // return user answer
    return answer;

}

// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export() {

    string exportFilename; // stores the file name of the file being exported
    int count = 0; // stores how many files were exported

    // Ask user what file they want to export to
    cout << "What would you like to call the export file?" << endl;
    cin >> exportFilename;

    // Open new file
    ofstream newFile;
    newFile.open(exportFilename);

    // for loop runs through all ciphers
    for (int i = 0; i < m_ciphers.size(); i++){

        // output cipher input to file
        newFile << m_ciphers.at(i)->FormatOutput() << endl;

        // up count of ciphers exported
        count++;
    }

    // close file
    newFile.close();

    // display how many ciphers were exported
    cout << count << " ciphers exported" << endl;

}

// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool shouldEncrypt) {

    // counts how many items were encrypted or decrypted
    int count = 0;

    // If passed true, then we should encrypt
    if (shouldEncrypt){

        // Run a for loop in the vector to check which ciphers need
        for (int i = 0; i < m_ciphers.size(); i++){

            // if current cipher is not encrypted
            if ( m_ciphers.at(i)->GetIsEncrypted() == false) {

                // toggle their encryption on/off
                m_ciphers.at(i)->ToggleEncrypted();

                // up count of ciphers encrypted
                count++;

                // trigger encryption algorthim
                m_ciphers.at(i)->Encrypt();

            } // End of if statement about if a cipher was not encrypted


        } // End of for loop to search for unencrypted ciphers


        // Lastly display how many ciphers were encrypted
        cout << count << " ciphers were encrypted" << endl;

    }

    // Else we should decrypt
    else {

        // Run a for loop in the vector to check which ciphers are needed
        for (int i = 0; i < m_ciphers.size(); i++){

            // if current cipher is encrypted
            if ( m_ciphers.at(i)->GetIsEncrypted() == true) {

                // toggle their encryption on/off
                m_ciphers.at(i)->ToggleEncrypted();

                // up count of amount of ciphers decrypted
                count++;

                // trigger decryption algorthim
                m_ciphers.at(i)->Decrypt();

            } // End of if statement about if a cipher was encrypted


        } // End of for loop to search for encrypted ciphers


        // Lastly display how many ciphers were decrypted
        cout << count << " ciphers were decrypted" << endl;

    }

}

// Name: GetType
// Desc - Pass it a cipher and it returns the char of the subtype
// Returns c for Caesar, v for Vigenere, and o for Ong
// Preconditions - m_ciphers all populated
// Postconditions - Returns char of type
// Not needed
char GetType(Cipher* A){
    return 'x';
}