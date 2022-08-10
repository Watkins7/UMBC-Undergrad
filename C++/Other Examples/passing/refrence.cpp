#include <iostream>

using namespace std;

//Remove this to see a change from refrence and value
void enterTwo(int& var1, int& var2);

double average(int a, int b);



int main() {
    int row = 0;
    int column = 0;
    enterTwo(row, column);
    cout << "row = " << row << " column = " << column << endl;

    int a = 11;
    int b = 12;
    double c =14.9;
    double d = 14.1;

    cout << "The average of a and b is " << average(a,b) << endl;
    cout << "The average of c and d is " << average(c,d) << endl;


    return 0;
}

    void enterTwo(int &var1, int &var2) {
        cout << "Enter your row and column" << endl;
        cin >> var1 >> var2;
    }

    double average(int a, int b){
    cout << a << endl;
    return (a+b)/2;
}