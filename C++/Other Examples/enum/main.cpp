#include <iostream>
#include <iomanip>
const int WORD_INPUT = 4;

using namespace std;

void rotate(int array[]);
int rotate(int);
/* void populateArray(char array[WORD_INPUT]);
void printArray(char array[WORD_INPUT]);


int main(){

    char myWord[WORD_INPUT] ;
    populateArray(myWord);
    printArray(myWord);
    return 0;

}

void populateArray(char array[]){
    char tempWord[WORD_INPUT];
    cout << "Enter a " << WORD_INPUT << " letter word: " << endl;
    cin >> tempWord;
    for(int i = 0; i < WORD_INPUT; i++){
        array[i] = tempWord[i];
    }
}

void printArray(char array[]) {
    int i = (WORD_INPUT) - 1;
    while (i >= 0) {
        cout << array[i];
        i--;
    }

    cout << endl;
}
 */

/*
struct Student{
    string name;
    int stuID;
};

int main (){
    const int NUM_INPUT= 3;
    int counter = 0;
    Student myClass[NUM_INPUT];
    for (int i = 0; i < NUM_INPUT; i++){
        cout << "Enter name:" << endl;
        getline(cin, myClass[i].name);
        cout << "Enter Student ID:" << endl;
        cin >> myClass[i].stuID;
        if(cin.fail() == '\n')
            cin.ignore();
    }

    while (counter < NUM_INPUT){
        cout << myClass[counter].name << " "
            << myClass[counter].stuID << endl;
        counter++;
    }
}

 */

int main(){


    enum seasons {Winter, Spring, Summer, Fall};
    cout << "My favorite season is " << Spring << endl;

    double x =0.5;
    cout << x << endl;

    int list[] = {2,4,6,8,10,12};

    for (int j = 4; j > 0; --j)
        cout << list[j+1] << " ";
    cout << endl;

    cout << setprecision(4) << fixed << 100.012344444 << endl;
}