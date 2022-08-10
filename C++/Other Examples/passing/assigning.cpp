#include <iostream>
using namespace std;

int addOne(int);

int main() {
    int num1 = 10;
    int num2 = 20;

    //Junk code
    int * num1Ptr = &num1;
    //num1Ptr+=1;
    cout << *num1Ptr << endl;

    cout << addOne(num1) << endl;
    num2 = addOne(num2);
    cout << num2 << endl;

    // ++num Increments while line is ruuning
    // num++ increments after line has run

    return 0;
}

int addOne(int num){
    // return num++;

    return num+2;

    // return ++num;

   // num++;
   // return num;
}