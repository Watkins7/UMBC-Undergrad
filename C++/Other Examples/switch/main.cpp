//Comments

#include <iostream>
#include <string>
using namespace std;

const string password = "UMBC";
int main() {

    //Variables
    string myInput;
    bool inSystem = false;
    int choice = 0;


    //Cout, cin examples
    cout << "Enter the password:" << endl;
    cin >> myInput;

    if (password == myInput) {
        cout << "You are IN the system." << endl;
        inSystem = true;
    }

    else
        cout << "You are NOT in the system" << endl;

    if(inSystem)
        cout << "What would you like to do?:" << endl;


    //Switch Example
    //do-while example
    do {
        cout << "What would you like to do?" << endl;
        cout << "1. Earn good grade" << endl;
        cout << "2. Earn more money" << endl;
        cout << "3. Live in basement" << endl;
        cout << "4. Quit" << endl;
        cin >> choice;
    }while(choice < 1 or choice > 4);

        switch (choice) {
            case 1:
                cout << "Earned A" << endl;
                break;
            case 2:
                cout << "You earned more money $$$$$" << endl;
                break;
            case 3:
                cout << "Okay you continue to live" << endl;
                break;
            case 4:
                break;
            default:
                cout << "Error in response" << endl;
        }

    //For loop example
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 11; j++) {
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}
